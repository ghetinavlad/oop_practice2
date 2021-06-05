#pragma once
#include <vector>
#include "Observer.h"
using namespace std;

class Subject
{

private:
	vector<Observer*> observers;
public:
	void add(Observer* observer);
	void notify();


};