#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "FordFulkerson.h"

int main() {

	setlocale(LC_ALL, "rus");
	ifstream f("in.txt", ios::in);
	Result(f);
	return 0;
}
