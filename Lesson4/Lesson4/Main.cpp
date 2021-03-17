#include <iostream>
#include "Locked.h"
#include "Closed.h"
#include "Opened.h"


using namespace std;

void ShowMenu()
{
	cout << "0. Locked" << endl;
	cout << "1. Unlocked" << endl;
	cout << "2. Opened" << endl;
	cout << "3. Closed" << endl;
	cout << "4. Exit" << endl;
}

int main()
{
	void (Machine:: * ptrs[])() =
	{
		&Machine::Lock, &Machine::Unlock, &Machine::Open, &Machine::Close
	};

	Machine fsm;
	int num = 0;
	while (1)
	{
		ShowMenu();
		cout << "Enter option: ";
		cin >> num;
		if (num == 4)
			break;

		(fsm.*ptrs[num])();
	}

	return 0;
}