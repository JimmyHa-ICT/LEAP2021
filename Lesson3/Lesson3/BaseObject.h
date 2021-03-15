#pragma once
#include <iostream>

using namespace std;

class BaseObject {
protected:
	int id = 1;
	char name[50];
	pair<int, int> position;

public:
	BaseObject();

	virtual ~BaseObject();

	char* GetName();

	int GetId();

	void PrintPosition();

	virtual void Move();
};