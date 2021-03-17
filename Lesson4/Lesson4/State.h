#pragma once
#include <iostream>
#include "Machine.h"

using namespace std;

class State
{
public:
	virtual void Lock(Machine *m) = 0;
	virtual void Unlock(Machine *m) = 0;
	virtual void Open(Machine *m) = 0;
	virtual void Close(Machine *m) = 0;
};