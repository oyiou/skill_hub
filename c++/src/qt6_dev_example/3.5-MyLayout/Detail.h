//
// Created by leever on 9/27/2022.
//

#ifndef QT6_DEV_EXAMPLE_DETAIL_H
#define QT6_DEV_EXAMPLE_DETAIL_H

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>

class Detail: public QWidget {
    Q_OBJECT
public:
    explicit Detail(QWidget *parent = nullptr);
private:
    QLabel *NationalLabel;
    QComboBox *NationalComboBox;
    QLabel *ProvinceLabel;
    QComboBox *ProvinceComboBox;
    QLabel *CityLabel;
    QLineEdit *CityLineEdit;
    QLabel *IntroductLabel;
    QTextEdit *IntroductTextEdit;
    QGridLayout *mainLayout;
};


#endif //QT6_DEV_EXAMPLE_DETAIL_H
