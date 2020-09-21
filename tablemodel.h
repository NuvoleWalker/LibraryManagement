#include <QtGui>
#include <QApplication>
#include <QSqlQueryModel>
#include <QMap>

class TableModel : public QSqlQueryModel
{

public:
    bool setData(const QModelIndex &, const QVariant &, int);
    QVariant data(const QModelIndex &, int) const;
    Qt::ItemFlags flags(const QModelIndex &) const;

    QMap<int, Qt::CheckState> check_state_map;
};
