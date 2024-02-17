#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include <netinet/in.h>
pthread_mutex_t mutex;
int clients[20];
int n=0;
void sendtoall(char*msg,int cur)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0;i<n;i++)
	{
		if(clients[i]!=cur)
		{
			
			if(send(clients[i],msg,strlen(msg)
			,0)<0)
			{
				printf("Sending failed");
				continue;
				}
		}
	}
	pthread_mutex_unlock(&mutex);
}
void * recvmg(void * client_sock)
{
	int sock=*((int*)client_sock);
	printf("my_sock=%d\n",sock);
	char msg[500];
	int len=0;
	while((len=recv(sock,msg,500,0))>0)
	{
		msg[len]='\0';
		puts(msg);
		sendtoall(msg,sock);
	}
	printf("len=%d\n",len);
	
}
int main()
{
	struct sockaddr_in Serverip;
	pthread_t recvt;
	int sock=0,client_sock=0;
	
	
	Serverip.sin_family=AF_INET;
	Serverip.sin_port=htons(8080);
	Serverip.sin_addr.s_addr=inet_addr("127.0.0.1");
	sock=socket(AF_INET,SOCK_STREAM,0);
	//printf("%d\n",sock);
	if(bind(sock,(struct sockaddr*)&Serverip,sizeof(Serverip))==-1)
	printf("Error in binding\n");
	else
		printf("Server started\n");
	if(listen(sock,20)==-1)
	printf("\nListening failed\n");
	while(1)
	{
		if((client_sock=accept(sock,(struct sockaddr*)NULL,NULL))<0)
		{
		printf("Accept failed\n");
		}
		pthread_mutex_lock(&mutex);
		clients[n]=client_sock;
		n=n+1;
		printf("n=%d,client_sock=%d\n",n,client_sock);
		
		pthread_create(&recvt,NULL,(void *)recvmg,&client_sock);
		pthread_mutex_unlock(&mutex);
		
		
	}
	return 0;
}

