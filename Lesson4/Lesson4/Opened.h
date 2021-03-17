#pragma once
#include "State.h"

class Opened : public State
{
public:
	Opened();
	~Opened();
	void Lock(Machine* m);
	void Unlock(Machine* m);
	void Open(Machine* m);
	void Close(Machine* m);
};