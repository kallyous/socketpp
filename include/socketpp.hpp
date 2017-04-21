#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>


class Socket
{
  private:
	int socket_type, address_family, port_number, ip_proto;
	int self_fd, other_fd; // File descriptors
	int yes = 1;
	unsigned int sockaddrin_size = sizeof(struct sockaddr_in);
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
  public:
	Socket(); // Same as Socket(AF_INET, SOCK_STREAM)
	Socket(int addr_family, int sock_type);
	bool bind(char * host, int port);
	bool listen(int);
	bool accept();
	bool connect(char * host, int port);
	int recv(char * buf, int buf_length);
	int send(char * buf, int buf_length);
	int recvFrom(char * buf, int buf_length);
	int sendTo(char * buf, int buf_length);
	void close();
	bool setsockopt(int sock_lvl, int opt_name, int opt_val);
	void setnonblocking(bool val);
};

// Default constructor
Socket::Socket()
{
	socket_type = SOCK_STREAM;
	address_family = AF_INET;
	ip_proto = IPPROTO_TCP;
	port_number = 0;
	other_fd = -1;
	self_fd = socket(address_family, socket_type, ip_proto);
	::setsockopt(self_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	// TODO: implement some error message in case self_fd comes as -1
}

// Main constructor
Socket::Socket(int addr_family, int sock_type)
{
	socket_type = sock_type;
	address_family = addr_family;
	if (socket_type == SOCK_DGRAM) ip_proto = IPPROTO_UDP;
	else if (socket_type == SOCK_STREAM) ip_proto = IPPROTO_TCP;
	else ip_proto = 0;
	port_number = 0;
	other_fd = -1;
	self_fd = socket(address_family, socket_type, ip_proto);
	::setsockopt(self_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	// TODO: implement some error message in case self_fd comes as -1
}

// Bind method
bool Socket::bind(char * host, int port)
{
	port_number = port;
	memset( &local_addr, 0, sizeof(local_addr) );
	local_addr.sin_family = address_family;
	local_addr.sin_port = htons(port_number);
	local_addr.sin_addr.s_addr = inet_addr(host);
	if (::bind( self_fd, (struct sockaddr *)&local_addr, sizeof local_addr ) != -1)
		return true;
	else
		return false;
	// TODO: implement error message
}


// Listen method
bool Socket::listen(int cli=4)
{
	if (::listen(self_fd, cli) != -1)
		return true;
	else
		return false;
	// TODO: implement error message
}

// Accept method
bool Socket::accept()
{
	other_fd = ::accept( self_fd, (struct sockaddr *)&remote_addr, &sockaddrin_size );
	if ( other_fd != -1)
		return true;
	else
		return false;
	// TODO: implement error message
}

// Send method
int Socket::send(char * buf, int buf_length)
{
	return ::send(other_fd, buf, buf_length, 0);
	// TODO: error message
}

// Receive method
int Socket::recv(char * buf, int buf_length)
{
	return ::recv(self_fd, buf, buf_length, 0);
	// TODO: error message
}

// Receive From method
int Socket::recvFrom(char * buf, int buf_length)
{
	return ::recvfrom();
}

// Connect method
bool Socket::connect(char * host, int port)
{
	int res;
	memset( &remote_addr, 0, sizeof(remote_addr) );

	remote_addr.sin_family = address_family;
	remote_addr.sin_port = htons(port);
	//inet_pton(address_family, host, &remote_addr.sin_addr);
	remote_addr.sin_addr.s_addr = inet_addr(host);

	res = ::connect(self_fd, (struct sockaddr *)&remote_addr, sizeof(remote_addr));

	if (res == 0)
		return true;
	else
		return false;
	// TODO: error message
}

// Close method
void Socket::close()
{
	::close(other_fd);
}

// Set Socket Option method
bool Socket::setsockopt(int sock_lvl, int opt_name, int opt_val)
{
	return (::setsockopt(self_fd, sock_lvl, opt_name, &opt_val, sizeof(int)) == 0);
}

// Set Blocking / Non Blocking flag method
void Socket::setnonblocking(bool val)
{
	int flags;
	// Set to non-blocking
	flags = fcntl(self_fd, F_GETFL, 0);
	// TODO: fcntl() return -1 in case of error, this should be handled.
	if (val == true)
		fcntl(self_fd, F_SETFL, flags | O_NONBLOCK);
		// TODO: same -1 to handle here
	else
		fcntl(self_fd, F_SETFL, flags & (~O_NONBLOCK));
		// TODO: and here too.
}
