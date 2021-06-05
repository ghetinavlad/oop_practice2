#pragma once
#include "repository.h"
#include "Subject.h"
#include <vector>

class Controller : public Subject {
private:
	Repository elements;
	std::string taskFilePath;

public:
	Controller(std::string taskFilePath);
	std::vector<Programmer> getAllProgrammers();
	std::vector<Task> getAllTasks();
	std::vector<Task> getAllTasksSorted();
	~Controller();
	void loadProgrammersFromFile(std::string filePath);
	void loadTasksFromFile(std::string filePath);
	void addTask(int id, std::string description, std::string status);
	void addProgrammer(int id, std::string name);
	int getAllProgrammersWithTask(int id);
	
	void updateFile(std::string filePath);
};
