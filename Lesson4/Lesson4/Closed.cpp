#include "Locked.h"
#include "Closed.h"
#include "Opened.h"

Closed::Closed()
{
	cout << "Enter closed state" << endl;
}

Closed::~Closed()
{
	cout << "Exit closed state" << endl;
}

void Closed::Lock(Machine* m)
{
	cout << "Locking the door" << endl;
	m->SetCurrent(new Locked());
	delete this;
}

void Closed::Unlock(Machine* m)
{
	cout << "The door is currently unlocked" << endl;
}

void Closed::Open(Machine* m)
{
	cout << "Opening the door" << endl;
	m->SetCurrent(new Opened());
	delete this;
}

void Closed::Close(Machine* m)
{
	cout << "You need to open the door first" << endl;
}