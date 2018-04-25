//UDP echo client program
#include "header.h"

int main(int argc, char *argv[])	//three arguments to be checked later
{
	//Declare and define variables
	int s; 							//socket descriptor						//length of string to be echoed
	char* servName;					//server name
	int servPort;					//server port
	char* string;					//string to be echoed
	char buffer[256+1];				//data buffer
	struct sockaddr_in servAddr;	//server socket address
	
	//check and set program arguments
	if(argc < 4)
	{
		printf("Error: three arguments are needed");
		exit(1);
	}
	servName = argv[1];
	servPort = atoi(argv[2]);
	string = argv[3];
	
	
	//build server socket address
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, servName, &servAddr.sin_addr);
	servAddr.sin_port = htons(servPort);

	//create socket
	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error: socket failed!");
		exit(1);
	}
	
	//send echo string
	sendto(s, string, sizeof(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
	
	//receive echo string
	recvfrom(s, buffer, sizeof(buffer), 0, NULL, NULL);
	
	//print and verify echoed string
	buffer[strlen(buffer)] = '\0';
	
	fputs(buffer, stdout);
	 printf("\n");

	//close the socket
	close(s);
	
	//stop the program
	exit(0);
	
}// end of echo client program
