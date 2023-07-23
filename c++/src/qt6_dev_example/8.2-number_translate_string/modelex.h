//
// Created by leever on 2023/5/31.
//

#ifndef C_MODELEX_H
#define C_MODELEX_H

#include <QAbstractItemModel>
#include <QVector>
#include <QMap>
#include <QStringList>

class ModelEx : public QAbstractTableModel {
public:
    explicit ModelEx(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
signals:

public slots:

private:
    QVector<short> army;
    QVector<short> weaponType;

    QMap<short, QString> armyMap;
    QMap<short, QString> weaponTypeMap;

    QStringList weapon;
    QStringList header;

    void populateModel();
};

#endif //C_MODELEX_H
