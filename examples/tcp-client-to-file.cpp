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
	std::ofstream fout("output.txt");
	char buffer[BUF_SIZE];
	int nrecv, nsend;
	char ch;

	if ( sock.connect( argv[1], std::stoi(argv[2]) ) ) {
		printf("Connected. Receiveing data...\n");
		do {
			nrecv = sock.recv(buffer, BUF_SIZE);
			for (int i = 0; i < nrecv; i++)
				fout.put(buffer[i]);
		} while(nrecv > 0);
		fout.close();
	}
	else {
		printf("Failed to connect.\n");
		exit(-1);
	}

	printf("\n --- Done. ---\n");
	return 0;
}
