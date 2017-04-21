#include "../include/socketpp.hpp"
#include <cstdio>
#include <iostream>

#define BUF_SIZE 1024

int main(int argc, char * argv[])
{
	// Arguments lookup
	if (argc < 3) {
		printf("Usage: tcpserver <host> <port>\n");
		exit(-1); }
	else
		for (int i = 0; i < argc; i++)
			printf("Arg %d: %s\n", i, argv[i]);

	// Stuff
	Socket sock; // Default results in AF_INET and SOCK_STREAM.
	char buffer[BUF_SIZE];
	int nrecv;
	char ch;

	// Connects to whatever...
	if ( sock.connect( argv[1], std::stoi(argv[2]) ) ) {
		printf("Connected. Receiveing data...\n");
		// Receive data.
		nrecv = sock.recv(buffer, BUF_SIZE);
		// Check for errors: recv() returns -1 for error.
		if (recv < 0)
			printf("Error receiving data.\n");
		else {
			printf("Data received:\n");
			// Print valid data from the buffer.
			for (int i = 0; i < nrecv; i++)
				std::cout.put(buffer[i]);
		}
		sock.close();
	}
	else {
		printf("Failed to connect.\n");
		exit(-1);
	}

	printf("\nDone.\n");
	return 0;
}
