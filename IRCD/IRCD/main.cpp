#include <iostream>
#include <cstring>
#include "irc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include "strvec.h"

using namespace std;
using namespace irc;
using namespace strvec;

void error(const char* msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char* argv[])
{
	const int PORT = 6667;
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char*)& serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);
	if (bind(sockfd, (struct sockaddr*) & serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,
		(struct sockaddr*) & cli_addr,
		&clilen);
	if (newsockfd < 0)
		error("ERROR on accept");
	for (;;)
	{

		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		if (n < 0) error("ERROR reading from socket");
		printf("Here is the message: %s\n", buffer);

		//message msg = parse_msg(":test!~test@test.com PRIVMSG #channel :Hi!");
		string msgs = buffer;
		cout << "size=" << msgs.size() << endl;
		cout << "found=" << msgs.find("\r\n") << endl;

		if (msgs.find("\r\n") != string::npos && msgs.find("\r\n") != (msgs.size() - 2))
		{
			vector<string> lines = split_once(msgs, "\r\n");
			for (auto line : lines)
			{
				message msg = parse_msg(line);
				cout << "msg.host=" << msg.host << endl;
				cout << "msg.command=" << msg.command << endl;
				cout << "msg.arguments=[";
				for (auto s : msg.arguments)
				{
					cout << s << ",";
				}
				cout << "]" << endl;
			}
		}
		else
		{
			message msg = parse_msg(buffer);
			cout << "msg.host=" << msg.host << endl;
			cout << "msg.command=" << msg.command << endl;
			cout << "msg.arguments=[";
			for (auto s : msg.arguments)
			{
				cout << s << ",";
			}
			cout << "]" << endl;
		}
		
		//=================
		//char* foo;
		//gets(foo);
		//=================
	}
	n = write(newsockfd, "I got your message", 18);
	if (n < 0) error("ERROR writing to socket");
	close(newsockfd);
	close(sockfd);

	return 0;
}
