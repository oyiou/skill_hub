//
// Created by leever on 2023/6/1.
//

#ifndef C_MAINWINDOW_H
#define C_MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>

#include "histogramview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createAction();
    void createMenu();
    void setupModel();
    void setupView();
private:
    QMenu *fileMenu;
    QAction *openAct;

    QStandardItemModel *model;
    QTableView *table;
    QSplitter *splitter;
public:
    void openFile(QString);
public slots:
    void slotOpen();
private:
    HistogramView *histogram;
};

#endif //C_MAINWINDOW_H
