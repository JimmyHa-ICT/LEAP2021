#include "Car.h"

Car::Car() : DynamicObject()
{
	strcpy(name, "Car");
}

void Car::Move()
{
	cout << "Roll Royce is running at 320 kmph" << endl;
}