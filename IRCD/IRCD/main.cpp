#include <string>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct message
{
	string host;
	string command;
	vector<string> arguments;
};

vector<string> split_on_spaces(string str)
{
    vector<string> words;
    string word = "";

    for(int i=0; i < str.length(); i++)
    {
        if(str[i] == ' ')
        {
          if(word != "")
          {
              words.push_back(word);
              word = "";
          }
        }
        else
        {
            word += str[i];
        }
    }

    if(word != "")
        words.push_back(word);

    return words;
}

vector<string> split_once(string str, string seperator)
{
	string first, second;

	first = strtok((char*)str.c_str(), seperator.c_str());
	second = strtok(NULL, seperator.c_str());

	char* tok;
	while ((tok = strtok(NULL, seperator.c_str())) != NULL)
	{
		second += ' ';
		second += tok;
	}

	vector<string> result;
	result.push_back(first);
	result.push_back(second);

	return result;
}
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
		prefix = pair[0];
		s = pair[1];
		cout << "prefix=" << prefix << endl;
		cout << "s=" << s << endl;

	}
	if (s.find(' :') != string::npos)
	{
		string trailing;

		vector<string> pair = split_once(s, " :");
		s = pair[0];
		trailing = pair[1];
		//vector<string> args = split_on_spaces(s);
	}
	message x;
	return x;
}

int main()
{
    vector<string> words = split_on_spaces("hello    world whatup");
    cout << words.size();
    cout << words[0] << endl << words[1] << endl << words[2] << endl;
	//parse_msg(":test!~test@test.com PRIVMSG #channel :Hi!");
	//=================
	char* foo;
	gets(foo);
	//=================
	return 0;
}
