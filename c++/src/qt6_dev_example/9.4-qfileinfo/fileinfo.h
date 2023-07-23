//
// Created by leever on 2023/6/2.
//

#ifndef C_FILEINFO_H
#define C_FILEINFO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class FileInfo: public QDialog {
    Q_OBJECT
public:
    FileInfo(QWidget *parent = nullptr, Qt::WindowFlags f = static_cast<QFlag>(0));
    ~FileInfo();
public slots:
    void slotFile();
    void slotGet();
private:
    QLabel *fileNameLabel;
    QLineEdit *fileNameLineEdit;
    QPushButton *fileBtn;

    QLabel *sizeLabel;
    QLineEdit *sizeLineEdit;

    QLabel *createTimeLabel;
    QLineEdit *createTimeLineEdit;

    QLabel *lastModifiedLabel;
    QLineEdit *lastModifiedLineEdit;

    QLabel *lastReadLabel;
    QLineEdit *lastReadLineEdit;

    QLabel *propertyLabel;
    QCheckBox *isDirCheckBox;
    QCheckBox *isFileCheckBox;
    QCheckBox *isSymLinkCheckBox;
    QCheckBox *isHiddenCheckBox;
    QCheckBox *isReadableCheckBox;
    QCheckBox *isWritableCheckBox;
    QCheckBox *isExecutableCheckBox;

    QPushButton *getBtn;
};

#endif //C_FILEINFO_H
