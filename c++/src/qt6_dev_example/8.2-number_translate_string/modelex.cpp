//
// Created by leever on 2023/5/31.
//
#include "modelex.h"

ModelEx::ModelEx(QObject *parent): QAbstractTableModel(parent) {
    armyMap[1] = QAbstractTableModel::tr("空军");
    armyMap[2] = QAbstractTableModel::tr("海军");
    armyMap[3] = QAbstractTableModel::tr("陆军");
    armyMap[4] = QAbstractTableModel::tr("海军陆战队");

    weaponTypeMap[1] = QAbstractTableModel::tr("轰炸机");
    weaponTypeMap[2] = QAbstractTableModel::tr("战斗机");
    weaponTypeMap[3] = QAbstractTableModel::tr("航空母舰");
    weaponTypeMap[4] = QAbstractTableModel::tr("驱逐舰");
    weaponTypeMap[5] = QAbstractTableModel::tr("直升机");
    weaponTypeMap[6] = QAbstractTableModel::tr("坦克");
    weaponTypeMap[7] = QAbstractTableModel::tr("两栖攻击舰");
    weaponTypeMap[8] = QAbstractTableModel::tr("两栖战车");
    populateModel();
}

void ModelEx::populateModel() {
    header << QAbstractTableModel::tr("军种") << QAbstractTableModel::tr("种类") << QAbstractTableModel::tr("武器");
    army << 1 << 2 << 3 << 4 << 2 << 4 << 3 << 1;
    weaponType << 1 << 3 << 5 << 7 << 4 << 8 << 6 << 2;
    weapon << QAbstractTableModel::tr("B-2") << QAbstractTableModel::tr("尼米兹级") << QAbstractTableModel::tr("阿帕奇") << QAbstractTableModel::tr("黄蜂级")
    << QAbstractTableModel::tr("阿利伯克级") << QAbstractTableModel::tr("AAAV") << QAbstractTableModel::tr("M1A1") << QAbstractTableModel::tr("F-22");
}

int ModelEx::columnCount(const QModelIndex &parent) const {
    return 3;
}

int ModelEx::rowCount(const QModelIndex &parent) const {
    return army.size();
}

QVariant ModelEx::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return armyMap[army[index.row()]];
                break;
            case 1:
                return weaponTypeMap[weaponType[index.row()]];
                break;
            case 2:
                return weapon[index.row()];
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant ModelEx::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return header[section];
    return QAbstractTableModel::headerData(section, orientation, role);
}
