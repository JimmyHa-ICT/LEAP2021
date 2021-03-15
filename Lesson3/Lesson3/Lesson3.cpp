// Lesson3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Dependences.h"
#include <vld.h>

using namespace std;

int main()
{
    vector<BaseObject*> listObj;

    listObj.push_back(new Tree());
    listObj.push_back(new House());
    listObj.push_back(new Motorbike());
    listObj.push_back(new Car());

    for (auto obj : listObj)
    {
        cout << obj->GetName() << endl;
    }

    cout << endl;

    for (auto obj : listObj)
    {
        obj->Move();
    }

    cout << endl;

    for (auto obj : listObj)
    {
        obj->PrintPosition();
        cout << endl;
    }

    for (auto obj : listObj)
    {
        delete(obj);
    }

    listObj.clear();

}

