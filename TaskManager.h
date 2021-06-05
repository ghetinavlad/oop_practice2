#pragma once
#include "Controller.h"
#include <QtWidgets/QMainWindow>
#include "ui_TaskManager.h"
#include "Model.h"

class TaskManager : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    TaskManager(Model* idea_model, Controller& controller,  QWidget* parent = Q_NULLPTR);
    void update() override;

private:
    Ui::TaskManagerClass ui;
    Controller& controller;
    Model* idea_model;
    void connectSignals();

public slots:
    void add_task();
    void search_by_name();

};
