//
// Created by leever on 9/27/2022.
//

#ifndef QT6_DEV_EXAMPLE_DOCK_H
#define QT6_DEV_EXAMPLE_DOCK_H

#include <QMainWindow>

class Dock: public QMainWindow {
    Q_OBJECT
public:
    Dock(QWidget *parent = nullptr);
    ~Dock() override;
};


#endif //QT6_DEV_EXAMPLE_DOCK_H
