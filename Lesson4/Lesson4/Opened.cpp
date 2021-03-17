#include "Locked.h"
#include "Closed.h"
#include "Opened.h"

Opened::Opened()
{
	cout << "Enter opened state" << endl;
}

Opened::~Opened()
{
	cout << "Exit opened state" << endl;
}

void Opened::Lock(Machine* m)
{
	cout << "You need to close the door first" << endl;
}

void Opened::Unlock(Machine* m)
{
	cout << "You need to lock the door first" << endl;
}

void Opened::Open(Machine* m)
{
	cout << "The door is already opened" << endl;
}

void Opened::Close(Machine* m)
{
	cout << "Closing the door" << endl;
	m->SetCurrent(new Closed());
	delete this;
}