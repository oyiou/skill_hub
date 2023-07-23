//
// Created by leever on 2022/10/11.
//

#ifndef QT6_DEV_EXAMPLE_GMAINWINDOW_H
#define QT6_DEV_EXAMPLE_GMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QGraphicsEllipseItem>

class GMainWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit GMainWindow(QWidget *parent = nullptr);
    ~GMainWindow() override;

    void initScene();
    void createActions();
    void createMenus();
public slots:
    void slotNew();
    void slotClear();
    void slotAddEllipseItem();
    void slotAddPolygonItem();
    void slotAddTextItem();
    void slotAddRectItem();
    void slotAddAlphaItem();
private:
    QGraphicsScene *scene;
    QAction *newAct;
    QAction *clearAct;
    QAction *exitAct;
    QAction *addEllipseItemAct;
    QAction *addPolygonItemAct;
    QAction *addTextItemAct;
    QAction *addRectItemAct;
    QAction *addAlphaItemAct;
};


#endif //QT6_DEV_EXAMPLE_GMAINWINDOW_H
