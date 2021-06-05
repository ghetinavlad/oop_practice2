#pragma once
#include "controller.h"
#include <algorithm>
#include <fstream>

Controller::Controller(std::string taskFilePath) {
	this->taskFilePath = taskFilePath;
}

std::vector <Programmer> Controller::getAllProgrammers() {
	return this->elements.getAllProgrammers();
}

std::vector<Task> Controller::getAllTasks() {
	return this->elements.getAllTasks();
}

std::vector<Task> Controller::getAllTasksSorted() {
	std::vector<Task> allTasks = this->elements.getAllTasks();
	std::sort(allTasks.begin(), allTasks.end(), [this](const Task& a, const Task& b) {return a.getStatus() < b.getStatus(); });
	return allTasks;
}

int Controller::getAllProgrammersWithTask(int id) {
	int counter = 0;
	std::vector<Programmer> allProgrammers = this->elements.getAllProgrammers();
	for (auto programmer : allProgrammers) {
		if (programmer.getID() == id) {
			counter++;
		}
	}

	return counter;
}

Controller::~Controller() {
	if (taskFilePath.length() != 0) {
		this->updateFile(taskFilePath);
	}
}

void Controller::loadProgrammersFromFile(std::string filePath) {
	this->elements.loadProgrammersFromFile(filePath);
}

void Controller::loadTasksFromFile(std::string filePath) {
	this->elements.loadTasksFromFile(filePath);
}

void Controller::addTask(int id, std::string description , std::string status) {
	this->elements.addTask(Task(description, status, id));
	this->notify();
}

void Controller::addProgrammer(int id, std::string name) {
	this->elements.addProgrammer(Programmer(id, name));
	this->notify();
}


void Controller::updateFile(std::string filePath) {
	std::fstream outputStream(filePath);
	std::vector<Task> allTasks = this->elements.getAllTasks();

	for (auto task : allTasks) {
		outputStream << task.toString() << "\n";
	}

	outputStream.close();
}