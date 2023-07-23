//
// Created by leever on 9/29/2022.
//

#ifndef QT6_DEV_EXAMPLE_PALETTE_H
#define QT6_DEV_EXAMPLE_PALETTE_H

#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>

class Palette : public QDialog {
    Q_OBJECT
public:
    explicit Palette(QWidget *parent = nullptr);
    ~Palette() override;
    void createCtrlFrame();
    void createContentFrame();
    static void fillColorList(QComboBox*);
private slots:
    void showWindow();
    void showWindowText();
    void showButton();
    void showButtonText();
    void showBase();
private:
    QFrame *ctrlFrame;
    QLabel *windowLabel;
    QComboBox *windowComboBox;
    QLabel *windowTextLabel;
    QComboBox *windowTextComboBox;
    QLabel *buttonLabel;
    QComboBox *buttonComboBox;
    QLabel *buttonTextLabel;
    QComboBox *buttonTextComboBox;
    QLabel *baseLabel;
    QComboBox *baseComboBox;
    QFrame *contentFrame;
    QLabel *label1;
    QComboBox *comboBox1;
    QLabel *label2;
    QLineEdit *lineEdit2;
    QTextEdit *textEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
};


#endif //QT6_DEV_EXAMPLE_PALETTE_H
