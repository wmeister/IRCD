#pragma once
#include <string>
#include <vector>

using namespace std;

namespace strvec {
	vector<string> split_on_spaces(string);
	vector<string> split_once(string, string);
}