//
// Created by leever on 2023/6/1.
//

#ifndef C_COMBODELEGATE_H
#define C_COMBODELEGATE_H

#include <QItemDelegate>

class ComboDelegate: public QItemDelegate {
    Q_OBJECT
public:
    ComboDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorDate(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif //C_COMBODELEGATE_H
