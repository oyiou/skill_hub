//
// Created by leever on 2023/6/2.
//

#ifndef C_WATCHER_H
#define C_WATCHER_H

#include <QWidget>
#include <QLabel>
#include <QFileSystemWatcher>

class Watcher: public QWidget {
    Q_OBJECT
public:
    Watcher(QWidget *parent = nullptr);
    ~Watcher();
public slots:
    static void directoryChanged(const QString& path);
private:
    QLabel *pathLabel;
    QFileSystemWatcher fsWatcher;
};

#endif //C_WATCHER_H
