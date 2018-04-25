#include "header.h"

int main(int argc, char *argv[])
{
	//declare and define variables
	int s; 							//Socket descriptor (reference)						//Length of string to be echoed
	char buffer[256]; 				//data buffer 
	struct sockaddr_in servAddr;	//server(local) socket address
	struct sockaddr_in clntAddr;	//client(remote) socket address
	int clntAddrLen;				//length of client socket address
	int SERVER_PORT;
	char* mergString;

	if ( argc < 3)
	{
		printf("Error more arguments needed");
		exit(1);
	}

	SERVER_PORT = atoi(argv[1]);
	mergString = argv[2];

	memset(&servAddr, 0, sizeof(servAddr));		//allocate memory
	servAddr.sin_family = AF_INET;					//family field
	servAddr.sin_port = htons (SERVER_PORT);		//default port number
	servAddr.sin_addr.s_addr = htonl (INADDR_ANY);	//default IP address
	
	
	//create socket
	if((s = socket(PF_INET, SOCK_DGRAM, 0))< 0 )
	{
		perror ("Error: socket failed!");
		exit(1);
	}
	if((bind(s,(struct sockaddr*)&servAddr, sizeof(servAddr))) < 0) 
	{
		perror("bind error");
		exit(1);
	}
	for(;;) //Run forever
	{
		//Receive String
	recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&clntAddr, &clntAddrLen);
	
	sprintf(buffer, "%s %s", buffer, mergString);
	//Send string

	sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr));
	
	}	//end of loop

} //end of echo server program
