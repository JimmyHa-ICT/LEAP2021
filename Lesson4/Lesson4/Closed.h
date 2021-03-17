#pragma once
#include "State.h"

class Closed : public State
{
public:
	Closed();
	~Closed();
	void Lock(Machine* m);
	void Unlock(Machine* m);
	void Open(Machine* m);
	void Close(Machine* m);
};