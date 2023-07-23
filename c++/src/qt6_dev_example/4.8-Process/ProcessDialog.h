//
// Created by leever on 9/28/2022.
//

#ifndef QT6_DEV_EXAMPLE_PROCESSDIALOG_H
#define QT6_DEV_EXAMPLE_PROCESSDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>

class ProcessDialog : public QDialog {
    Q_OBJECT
public:
    explicit ProcessDialog(QWidget *parent = nullptr);
    ~ProcessDialog() override;
private slots:
    void startProgress();
private:
    QLabel *fileNum;
    QLineEdit *fileNumLineEdit;
    QLabel *progressType;
    QComboBox *comboBox;
    QProgressBar *progressBar;
    QPushButton *starBtn;
    QGridLayout *mainLayout;
};


#endif //QT6_DEV_EXAMPLE_PROCESSDIALOG_H
