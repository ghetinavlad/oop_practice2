#include "Subject.h"

void Subject::add(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::notify()
{

	for (auto observer : this->observers)
	{
		observer->update();
	}
}