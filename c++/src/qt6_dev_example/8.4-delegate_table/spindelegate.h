//
// Created by leever on 2023/6/1.
//

#ifndef C_SPINDELEGATE_H
#define C_SPINDELEGATE_H

#include <QItemDelegate>

class SpinDelegate: public QItemDelegate {
    Q_OBJECT
public:
    SpinDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelDate(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif //C_SPINDELEGATE_H
