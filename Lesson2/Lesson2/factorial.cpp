#include "lesson2.h"
#include <iostream>

using namespace std;

void factorial()
{
	int n;
	cin >> n;

	unsigned long long result = 1;

	for (int i = 1; i <= n; i++)
		result *= i;

	cout << result << endl;
}