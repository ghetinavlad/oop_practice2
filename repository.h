#pragma once
#include <vector>
#include "domain.h"
//#include "CustomException.h"

class Repository {
private:
	std::vector <Programmer> programmers;
	std::vector <Task> tasks;

public:
	Repository();
	std::vector <Programmer> getAllProgrammers();
	std::vector <Task> getAllTasks();
	void loadProgrammersFromFile(std::string filePath);
	void loadTasksFromFile(std::string filePath);
	void addTask(Task newTask);
	void addProgrammer(Programmer newProgrammer);
	
	~Repository();
};