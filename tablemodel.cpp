#include "tablemodel.h"

bool TableModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
        if(!index.isValid())
                return false;

        if (role == Qt::CheckStateRole && index.column() == 7)
        {
                check_state_map[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);
        }

        return true;
}

QVariant TableModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role== Qt::CheckStateRole)
    {
        if(index.column() == 7)
        {
            if (check_state_map.contains(index.row()))
                return check_state_map[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;
            return Qt::Unchecked;
        }
    }
    return QSqlQueryModel::data(index,role);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return 0;

    if (index.column() == 7)
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
