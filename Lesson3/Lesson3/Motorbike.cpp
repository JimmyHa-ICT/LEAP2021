#include "Motorbike.h"

Motorbike::Motorbike() : DynamicObject()
{
	strcpy(name, "Motorbike");
}

void Motorbike::Move()
{
	cout << "Ducati is running at 120 kmph" << endl;
}