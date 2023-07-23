//
// Created by leever on 9/30/2022.
//

#ifndef QT6_DEV_EXAMPLE_IMAGEPROCESSOR_H
#define QT6_DEV_EXAMPLE_IMAGEPROCESSOR_H

#include "ShowWidget.h"
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBox>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <QToolBar>

class ImageProcessor: public QMainWindow {
    Q_OBJECT
public:
    explicit ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor() override;

    void createActions();
    void createMenus();
    void createToolBars();

    void loadFile(QString filename);
    void mergeFormat(const QTextCharFormat&);
protected slots:
    static void showNewFile();
    void showOpenFile();
    void showPrintText();
    void showPrintImage();
    void showZoomIn();
    void showZoomOut();
    void showRotate90();
    void showRotate180();
    void showRotate270();
    void showMirrorVertical();
    void showMirrorHorizontal();

    void showFontComboBox(const QString& comboString);
    void showSizeSpinBox(const QString& spinValue);
    void showBoldBtn();
    void showItalicBtn();
    void showUnderlineBtn();
    void showColorBtn();
    void showCurrentFormatChange(const QTextCharFormat &fmt);

    void showList(int);
    void showAlignment(QAction *action);
    void showCursorPositionChanged();
private:
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;

    QImage img;
    QString fileName;
    ShowWidget *showWidget;

    QAction *openFileAction;
    QAction *newFileAction;
    QAction *printTextAction;
    QAction *printImageAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    QAction *rotate90Action;
    QAction *rotate180Action;
    QAction *rotate270Action;

    QAction *mirrorVerticalAction;
    QAction *mirrorHorizontalAction;

    QAction *undoAction;
    QAction *redoAction;

    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;

    QToolBar *doToolBar;
//
    QLabel *fontLabel1;
    QFontComboBox *fontComboBox;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;

    QToolBar *fontToolBar;
//
    QLabel *listLabel;
    QComboBox *listComboBox;
    QActionGroup *actionGroup;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;

    QToolBar *listToolBar;
};


#endif //QT6_DEV_EXAMPLE_IMAGEPROCESSOR_H
