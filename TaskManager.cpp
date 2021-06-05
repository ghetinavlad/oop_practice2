#include "TaskManager.h"
#include <qmessagebox.h>
#include <qboxlayout.h>
#include <algorithm>

TaskManager::TaskManager(Model* idea_model, Controller& controller,QWidget* parent)
    : controller{ controller }, idea_model{ idea_model }, QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString("Task Manager"));
    this->connectSignals();
    this->ui.tableView->setModel(idea_model);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void TaskManager::update()
{
}

void TaskManager::connectSignals()
{
	QObject::connect(this->ui.pushButton, &QPushButton::clicked, this, &TaskManager::add_task);
	QObject::connect(this->ui.prgName_line_edit, &QLineEdit::textChanged, this, &TaskManager::search_by_name);
	
}

void TaskManager::add_task()
{
	try
	{
		int id = std::stoi(this->ui.id_line_edit->text().toStdString());
		std::string description = this->ui.dscr_line_edit->text().toStdString();
		std::string status = this->ui.status_line_edit->text().toStdString();

		std::string prg1 = this->ui.prg1_line_edit->text().toStdString();
		std::string prg2 = this->ui.prg2_line_edit->text().toStdString();
		std::string prg3 = this->ui.prg3_line_edit->text().toStdString();
		std::string prg4 = this->ui.prg4_line_edit->text().toStdString();



		try {
			this->controller.addTask(id, description, status);
			this->controller.updateFile("tasks.txt");
			if (prg1 != "")
				this->controller.addProgrammer(id, prg1);
			if (prg2 != "")
				this->controller.addProgrammer(id, prg2);
			if (prg3 != "")
				this->controller.addProgrammer(id, prg3);
			if (prg4 != "")
				this->controller.addProgrammer(id, prg4);
		}
		catch (const std::exception& exception)
		{
			QMessageBox::critical(this, "Error", "Invalid Input!");

		}
		this->idea_model->insert_row();
		emit this->idea_model->dataChanged(this->idea_model->index(0, 0), this->idea_model->index(this->controller.getAllTasks().size() + 1, 3));
	}
	catch (const std::exception& exception)
	{
		QMessageBox::critical(this, "Error", "Invalid Input!");

	}
}

void TaskManager::search_by_name()
{

	std::string prgName = this->ui.prgName_line_edit->text().toStdString();

	std::vector<Programmer> allProgrammers = this->controller.getAllProgrammers();
	std::vector<int> tasksId;

	for (auto programmer : allProgrammers) {
		if (programmer.getName().find(prgName) != string::npos) {
			tasksId.push_back(programmer.getID());
		}
	}

	std::vector<Task> allTasks = this->controller.getAllTasksSorted();

	int i = 0;
	for (auto task : allTasks) {
		if (std::find(tasksId.begin(), tasksId.end(), task.getID()) != tasksId.end()) {
			this->ui.tableView->showRow(i);
		}
		else {
			this->ui.tableView->hideRow(i);
		}
	  i++;
	}

	

}
