#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#pragma comment(lib,"ws2_32")

void errorexit(char *);
BOOL parse(int, char **);
int socket_type = SOCK_STREAM;  // default 
char *server_name = "localhost";
unsigned short port = 25000;  // default port num 
int main(int argc, char *argv[]) {
	char Buffer[128];
	int result;
	unsigned int addr;
	struct sockaddr_in server;
	struct hostent *hp;
	WSADATA wsaData;
	SOCKET  serve_socket;
	if (parse(argc, argv) == FALSE) exit(-1);
	if ((result = WSAStartup(0x202, &wsaData)) != 0)  errorexit("WSAStartup 실패");
	if (port == 0) errorexit("사용법을 다시 보세요");
	if (isalpha(server_name[0]))
		hp = gethostbyname(server_name);
	else      {
		addr = inet_addr(server_name);
		hp = gethostbyaddr((char *)&addr, 4, AF_INET);
	}
	if (hp == NULL)         errorexit("%s 라는 주소 없음\n");
	memset(&server, 0, sizeof(server));
	memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);

	serve_socket = socket(AF_INET, socket_type, 0);
	if (serve_socket < 0)
		errorexit("소켓 열수 없음\n");

	printf("%s 서버에 연결 성공\n", hp->h_name);
	if (connect(serve_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
		errorexit("연결 실패\n");


	while (1){

		//wsprintf(Buffer,"12122443 heon");


		result = recv(serve_socket, Buffer, sizeof(Buffer), 0);
		if (result == SOCKET_ERROR){
			fprintf(stderr, "recv() 실패\n");
			closesocket(serve_socket);
			WSACleanup();
			return -1;
		}
		if (result == 0) {
			printf("서버 연결을 닫음\n");
			closesocket(serve_socket);
			WSACleanup();
			return -1;
		}
		printf("데이터 수신 성공 : %s\n", Buffer);


		fprintf(stdout, "Client : ");			//추가한부분	표준출력
		fgets(Buffer, sizeof(Buffer), stdin);	//추가한부분	표준입력


		result = send(serve_socket, Buffer, sizeof(Buffer), 0);
		if (result == SOCKET_ERROR)
			errorexit("전송 실패\n");

		//printf("보낸 데이터 [%s] \n", Buffer);


		if (strncmp(Buffer, "BYE", 3) == 0) {		//추가한부분
			printf("서버 연결을 닫음\n");
			closesocket(serve_socket);
			WSACleanup();
			return -1;
		}
	}
	
	closesocket(serve_socket);
	WSACleanup();
	exit(0);
	
}

BOOL parse(int argc, char **argv) {
	int i;

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if ((argv[i][0] == '-') || (argv[i][0] == '/')) {
				switch (tolower(argv[i][1])) {
				case 'p':
					if (!_stricmp(argv[i + 1], "TCP"))
						socket_type = SOCK_STREAM;
					else if (!_stricmp(argv[i + 1], "UDP"))
						socket_type = SOCK_DGRAM;
					else {
						fprintf(stderr, "사용법 :%s -p [protocol] -s [server] -n [port num]\n", argv[0]);
						return FALSE;
					}
					i++;
					break;
				case 's':
					server_name = argv[++i];
					break;
				case 'n':
					port = atoi(argv[++i]);
					break;
				default:
					fprintf(stderr, "사용법 :%s -p [protocol] -s [server] -n [port num]\n", argv[0]);
					return FALSE;
					break;
				}	// of switch
			}	//of if
			else {
				fprintf(stderr, "사용법 :%s -p [protocol] -s [server] -n [port num]\n", argv[0]);
				return FALSE;
			}
		}	//of for
	}	//of if
}

void errorexit(char *err_msg) {
	fprintf(stderr, err_msg);
	WSACleanup();
	exit(-1);
}