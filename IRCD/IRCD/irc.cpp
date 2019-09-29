#include "irc.h"
#include <string>
#include <vector>
#include "strvec.h"

using namespace std;
using namespace strvec;

namespace irc {
	/*
	def parsemsg(s):
		"""Breaks a message from an IRC server into its prefix, command, and arguments.
		"""
		prefix = ''
		trailing = []
		if not s:
		   raise IRCBadMessage("Empty line.")
		if s[0] == ':':
			prefix, s = s[1:].split(' ', 1)
		if s.find(' :') != -1:
			s, trailing = s.split(' :', 1)
			args = s.split()
			args.append(trailing)
		else:
			args = s.split()
		command = args.pop(0)
		return prefix, command, args

	parsemsg(":test!~test@test.com PRIVMSG #channel :Hi!")
	# ('test!~test@test.com', 'PRIVMSG', ['#channel', 'Hi!'])
	*/
	message parse_msg(string s)
	{
		string prefix = "";
		vector<string> args;

		if (s == "")
		{
			throw("Empty line.");
		}
		if (s[0] == ':')
		{
			string tail = s.substr(1);
			vector<string> pair = split_once(tail, " ");
			prefix = pair[0]; // XXX there might be a bug here look at python code
			s = pair[1];
		}
		if (s.find(" :") != string::npos)
		{
			string trailing;

			vector<string> pair = split_once(s, " :");
			s = pair[0];
			trailing = pair[1];
			args = split_on_spaces(s);

			// deviation from original python function
			//vector<string> trail = split_once(trailing, " ");
			//args.push_back(trail[0]);
			//args.push_back(trail[1]);
			vector<string> trail = split_on_spaces(trailing);
			args.insert(args.end(), trail.begin(), trail.end());
		}
		else
		{
			args = split_on_spaces(s);
		}

		message msg;

		msg.command = args[0];
		args.erase(args.begin());
		msg.host = prefix;
		msg.arguments = args;

		return msg;
	}
}