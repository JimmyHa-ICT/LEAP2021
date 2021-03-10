#include "lesson2.h"
#include <iostream>

using namespace std;

void prompt_input()
{
	int n;

	do {
		cout << "Enter a positive integer: ";
		cin >> n;
	} while (n <= 0);
}