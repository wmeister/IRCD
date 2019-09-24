#include <string>
#include <cstring>
#include <vector>
#include "strvec.h"

using namespace std;

namespace strvec {
	vector<string> split_on_spaces(string str)
	{
		vector<string> words;
		string word = "";

		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ')
			{
				if (word != "")
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

		if (word != "")
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
}