#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 6667

int socketfd = 0;
struct sockaddr_in serverAddr;
char buffer[1024] = {0};
char *hostname = "irc.freenode.net";


int main(int argc, char const *argv[]){
 if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
	printf("Socket failed\n");
	 
	return -1;
 }

 printf("socket created suckesfully \n"); 

 char hostaddress[100];
 struct hostent *he;
 struct in_addr **addresslist;
 int i = 0;

 if((he = gethostbyname(hostname)) == NULL){
 	printf("error getting host address");
	return -1;
 }

 printf("host name resolved\n");

 addresslist = (struct in_addr **)he->h_addr_list;

 for(i = 0; addresslist[i] != NULL; i++){
	strcpy(hostaddress, inet_ntoa(*addresslist[i]));
 }

 printf("Recieved first valid host address %s\n", hostaddress);


 memset(&serverAddr, '0', sizeof(serverAddr));

 serverAddr.sin_family = AF_INET;
 serverAddr.sin_port = htons(PORT);

 if(inet_pton(AF_INET, hostaddress, &serverAddr.sin_addr)<=0){
	printf("Failed to allocate address");
	return -1;
 } 

 printf("Allocating socket address, success\n");



 if(connect(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
	printf("Connection failed\n");
 	return -1;
 } 

 printf("Socket connected\n");

 return 0;
}
