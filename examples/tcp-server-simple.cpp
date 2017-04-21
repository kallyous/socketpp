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
	Socket sock;
	int nsent;
	char msg[] = "Hello World!";

	// Bind the socket.
	if ( sock.bind(argv[1], std::stoi(argv[2])) ) {
		printf("Binding successful.\n");
		// Listen.
		if ( sock.listen() )
			printf("Listening...\n");
		else {
			printf("Failed to listen.\n");
			exit(-1);
		}
	}
	else {
		printf("Failed to bind.\n");
		exit(-1);
	}

	// Main loop
	while(true) {
		// Accept connection.
		if (sock.accept()) {
			printf("Connection acepted. Sending message...\n");
			// Send message.
			nsent = sock.send(msg, sizeof(msg));
			// Check for sending errors: send() returns -1 on errors.
			if (nsent < 0)
				printf("Error sending the message.\n");
			else
				printf("Message sent successfully. %d bytes sent.", nsent);
			// Close connection.
			sock.close();
		}
	}

	printf("Done.\n");
	return 0;
}
