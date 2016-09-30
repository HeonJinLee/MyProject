#pragma warning(disable:4996)
#include <winsock2.h> 
#include <stdio.h> 
#include <stdlib.h>

#define ICMP_ECHO 8 
#define ICMP_ECHOREPLY 0 
#define ICMP_MIN 8 

typedef struct iphdr {
	/* IP 헤더 구조 */
	unsigned int h_len : 4;
	unsigned int version : 4;
	unsigned char tos;
	unsigned short total_len;
	unsigned short ident;
	unsigned short frag_and_flags;
	unsigned char ttl;
	unsigned char proto;
	unsigned short checksum;
	unsigned int sourceIP;
	unsigned int destIP;
}IpHeader;

typedef struct _ihdr {
	BYTE i_type;
	BYTE i_code;
	USHORT i_cksum;
	USHORT i_id;
	USHORT i_seq;
	ULONG timestamp;
}IcmpHeader;

#define default_pkt_size 32 
#define max_pkt 1024
void make_icmp(char *, int);
USHORT checksum(USHORT *, int);
void analyse_response(char *, int, struct sockaddr_in *);

void errorexit(char *errmsg) {
	fprintf(stderr, errmsg);
	exit(-1);
}

int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET raw_skt;
	struct sockaddr_in target, from;
	struct hostent *host_ent;
	int return_value, datasize, byte_sent;
	int timeout = 1000, counter = 10;
	char *target_ip, *icmp_data, *recvbuf;
	unsigned int addr = 0; 
	USHORT seq_no = 0;
	char hostname[] = "google.com"; // default server

	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0)
	{
		errorexit("WSAStartup 실패\n");
	}

	if (argc<2)
	{
		fprintf(stderr, "%s 호스트주소 [데이터 크기]\n 정해진 server, 데이터크기 사용함\n", argv[0]);
	}
	else strcpy(hostname, argv[1]);

	raw_skt = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	if (raw_skt == INVALID_SOCKET)
	{
		errorexit("WSASocket() 실패\n");
	}

	return_value = setsockopt(raw_skt, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	if (return_value == SOCKET_ERROR)
	{
		fprintf(stderr, " 수신 제한시간 설정 실패\n");
		return -1;
	}

	timeout = 1000;

	return_value = setsockopt(raw_skt, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
	if (return_value == SOCKET_ERROR)
	{
		errorexit("송신 제한시간 설정 실패\n");
	}
	memset(&target, 0, sizeof(target));	//초기화한다 target주소를

	/*if( (host_ent = gethostbyname(hostname)) == NULL) 
	{ 
		target.sin_addr.s_addr = (IN_ADDR *)(hostname);
		target.sin_family = AF_INET;
	} else*/
	{
		host_ent = gethostbyname(hostname); 	//도메인주소를 주소값으로 바꿔준다.
		memcpy(&target.sin_addr, host_ent->h_addr, host_ent->h_length);
		target.sin_family = host_ent->h_addrtype;
	}

	target_ip = inet_ntoa(target.sin_addr); //타겟 ip를 도트 데시말로 바꿔준다.
	if (argc >2)
	{    /* 사용자가 데이터 크기를 설정했다면 */
		datasize = atoi(argv[2]);
		if (datasize == 0) datasize = default_pkt_size; //default 32크기로 날린다.
	}
	else datasize = default_pkt_size;

	datasize += sizeof(IcmpHeader);

	if ((icmp_data = malloc(max_pkt)) == 0) 
		errorexit("메모리 할당 실패");
	if ((recvbuf = malloc(max_pkt)) == 0) 
		errorexit("메모리 할당 실패");



	memset(icmp_data, 0, max_pkt);
	make_icmp(icmp_data, datasize);

	while (--counter>0) { 
		/* 일정한 회수만큼 ICMP를 보냄*/
		int len_addr = sizeof(struct sockaddr);
		((IcmpHeader*)icmp_data)->i_cksum = 0;
		((IcmpHeader*)icmp_data)->timestamp = GetTickCount();
		// 왕복 지연 시간을 측정하기 위하여 현재 시간을 기록.
		((IcmpHeader*)icmp_data)->i_seq = seq_no++;
		((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, datasize);
		byte_sent = sendto(raw_skt, icmp_data, datasize, 0, (struct sockaddr*)&target, sizeof(target));

		if (byte_sent == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT)
			{
				printf("시간 초과\n"); 
				continue;
			}
			errorexit("sendto 실패\n");
		}

		if (byte_sent < datasize) 
			fprintf(stdout, "%d bytes 전송 \n", byte_sent);
		return_value = recvfrom(raw_skt, recvbuf, max_pkt, 0, (struct sockaddr*)&from, &len_addr);

		if (return_value == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT)
			{
				printf("시간 초과\n"); 
				continue;
			}
			fprintf(stderr, "recvfrom 실패\n");
		}
		analyse_response(recvbuf, return_value, &from);
		Sleep(1000);
	}
	return 0;
}


void analyse_response(char *buf, int bytes, struct sockaddr_in *from)
{
	IpHeader *iphdr;
	IcmpHeader *icmphdr;
	unsigned short iphdrlen;
	iphdr = (IpHeader *)buf;
	iphdrlen = iphdr->h_len * 4;
	if (bytes < iphdrlen + ICMP_MIN)
	{
		printf("패킷 크기가 너무 작음 %s\n", inet_ntoa(from->sin_addr));
	}
	icmphdr = (IcmpHeader*)(buf + iphdrlen);
	if (icmphdr->i_type != ICMP_ECHOREPLY) { errorexit("에코 응답이 아님\n"); }

	if (icmphdr->i_id != (USHORT)GetCurrentProcessId())
	{
		errorexit("식별자가 다른 패킷임\n");
		// 자신이 보내지 않은 엉뚱한 곳으로부터 응답이 도착했다.
	}
	printf("%s로부터 %d bytes 도착", inet_ntoa(from->sin_addr), bytes);
	printf(" icmp 순서번호 = %d. ", icmphdr->i_seq);
	printf(" 왕복지연시간:%d ms\n", GetTickCount() - icmphdr->timestamp);

}

USHORT checksum(USHORT *buffer, int size)
{
	unsigned long cksum = 0;
	while (size >1) 
	{
		cksum += *buffer++; 
		size -= sizeof(USHORT);
	}
	if (size)
	{
		cksum += *(UCHAR*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

void make_icmp(char * icmp_data, int datasize)
{
	IcmpHeader *icmp_hdr;
	icmp_hdr = (IcmpHeader*)icmp_data;
	icmp_hdr->i_type = ICMP_ECHO;
	icmp_hdr->i_code = 0;
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
	memset(icmp_data + sizeof(IcmpHeader), 0xaa, datasize - sizeof(IcmpHeader));
	/* 0xaa 임의 데이터로 채우기 */
}