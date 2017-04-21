#include "../include/socketpp.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>

#define BUF_SIZE 1024

int main(int argc, char * argv[])
{
	/* Arguments lookup */
	if (argc < 3) {
		printf("Usage: tcpserver <host> <port>\n");
		exit(-1); }
	else
		for (int i = 0; i < argc; i++)
			printf("Arg %d: %s\n", i, argv[i]);

	/* Stuff we will work with */
	Socket sock;
	std::ifstream fin("foo.txt");
	char buffer[BUF_SIZE];
	int nread, nsend;
	char ch;

	/* Prepare the socket. Notice it is on blocking mode. */
	if ( sock.bind(argv[1], std::stoi(argv[2])) ) {
		printf("Binding successful.\n");
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

	/* Main loop. Listen for connections and send the content of foo.txt to them. */
	while(true) {
		if (sock.accept()) {
			printf("Connection acepted.\n");
			// Read chunck per chunk from the file into the buffer and send to client.
			do {
				for (nread = 0; nread < BUF_SIZE; nread++) {
					ch = fin.get();
					if (ch == EOF) break;
					buffer[nread] = ch;
				}
				sock.send(buffer, nread);
			} while (ch != EOF);
			// Close connection.
			sock.close();
		}
	}

	printf("\n --- Done ---\n");
	return 0;
}
