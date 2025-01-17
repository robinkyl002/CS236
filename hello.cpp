
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

int main (int argc, char* argv[]) {

	// cout << "Hello" << endl;
	// cout << "argc: " <<  argc << endl;
	// cout << "argv[0]: " << argv[0] << endl;
	// cout << "argv[1]: " << argv[1] << endl;
	// cout << endl;


	// cout << "*** Start of Input ***" << endl;

	ifstream in;
	in.open(argv[1]);
	stringstream ss;
	ss << in.rdbuf();
	string input = ss.str();
	in.close();

	// cout << input << endl;

	// cout << "*** End of Input ***" << endl;
	int numCount = 0;
	int charCount = input.length();
	int letterCount = 0;
	int lineCount = 0;
	int spaceCount = 0;

	for (size_t i = 0; i < input.length(); i++) {

		if (isalpha(input[i])) {
			letterCount++;
		}
		if (isdigit(input[i])) {
			numCount++;
		}
		if (isspace(input[i])) {
			spaceCount++;
		}
		if (input[i] ==  '\n') {
			lineCount++;
		}
	}

	cout << "chars: " << charCount  << endl;
	cout << "lines: " << lineCount << endl;
	cout << "wspace: " << spaceCount << endl;
	cout << "digits: " << numCount << endl;
	cout << "letters: " << letterCount << endl;

}
