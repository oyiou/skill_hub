//
// Created by leever on 9/26/2022.
//

#ifndef QT6_DEV_EXAMPLE_BUTTONS_H
#define QT6_DEV_EXAMPLE_BUTTONS_H

#include <QWidget>

class Buttons: public QWidget {
    Q_OBJECT
public:
    explicit Buttons(QWidget *parent = nullptr);
    ~Buttons() override;
};

#endif //QT6_DEV_EXAMPLE_BUTTONS_H
