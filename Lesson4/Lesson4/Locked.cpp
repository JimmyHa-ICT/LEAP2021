#include "Locked.h"
#include "Closed.h"
#include "Opened.h"

Locked::Locked()
{
	cout << "Enter locked state" << endl;
}

Locked::~Locked()
{
	cout << "Exit locked state" << endl;
}

void Locked::Lock(Machine *m)
{
	cout << "Already in lock state" << endl;
}

void Locked::Unlock(Machine *m)
{
	cout << "Unlocking the door" << endl;
	m->SetCurrent(new Closed());
	delete this;
}

void Locked::Open(Machine* m)
{
	cout << "You need to unlock first" << endl;
}

void Locked::Close(Machine* m)
{
	cout << "You need to unlock first" << endl;
}