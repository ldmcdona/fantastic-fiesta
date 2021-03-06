#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <time.h>

#define	 MY_PORT  2224

/* ---------------------------------------------------------------------
   This is a sample client program for the number server. The client and
   the server need to run on the same machine.
   --------------------------------------------------------------------- */

int main()
{
	int	s, number;
	int data[7]; //2 xy, 1 facing, 1 shooting, 1 time, 2 buffer
	struct	sockaddr_in	server;

	struct	hostent		*host;

	time_t * seconds;

	host = gethostbyname ("localhost");

	if (host == NULL) {
		perror ("Client: cannot get host description");
		exit (1);
	}


	s = socket (AF_INET, SOCK_STREAM, 0);

	if (s < 0) {
		perror ("Client: cannot open socket");
		exit (1);
	}

	bzero (&server, sizeof (server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons (MY_PORT);

	if (connect (s, (struct sockaddr*) & server, sizeof (server))) {
		perror ("Client: cannot connect to server");
		exit (1);
	}
	
	// Zero out all bytes in character array c
	bzero(data,7);
	
	data[0] = 5;
	data[1] = 5;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;

	// Send all 11 bytes of character array c to the server
	// It is important to note that even the null terminating (zero valued) bytes
	// are sent to the server. 
	send(s,c,7,0);

	// zero out each byte of the array before receiving from the server
	bzero(c,11);

	// Here the client wants to receive 7 bytes from the server, but the server
	// only sends 5 bytes
	recv(s,c,7,0);
	sleep(2);

	// Now we print out the character array to reveal that only 5 bytes were
	// received.
	printf("%s\n",c);
	close (s);
}
