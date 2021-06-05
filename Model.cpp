#include "Model.h"

int Model::rowCount(const QModelIndex& parent) const
{

	return controller.getAllTasks().size() + 1;
}

int Model::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
	int line = index.row();
	int column = index.column();

	if (line == rowCount() - 1)
	{
		return QVariant();
	}

	Task task = this->controller.getAllTasksSorted().at(line);
	int prgCnt = this->controller.getAllProgrammersWithTask(task.getID());

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if (column == 0)
		{
			return QString::fromStdString(std::to_string(task.getID()));
		}
		else if (column == 1)
		{
			return QString::fromStdString(task.getDescription());
		}

		else if (column == 2)
		{
			return QString::fromStdString(task.getStatus());
		}

		else if (column == 3)
		{
			return QString::fromStdString(std::to_string(prgCnt));
		}
		

	}
	
	return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section)
		{
		case 0:
			return QString::fromStdString("ID");
		case 1:
			return QString::fromStdString("Description");
		case 2:
			return QString::fromStdString("Status");
		case 3:
			return QString::fromStdString("Prg Cnt");
		default:
			break;
		}
	}

	return QVariant();
}

void Model::insert_row()
{
	beginInsertRows(QModelIndex(), this->controller.getAllTasks().size(), this->controller.getAllTasks().size());
	endInsertRows();
}