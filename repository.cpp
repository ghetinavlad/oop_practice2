#include "repository.h"
#include <fstream>

Repository::Repository() {
	;
}

std::vector <Programmer> Repository::getAllProgrammers() {
	return this->programmers;
}

std::vector<Task> Repository::getAllTasks() {
	return this->tasks;
}

void Repository::loadProgrammersFromFile(std::string filePath) {
	const int NAME_POSITION = 0;

	std::fstream inputStream(filePath);
	std::string currentLine;

	std::string name;
	int ID;

	this->programmers.clear();

	while (std::getline(inputStream, currentLine)) {
		int separatorPosition = currentLine.find("|");
		int propertyPosition = 0;

		while (separatorPosition != std::string::npos) {
			// subtract 1 from the separator position because there is a space between the property and the separator;
			// this substr will stop just before "separatorPosition - 1" => it will include the entire property
			// and nothing else
			std::string currentProperty = currentLine.substr(0, separatorPosition - 1);

			// add 2 to the separator position because there is a space between the separator and the next property
			// we then subtract 1 from "currentLine.length() - separatorPosition" in order to avoid that space
			currentLine = currentLine.substr(separatorPosition + 2, currentLine.length() - separatorPosition - 1);
			separatorPosition = currentLine.find("|");

			if (propertyPosition == NAME_POSITION) {
				name = currentProperty;
			}
			propertyPosition++;
		}

		// the last property remains outside the while loop, we treat it separately
		ID = stoi(currentLine);

		this->programmers.push_back(Programmer(ID, name));
	}

	inputStream.close();
}

void Repository::loadTasksFromFile(std::string filePath) {
	const int DESCRIPTION_POSITION = 0;
	const int STATUS_POSITION = 1;

	std::fstream inputStream(filePath);
	std::string currentLine;

	std::string description;
	std::string status;
	int ID;

	this->tasks.clear();

	while (std::getline(inputStream, currentLine)) {
		int separatorPosition = currentLine.find("|");
		int propertyPosition = 0;

		while (separatorPosition != std::string::npos) {
			// subtract 1 from the separator position because there is a space between the property and the separator;
			// this substr will stop just before "separatorPosition - 1" => it will include the entire property
			// and nothing else
			std::string currentProperty = currentLine.substr(0, separatorPosition - 1);

			// add 2 to the separator position because there is a space between the separator and the next property
			// we then subtract 1 from "currentLine.length() - separatorPosition" in order to avoid that space
			currentLine = currentLine.substr(separatorPosition + 2, currentLine.length() - separatorPosition - 1);
			separatorPosition = currentLine.find("|");

			if (propertyPosition == DESCRIPTION_POSITION) {
				description = currentProperty;
			}
			else if (propertyPosition == STATUS_POSITION) {
				status = currentProperty;
			}

			propertyPosition++;
		}

		// the last property remains outside the while loop, we treat it separately
		if (currentLine.length() == 0) {
			ID = UNASSIGNED_PROGRAMMER;
		}
		else {
			ID = stoi(currentLine);
		}

		this->tasks.push_back(Task(description, status, ID));
	}

	inputStream.close();
}

void Repository::addTask(Task newTask) {
	if (newTask.getDescription() == "" || (newTask.getStatus() != "open" && newTask.getStatus() != "inprogress" && newTask.getStatus() != "closed")) {
		throw std::exception("description or status");
	}


	for (auto task : this->tasks) {
		if (task.getID() == newTask.getID()) {
			throw std::exception("Task already exists");
		}
	}

	this->tasks.push_back(newTask);
}

void Repository::addProgrammer(Programmer newProgrammer) {
	this->programmers.push_back(newProgrammer);
}


Repository::~Repository() {
	;
}