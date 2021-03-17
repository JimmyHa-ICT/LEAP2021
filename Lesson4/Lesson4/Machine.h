#pragma once
#include <iostream>

using namespace std;

class Machine
{
private:
	class State* current;
public:
	Machine();
	void SetCurrent(State* s);

	void Lock();
	void Unlock();
	void Open();
	void Close();
};