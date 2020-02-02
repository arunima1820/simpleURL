#include <iostream>
#include <string>
#include "parse.h"

using namespace std;

int main(int argc, char *argv[]) {
	std::cout << "Enter URL: \t";
	string url;
	cin >> url;
	cout << endl;

	parse p(url);

}