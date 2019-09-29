#pragma once
#include <string>
#include <vector>

using namespace std;

namespace irc {
	struct message
	{
		string host;
		string command;
		vector<string> arguments;
	};
	message parse_msg(string s);
}