#include "TaskManager.h"
#include <QtWidgets/QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller actionController("tasks.txt");
    actionController.loadProgrammersFromFile("programmers.txt");
    actionController.loadTasksFromFile("tasks.txt");

    Model* idea_model = new Model(actionController);

    std::vector<TaskManager*> windows;
 
    int i = 0;
    TaskManager* taskmanager = new TaskManager(idea_model, actionController);
    windows.push_back(taskmanager);
    actionController.add(taskmanager);
    windows[i]->show();
    i++;
    return a.exec();
}
