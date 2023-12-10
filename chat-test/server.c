// 통신을 위한 포트를 열어주는 server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define MAX_LINE  1024
#define MAX_SOCK 2048
time_t ct;
struct tm tm;
int active_user =0;			// 활성화된 유저 정보
int active_chat =0;			// 채팅 개수
int max_fdp1;				
char *EXIT_STRING ="exit"; // 종료
char *START_STRING ="Connected to chat_server \n"; // 메시지 채팅 시작
int client_sock_list[MAX_SOCK];		// 소켓 리스트
char ip_list[MAX_SOCK][20];		// ip list
int listen_sock;			
void err_handle(char *msg) { perror(msg); exit(1); }
int listen_tcp(int host, int port, int backlog); 
void client_add(int s, struct sockaddr_in *new_client_addr);   
int get_socket_max();				
void cleant_remove(int s);	
void *thread_function(void *arg);
int main(int argc, char *argv[]) {
	struct sockaddr_in client_addr;
	char buf[MAX_LINE +1];  // 메시지를 받기 위한 버퍼
	int i, j, nbyte, accp_sock, addrlen =sizeof(struct
		sockaddr_in);
	fd_set read_fds;	
	pthread_t a_thread;
	if (argc !=2) {
		printf("사용법 :%s port\n", argv[0]);
		exit(0);
	}
	
	listen_sock = listen_tcp(INADDR_ANY, atoi(argv[1]), 5);
	
	// 쓰레드 생성
	pthread_create(&a_thread, NULL, thread_function, (void *)NULL);
	while (1) {
		FD_ZERO(&read_fds);
		FD_SET(listen_sock, &read_fds);
		for (i =0; i < active_user; i++)
			FD_SET(client_sock_list[i], &read_fds);
		max_fdp1 = get_socket_max() +1;	
		if (select(max_fdp1, &read_fds, NULL, NULL, NULL) <0)
			err_handle("select fail");
		if (FD_ISSET(listen_sock, &read_fds)) {
			accp_sock = accept(listen_sock,
				(struct sockaddr*)&client_addr, &addrlen);
			if (accp_sock ==-1) err_handle("accept fail");
			client_add(accp_sock, &client_addr);
			send(accp_sock, START_STRING, strlen(START_STRING), 0);
			ct = time(NULL);		
			tm =*localtime(&ct);
			write(1, "\033[0G", 4);		
			printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
			fprintf(stderr, "\033[33m");
			printf("사용자 1명 추가. 현재 참가자 수 = %d\n", active_user);
			fprintf(stderr, "\033[32m");
			fprintf(stderr, "server>"); 
		}
		
		for (i =0; i < active_user; i++) {
			if (FD_ISSET(client_sock_list[i], &read_fds)) {
				active_chat++;				
				nbyte = recv(client_sock_list[i], buf, MAX_LINE, 0);
				if (nbyte <=0) {
					cleant_remove(i);	
					continue;
				}
				buf[nbyte] =0;
				
				if (strstr(buf, EXIT_STRING) !=NULL) {
					cleant_remove(i);	
					continue;
				}
				
				for (j =0; j < active_user; j++)
					send(client_sock_list[j], buf, nbyte, 0);
				printf("\033[0G");		
				fprintf(stderr, "\033[97m");
				printf("%s", buf);			
				fprintf(stderr, "\033[35m");
				fprintf(stderr, "server>"); 
			}
		}
	}
	return 0;
}
// 클라이언트 추가
void client_add(int s, struct sockaddr_in *new_client_addr) {
	char buf[20];
	inet_ntop(AF_INET, &new_client_addr->sin_addr, buf, sizeof(buf));
	write(1, "\033[0G", 4);		
	fprintf(stderr, "\033[33m");	
	printf("new client: %s\n", buf); 
	client_sock_list[active_user] = s;
	strcpy(ip_list[active_user], buf);
	active_user++; 
}
// listen 소켓 생성
int  listen_tcp(int host, int port, int backlog) {
	int sd;
	struct sockaddr_in server_addr;
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd ==-1) {
		perror("socket fail");
		exit(1);
	}
	
	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(host);
	server_addr.sin_port = htons(port);
	if (bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0) {
		perror("bind fail");  exit(1);
	}
	// 대기
	listen(sd, backlog);
	return sd;
}


void *thread_function(void *arg) {
	int i;
	printf("===========Availble Commands=========== \n");
	printf("help, active_user, active_chat, ip_list\n");
	printf("======================================= \n");
	while (1) {
		char buf_msg[MAX_LINE +1];
		fprintf(stderr, "\033[1;32m"); 
		printf("Socket Server > ");
		fgets(buf_msg, MAX_LINE, stdin); 
		if (!strcmp(buf_msg, "\n")) continue;  
		else if (!strcmp(buf_msg, "help\n"))
			printf("help, active_user, active_chat, ip_list\n");
		else if (!strcmp(buf_msg, "active_user\n"))
			printf("현재 참가자 수 = %d\n", active_user);
		else if (!strcmp(buf_msg, "active_chat\n"))
			printf("지금까지의 대화의 수 = %d\n", active_chat);
		else if (!strcmp(buf_msg, "ip_list\n"))
			for (i =0; i < active_user; i++)
				printf("%s\n", ip_list[i]);
		else 
			printf("해당 명령어가 없습니다. help 를 참조하세요.\n");
	}
}
// 최대 인원 초과
int get_socket_max() {
	
	int max = listen_sock;
	int i;
	for (i =0; i < active_user; i++)
		if (client_sock_list[i] > max)
			max = client_sock_list[i];
	return max;
}

// 채팅 종료
void cleant_remove(int s) {
	close(client_sock_list[s]);
	if (s != active_user -1) { 
		client_sock_list[s] = client_sock_list[active_user -1];
		strcpy(ip_list[s], ip_list[active_user -1]);
	}
	active_user--; 
	ct = time(NULL);			
	tm =*localtime(&ct);
	write(1, "\033[0G", 4);		
	fprintf(stderr, "\033[33m");
	printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("채팅 참가자 1명 탈퇴. 현재 참가자 수 = %d\n", active_user);
	fprintf(stderr, "\033[32m");
	fprintf(stderr, "server>"); 
}
