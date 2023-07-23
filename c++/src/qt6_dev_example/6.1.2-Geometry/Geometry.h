//
// Created by leever on 2022/10/9.
//

#ifndef QT6_DEV_EXAMPLE_GEOMETRY_H
#define QT6_DEV_EXAMPLE_GEOMETRY_H

#include <QLabel>
#include <QGridLayout>
#include <QDialog>

class Geometry: public QDialog {
    Q_OBJECT
public:
    explicit Geometry(QWidget *parent = nullptr);
    ~Geometry() override;
    void updateLabel();
private:
    QLabel *xLabel;
    QLabel *xValueLabel;
    QLabel *yLabel;
    QLabel *yValueLabel;
    QLabel *frmLabel;
    QLabel *frmValueLabel;
    QLabel *posLabel;
    QLabel *posValueLabel;
    QLabel *geoLabel;
    QLabel *geoValueLabel;
    QLabel *widthLabel;
    QLabel *widthValueLabel;
    QLabel *heightLabel;
    QLabel *heightValueLabel;
    QLabel *rectLabel;
    QLabel *rectValueLabel;
    QLabel *sizeLabel;
    QLabel *sizeValueLabel;
    QGridLayout *mainLayout;
protected:
    void moveEvent(QMoveEvent *) override;
    void resizeEvent(QResizeEvent *) override;
};


#endif //QT6_DEV_EXAMPLE_GEOMETRY_H
