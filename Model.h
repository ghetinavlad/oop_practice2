#pragma once
#include <qabstractitemmodel.h>
#include "Controller.h"
#include <qfont.h>
#include <qdebug.h>
#include <qcolor.h>
#include <qbrush.h>

class Model :
	public QAbstractTableModel
{
private:
	Controller& controller;

public:
	Model(Controller& controller, QObject* parent = NULL) :controller{ controller } {}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void insert_row();



};