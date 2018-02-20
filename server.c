#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

#define	MY_PORT	2224

/* ---------------------------------------------------------------------
   This	is  a sample server which opens a stream socket and then awaits
   requests coming from client processes.
   --------------------------------------------------------------------- */

int main(int argc, char * argv[])
{
	int	sock, snew, fromlength, number, outnum;

	struct	sockaddr_in	master, from;
	char c[11];


	int i = 0;

	sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror ("Server: cannot open master socket");
		exit (1);
	}

	master.sin_family = AF_INET;
	master.sin_addr.s_addr = inet_addr("127.0.0.1");
	master.sin_port = htons (MY_PORT);

	if (bind (sock, (struct sockaddr*) &master, sizeof (master))) {
		perror ("Server: cannot bind master socket");
		exit (1);
	}

	listen (sock, 5);
	fromlength = sizeof (from);
	snew = accept (sock, (struct sockaddr*) & from, & fromlength);
	if (snew < 0) {
		perror ("Server: accept failed");
		exit (1);
	}
	outnum = htonl (number);
	
	// Zero out all of the bytes in character array c
	bzero(c,11);

	// Here we print off the values of character array c to show that
	// each byte has an intial value of zero before receiving anything
	// from the client.
	printf("Before recieving from client\n--------------------------\n");
	printf("Character array c has the following byte values:\n");
	for (i = 0; i < 11; i++){
		printf("c[%d] = %d\n",i,c[i]);
	}

	// Now we receive from the client, we specify that we would like 11 bytes
	recv(snew,c,11,0);

	// Print off the received bytes from the client as a string. 
	// Next, print off the value of each byte to showcase that indeed
	// 11 bytes were received from the client
	printf("\nAfter receiving from client\n-------------------------\n");
	printf("Printing character array c as a string is: %s\n",c);
	printf("Character array c has the following byte values:\n");
	for (i = 0; i < 11; i++){
		printf("c[%d] = %d\n",i,c[i]);
	}

	//copy the string "Stevens" into character array c
	strncpy(c,"Stevens",7);
	
	//Send the first five bytes of character array c back to the client
	//The client, however, wants to receive 7 bytes.
	send(snew,c,5,0);

	close (snew);
	sleep(1);
}
