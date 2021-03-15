#pragma once
#pragma once
#include <iostream>
#include "DynamicObject.h"

using namespace std;

class Car : public DynamicObject
{
public:
	Car();
	void Move();
};