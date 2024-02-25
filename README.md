For running the code sample example is given below:
1)gcc -o s server.c -pthread
2)./s
then take a new terminal and do the following:
3)gcc -o a client.c -pthread
4)./a A
here A is just the name for the client (you can choose any according to your wish)
OPen a new terminal and type
5)gcc -o b client.c -pthread
4)./b B

You can type message in any client terminal and you can see the output

Working
--------
Client is sending the data to all other client in the network. For that client first send the data to server , and server will send the data to the corresponding client.

write(sock,client_name,strlen(client_name))  to send the msg to server
(fgets(msg,500,stdin)>0): eg we will write "hi" then hi is stored in msg and this msg is being send to server through write function.
In the same program a single client is able to send msg to sever using write and receive msg from server using recv because of multithreading.
client use pthread_create to create a thread that receive msg from server. and the main client will write /send msg to server.

AF_INET is the Internet address family for IPv4. SOCK_STREAM is the socket type for TCP,

=>struct socaddr is a general structure for all protocol but struct sockaddr_in is a structure specific for ipv4 address family.
=>Port 80 is the default port. It's what gets used when no port is specified. 8080 is Tomcat's default port so as not to interfere with any other web server that may be running.
=>htons:convert host byte order to network  byte order.
=>inet_addr converts an IPv4 address from a string in dotted decimal representation to an integer. 
