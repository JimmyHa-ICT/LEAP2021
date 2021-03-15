#include <iostream>
#include "BaseObject.h"

using namespace std;

BaseObject::BaseObject() {}

BaseObject::~BaseObject() {}

char* BaseObject::GetName()
{
	return name;
}

int BaseObject::GetId()
{
	return id;
}

void BaseObject::PrintPosition()
{
	cout << "(" << position.first << ", " << position.second << ")";
}

void BaseObject::Move()
{
	cout << "Base object moves!" << endl;
}