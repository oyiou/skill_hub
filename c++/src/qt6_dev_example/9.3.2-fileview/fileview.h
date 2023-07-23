//
// Created by leever on 2023/6/2.
//

#ifndef C_FILEVIEW_H
#define C_FILEVIEW_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QListWidgetItem>
#include <QFileInfoList>

class FileView: public QDialog {
    Q_OBJECT
public:
    FileView(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    ~FileView();
    void showFileInfoList(const QFileInfoList& list);
public slots:
    void slotShow(const QDir& dir);
    void slotDirShow(QListWidgetItem *item);
private:
    QLineEdit *fileLineEdit;
    QListWidget *fileListWidget;
    QVBoxLayout *mainLayout;
};

#endif //C_FILEVIEW_H
