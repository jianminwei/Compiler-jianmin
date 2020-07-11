#include <iostream>
#include <sstream>
#include <string>
//#include "calcex.h"
#include "calculator.h"

using namespace std;

Calculator* calc;

int main(int argc, char* argv[]) {
	string line;

	try{

	cout << "Please enter a calculator expression: ";

	getline(cin, line);

	calc = new Calculator();

	int result = calc->eval(line);

	cout << "The result is " << result << endl;

	delete calc;

	}
		catch(std::exception ex) {
		cout << "Program Aborted due to exception!" << endl;
	}
}
