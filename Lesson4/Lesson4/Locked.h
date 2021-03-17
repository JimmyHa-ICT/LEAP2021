#pragma once
#include "State.h"

class Locked : public State
{
public:
	Locked();
	~Locked();
	void Lock(Machine *m);
	void Unlock(Machine *m);
	void Open(Machine *m);
	void Close(Machine *m);
};