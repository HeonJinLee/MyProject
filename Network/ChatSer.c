#include<WinSock2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#pragma comment(lib,"ws2_32")
#define socket_type SOCK_STREAM
//define 하지 않으면 SOCK_DGRAM으로 간주
//#define socket_type SOCK_DGRAM
#define default_port 25000

int main(int argc, char **argv) {
	char Buffer[128];
	int result, port;
	struct sockaddr_in my_addr, your_addr;
	int len_addr = sizeof(struct sockaddr_in);
	WSADATA wsaData;
	SOCKET socket_descriptor, rcv_sock;

	if (argc < 2) port = default_port;
	else port = atoi(argv[1]);

	if ((result = WSAStartup(0x202, &wsaData)) != 0) {
		fprintf(stderr, "WSAStartup 실패\n");
		WSACleanup();
		return -1;
	}

	socket_descriptor = socket(AF_INET, socket_type, 0);
	if (socket_descriptor == INVALID_SOCKET) {
		fprintf(stderr, "socket 생성 실패\n");
		WSACleanup();
		return -1;
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(port);
	if (bind(socket_descriptor, (struct sockaddr*) &my_addr, sizeof(my_addr)) == SOCKET_ERROR) {
		fprintf(stderr, "bind() 실패\n");
		WSACleanup();
		return -1;
	}

	if (socket_type == SOCK_STREAM) {
		//UDP를 사용한다면 listen()이 필요없다.
		if (listen(socket_descriptor, 5) == SOCKET_ERROR) {
			fprintf(stderr, "listen() 실패\n");
			WSACleanup();
			return -1;
		}
	}
	if (socket_type == SOCK_STREAM) {
		//TCP에서만 accept()가 필요하다.
		rcv_sock = accept(socket_descriptor, (struct sockaddr*)&your_addr, &len_addr);
		if (rcv_sock == INVALID_SOCKET) {
			fprintf(stderr, "accept() 실패\n");
			WSACleanup();
			return -1;
		}
		printf("accept() : %s, 포트번호 %d로부터의 연결 허락\n", inet_ntoa(your_addr.sin_addr), htons(your_addr.sin_port));
	}
	/*
	else //UDP를 사용한다면 accept()가 필요없다.
	rcv_sock = socket_descriptor;
	*/
	//	closesocket(socket_descriptor);			//socket_descriptor 소켓을 닫아준다. 이제 쓰이지 않기때문에

	while (1) {			//while을 accept에서 rcv로 옮겼다. accept가 무한 루프면 할때마다 연결을 하는거라서.

		fprintf(stdout, "server : ");			//새로 추가했다.	글씨 출력
		fgets(Buffer, sizeof(Buffer), stdin);	//새로 추가했다.	Buffer배열안에 글씨 입력하기.

		if (socket_type == SOCK_STREAM)
			result = send(rcv_sock, Buffer, sizeof(Buffer), 0);	//echo
		else result = sendto(rcv_sock, Buffer, sizeof(Buffer), 0, (struct sockaddr *)&your_addr, len_addr);
		if (result == SOCKET_ERROR) {
			fprintf(stderr, "send()/sendto() 실패\n");
		}
		if (strncmp(Buffer, "BYE", 3) == 0) {	//BYE를 입력하면 서버 종료.
			printf("서버 연결을 닫음\n");
			closesocket(rcv_sock);
			WSACleanup();
			return -1;
		}




		if (socket_type == SOCK_STREAM)
			result = recv(rcv_sock, Buffer, sizeof(Buffer), 0);
		else {
			result = recvfrom(rcv_sock, Buffer, sizeof(Buffer), 0, (struct sockaddr *)&your_addr, &len_addr);
			printf(" %s로부터 데이터 수신\n", inet_ntoa(your_addr.sin_addr));
		}
		if (result == SOCKET_ERROR) {
			fprintf(stderr, "recv()/recvfrom() 실패\n");
			closesocket(rcv_sock);
			continue;
		}
		if (result == 0) {
			printf("클라이언트가 연결을 끊음\n");
			closesocket(rcv_sock);
			continue;
		}
		printf("받은 데이터 :%s\n", Buffer);

		
		//else printf("계속 요청을 기다리고 있습니다.\n");
		continue;
	}
}