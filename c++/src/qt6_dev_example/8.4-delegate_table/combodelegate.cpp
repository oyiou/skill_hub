//
// Created by leever on 2023/6/1.
//
#include "combodelegate.h"
#include <QComboBox>

ComboDelegate::ComboDelegate(QObject *parent): QItemDelegate(parent) {

}

QWidget *
ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto *editor = new QComboBox(parent);
    editor->addItem("工人");
    editor->addItem("农民");
    editor->addItem("医生");
    editor->addItem("律师");
    editor->addItem("军人");
    editor->installEventFilter(const_cast<ComboDelegate*>(this));
    return editor;
}

void ComboDelegate::setEditorDate(QWidget *editor, const QModelIndex &index) const {
    QString str = index.model()->data(index).toString();

    auto *box = dynamic_cast<QComboBox*>(editor);
    int i = box->findText(str);
    box->setCurrentIndex(i);
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    auto *box = dynamic_cast<QComboBox*>(editor);
    QString str = box->currentText();
    model->setData(index, str);
}
