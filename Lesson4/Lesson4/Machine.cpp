#include "Machine.h"
#include "Locked.h"

Machine::Machine()
{
	current = new Locked();
}

void Machine::SetCurrent(State *s)
{
	current = s;
}

void Machine::Lock()
{
	current->Lock(this);
}

void Machine::Close()
{
	current->Close(this);
}

void Machine::Open()
{
	current->Open(this);
}

void Machine::Unlock()
{
	current->Unlock(this);
}