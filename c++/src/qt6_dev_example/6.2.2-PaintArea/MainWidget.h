//
// Created by leever on 2022/10/9.
//

#ifndef QT6_DEV_EXAMPLE_MAINWIDGET_H
#define QT6_DEV_EXAMPLE_MAINWIDGET_H

#include "PaintArea.h"
#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QGradient>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class MainWidget: public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;
private:
    PaintArea *paintArea;

    QLabel *shapeLabel;
    QComboBox *shapeComboBox;
    QLabel *penWidthLabel;
    QSpinBox *penWidthSpinBox;
    QLabel *penColorLabel;
    QFrame *penColorFrame;
    QPushButton *penColorBtn;
    QLabel *penStyleLabel;
    QComboBox *penStyleComboBox;
    QLabel *penCapLabel;
    QComboBox *penCapComboBox;
    QLabel *penJoinLabel;
    QComboBox *penJoinComboBox;
    QLabel *fillRuleLabel;
    QComboBox *fillRuleComboBox;
    QLabel *spreadLabel;
    QComboBox *spreadComboBox;
    QGradient::Spread spread;
    QLabel *brushStyleLabel;
    QComboBox *brushStyleComboBox;
    QLabel *brushColorLabel;
    QFrame *brushColorFrame;
    QPushButton *brushColorBtn;

    QGridLayout *rightLayout;
protected slots:
    void showShape(int);
    void showPenWidth(int);
    void showPenColor();
    void showPenStyle(int);
    void showPenCap(int);
    void showPenJoin(int);
    void showSpreadStyle();
    void showFillRule();
    void showBrushColor();
    void showBrush(int);
};


#endif //QT6_DEV_EXAMPLE_MAINWIDGET_H
