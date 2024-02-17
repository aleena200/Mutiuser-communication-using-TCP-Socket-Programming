#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include <netinet/in.h>
char msg[500];
void * recvmg(void * my_sock)
{
	int sock=*((int *)my_sock);
	int len=0;
	
	while((len=recv(sock,msg,500,0))>0)
	{
		//printf("%d\n",len);
		msg[len]='\0';
		fputs(msg,stdout);
	}
	
}
int main(int argc,char * argv[])
{
	int sock,len;
	pthread_t recvt;
	char msg2[500];
	char client_name[20];
	if(argc<2)
	{
		printf("Argument less than 2\n");
	}
	strcpy(client_name,argv[1]);
	struct sockaddr_in Serverip;
	sock=socket(AF_INET,SOCK_STREAM,0);
	Serverip.sin_family=AF_INET;
	Serverip.sin_port=htons(8080);
	Serverip.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sock,(struct sockaddr*)&Serverip,sizeof(Serverip))==-1)
		printf("connection failed\n");
	pthread_create(&recvt,NULL,(void*)recvmg,&sock);
	while(fgets(msg,500,stdin)>0)
	{
		//puts(msg);
		strcpy(msg2,client_name);
		strcat(msg2,":");
		strcat(msg2,msg);
		//puts(msg2);
		len=write(sock,msg2,strlen(msg2));
		
		if(len<0)
		printf("Msg not send\n");
		
	}
	pthread_join(recvt,NULL);
	close(sock);
	return 0;
	
}

