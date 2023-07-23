//
// Created by leever on 2023/6/1.
//
#include "spindelegate.h"
#include <QSpinBox>

SpinDelegate::SpinDelegate(QObject *parent): QItemDelegate(parent) {

}

QWidget *
SpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto *editor = new QSpinBox(parent);
    editor->setRange(0, 10000);
    editor->installEventFilter(const_cast<SpinDelegate*>(this));
    return editor;
}

void SpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    int value = index.model()->data(index).toInt();
    auto *box = dynamic_cast<QSpinBox*>(editor);
    box->setValue(value);
}

void SpinDelegate::setModelDate(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    auto *box = dynamic_cast<QSpinBox*>(editor);
    int value = box->value();

    model->setData(index, value);
}

void SpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}
