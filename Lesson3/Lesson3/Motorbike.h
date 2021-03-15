#pragma once
#include <iostream>
#include "DynamicObject.h"

using namespace std;

class Motorbike : public DynamicObject
{
public:
	Motorbike();
	void Move();
};