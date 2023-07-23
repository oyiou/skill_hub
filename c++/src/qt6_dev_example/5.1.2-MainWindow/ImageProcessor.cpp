//
// Created by leever on 9/30/2022.
//

#include "ImageProcessor.h"
#include <QApplication>
#include <QFileDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTransform>
#include <QColorDialog>
#include <QActionGroup>
#include <QTextCursor>
#include <QTextList>

ImageProcessor::ImageProcessor(QWidget *parent): QMainWindow(parent) {
    setWindowTitle(tr("Ease Word"));

    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);
//
    fontLabel1 = new QLabel(tr("字体："));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);

    fontLabel2 = new QLabel(tr("字号："));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach (int size, db.standardSizes())
    sizeComboBox->addItem(QString::number(size));

    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon("bold.png"));
    boldBtn->setCheckable(true);

    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon("italic.png"));
    italicBtn->setCheckable(true);

    underlineBtn = new QToolButton;
    underlineBtn->setIcon(QIcon("underline.png"));
    underlineBtn->setCheckable(true);

    colorBtn = new QToolButton;
    colorBtn->setIcon(QIcon("color.png"));
    colorBtn->setCheckable(true);
//
    listLabel = new QLabel(tr("排序"));
    listComboBox = new QComboBox;
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem("QTextListFormat::ListLowerAlpha");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");
//
    createActions();
    createMenus();
    createToolBars();

    if (img.load("image.png")) {
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    connect(fontComboBox, SIGNAL(activated(QString)), this, SLOT(showFontComboBox(QString)));
    connect(sizeComboBox, SIGNAL(activated(QString)), this, SLOT(showSizeSpinBox(QString)));
    connect(boldBtn, SIGNAL(clicked()), this, SLOT(showBoldBtn()));
    connect(italicBtn, SIGNAL(clicked()), this, SLOT(showItalicBtn()));
    connect(underlineBtn, SIGNAL(clicked()), this, SLOT(showUnderlineBtn()));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(showColorBtn()));
    connect(showWidget->textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat&)), this, SLOT(showCurrentFormatChange(QTextCharFormat&)));
//
    connect(listComboBox, SIGNAL(activated(int)), this, SLOT(showList(int)));
    connect(showWidget->textEdit->document(), SIGNAL(undoAvailable(bool)), redoAction, SLOT(setEnabled(bool)));
    connect(showWidget->textEdit->document(), SIGNAL(redoAvailable(bool)), redoAction, SLOT(setEnabled(bool)));
    connect(showWidget->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(showCursorPositionChanged()));
}

void ImageProcessor::createActions() {
    openFileAction = new QAction(QIcon("open.png"), tr("打开"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("打开一个文件"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));

    newFileAction = new QAction(QIcon("new.png"), tr("新建"), this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip(tr("新建一个文件"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(showNewFile()));

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    copyAction = new QAction(QIcon("copy.png"), tr("复制"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("复制文件"));
    connect(copyAction, SIGNAL(triggered()), showWidget->textEdit, SLOT(copy()));

    cutAction = new QAction(QIcon("cut.png"), tr("剪切"), this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("剪切文件"));
    connect(cutAction, SIGNAL(triggered()), showWidget->textEdit, SLOT(cut()));

    pasteAction = new QAction(QIcon("paste.png"), tr("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("粘贴文件"));
    connect(pasteAction, SIGNAL(triggered()), showWidget->textEdit, SLOT(paste()));

    aboutAction = new QAction(tr("关于"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(QApplication::aboutQt()));

    printTextAction = new QAction(QIcon("printText.png"), tr("打印文本"), this);
    printTextAction->setStatusTip(tr("打印一个文本"));
    connect(printTextAction, SIGNAL(triggered()), this, SLOT(showPrintText()));

    printImageAction = new QAction(QIcon("printImage.png"), tr("打印图像"), this);
    printImageAction->setStatusTip(tr("打印一副图像"));
    connect(printImageAction, SIGNAL(triggered()), this, SLOT(showPrintImage()));

    zoomInAction = new QAction(QIcon("zoomIn.png"), tr("放大"), this);
    zoomInAction->setStatusTip(tr("放大一张图片"));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(showZoomIn()));

    zoomOutAction = new QAction(QIcon("zoomOut.png"), tr("缩小"), this);
    zoomOutAction->setStatusTip(tr("缩小一张图片"));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(showZoomOut()));

    rotate90Action = new QAction(QIcon("rotate90.png"), tr("旋转 90°"), this);
    rotate90Action->setStatusTip(tr("将一张图片旋转 90°"));
    connect(rotate90Action, SIGNAL(triggered()), this, SLOT(showRotate90()));

    rotate180Action = new QAction(QIcon("rotate180.png"), tr("旋转 180°"), this);
    rotate180Action->setStatusTip(tr("将一张图片旋转 180°"));
    connect(rotate180Action, SIGNAL(triggered()), this, SLOT(showRotate180()));

    rotate270Action = new QAction(QIcon("rotate270.png"), tr("旋转 270°"), this);
    rotate270Action->setStatusTip(tr("将一张图片旋转 270°"));
    connect(rotate270Action, SIGNAL(triggered()), this, SLOT(showRotate270()));

    mirrorVerticalAction = new QAction(QIcon("mirrorVertical.png"), tr("纵向镜像"), this);
    mirrorVerticalAction->setStatusTip(tr("对一张图做纵向镜像"));
    connect(mirrorVerticalAction, SIGNAL(triggered()), this, SLOT(showMirrorVertical()));

    mirrorHorizontalAction = new QAction(QIcon("mirrorHorizontal.png"), tr("横向镜像"), this);
    mirrorHorizontalAction->setStatusTip(tr("对一张图做横向镜像"));
    connect(mirrorHorizontalAction, SIGNAL(triggered()), this, SLOT(showMirrorHorizontal()));

    undoAction = new QAction(QIcon("undo.png"), "撤销", this);
    connect(undoAction, SIGNAL(triggered()), showWidget->textEdit, SLOT(undo()));

    redoAction = new QAction(QIcon("redo.png"), "重做", this);
    connect(redoAction, SIGNAL(triggered()), showWidget->textEdit, SLOT(redo()));
//
    actionGroup = new QActionGroup(this);

    leftAction = new QAction(QIcon("left.png"), "左对齐", actionGroup);
    leftAction->setCheckable(true);

    rightAction = new QAction(QIcon("right.png"), "右对齐", actionGroup);
    rightAction->setCheckable(true);

    centerAction = new QAction(QIcon("center.png"), "居中", actionGroup);
    centerAction->setCheckable(true);
    justifyAction = new QAction(QIcon("justify.png"), "两端对齐", actionGroup);
    justifyAction->setCheckable(true);

    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(showAlignment(QAction*)));
}

void ImageProcessor::createMenus() {
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(printTextAction);
    fileMenu->addAction(printImageAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    zoomMenu = menuBar()->addMenu(tr("编辑"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);

    rotateMenu = menuBar()->addMenu(tr("旋转"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    mirrorMenu = menuBar()->addMenu(tr("镜像"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorHorizontalAction);
}

void ImageProcessor::createToolBars() {
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(newFileAction);
    fileTool->addAction(printTextAction);
    fileTool->addAction(printImageAction);

    zoomTool = addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);

    rotateTool = addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);

    mirrorTool = addToolBar("mirror");
    mirrorTool->addAction(mirrorVerticalAction);
    mirrorTool->addAction(mirrorHorizontalAction);

    doToolBar = addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);

    fontToolBar = addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);

    listToolBar = addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actionGroup->actions());
}

void ImageProcessor::showNewFile() {
    auto *newImageProcessor = new ImageProcessor;
    newImageProcessor->show();
}

void ImageProcessor::showOpenFile() {
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        if (showWidget->textEdit->document()->isEmpty()) {
            loadFile(fileName);
        } else {
            auto *newImageProcessor = new ImageProcessor;
            newImageProcessor->show();
            newImageProcessor->loadFile(fileName);
        }
    }
}

void ImageProcessor::loadFile(QString filename) {
    printf("file name:%s\n", filename.data());

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream textStream(&file);
        while (!textStream.atEnd()) {
            showWidget->textEdit->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
}

void ImageProcessor::showPrintText() {
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
        QTextDocument *document = showWidget->textEdit->document();
        document->print(&printer);
    }
}

void ImageProcessor::showPrintImage() {
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = img.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);

        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(img.rect());
        painter.drawImage(0, 0, img);
    }
}

void ImageProcessor::showZoomIn() {
    if (img.isNull()) {
        return;
    }
    QTransform matrix;
    matrix.scale(2, 2);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showZoomOut() {
    if (img.isNull()) {
        return;
    }
    QTransform matrix;
    matrix.scale(0.5, 0.5);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showRotate90() {
    if (img.isNull()) {
        return;
    }
    QTransform matrix;
    matrix.rotate(90);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showRotate180() {
    if (img.isNull()) {
        return;
    }
    QTransform matrix;
    matrix.rotate(180);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showRotate270() {
    if (img.isNull()) {
        return;
    }
    QTransform matrix;
    matrix.rotate(270);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showMirrorVertical() {
    if (img.isNull()) {
        return;
    }
    img = img.mirrored(false, true);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showMirrorHorizontal() {
    if (img.isNull()) {
        return;
    }
    img = img.mirrored(true, false);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showFontComboBox(const QString& comboString) {
    QTextCharFormat fmt;
    fmt.setFontFamilies(comboString.split(""));
    mergeFormat(fmt);
}

void ImageProcessor::mergeFormat(const QTextCharFormat& format) {
    QTextCursor cursor = showWidget->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    showWidget->textEdit->mergeCurrentCharFormat(format);
}

void ImageProcessor::showSizeSpinBox(const QString& spinValue) {
    QTextTableCellFormat format;
    format.setFontPointSize(spinValue.toFloat());
    showWidget->textEdit->mergeCurrentCharFormat(format);
}

void ImageProcessor::showBoldBtn() {
    QTextCharFormat format;
    format.setFontWeight(boldBtn->isChecked() ? QFont::Bold : QFont::Normal);
    showWidget->textEdit->mergeCurrentCharFormat(format);
}

void ImageProcessor::showItalicBtn() {
    QTextCharFormat format;
    format.setFontItalic(italicBtn->isChecked());
    showWidget->textEdit->mergeCurrentCharFormat(format);
}

void ImageProcessor::showUnderlineBtn() {
    QTextCharFormat format;
    format.setFontUnderline(underlineBtn->isChecked());
    showWidget->textEdit->mergeCurrentCharFormat(format);
}

void ImageProcessor::showColorBtn() {
    QColor color = QColorDialog::getColor(Qt::red, this);
    if (color.isValid()) {
        QTextCharFormat format;
        format.setForeground(color);
        showWidget->textEdit->mergeCurrentCharFormat(format);
    }
}

void ImageProcessor::showCurrentFormatChange(const QTextCharFormat &fmt) {
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamilies().toString(),Qt::MatchExactly));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}

void ImageProcessor::showAlignment(QAction *action) {
    if (action == leftAction)
        showWidget->textEdit->setAlignment(Qt::AlignLeft);
    if (action == rightAction)
        showWidget->textEdit->setAlignment(Qt::AlignRight);
    if (action == centerAction)
        showWidget->textEdit->setAlignment(Qt::AlignCenter);
    if (action == justifyAction)
        showWidget->textEdit->setAlignment(Qt::AlignJustify);
}

void ImageProcessor::showCursorPositionChanged() {
    if (showWidget->textEdit->alignment() == Qt::AlignLeft)
        leftAction->setChecked(true);
    if (showWidget->textEdit->alignment() == Qt::AlignRight)
        rightAction->setChecked(true);
    if (showWidget->textEdit->alignment() == Qt::AlignCenter)
        centerAction->setChecked(true);
    if (showWidget->textEdit->alignment() == Qt::AlignJustify)
        justifyAction->setChecked(true);
}

void ImageProcessor::showList(int index) {
    QTextCursor cursor = showWidget->textEdit->textCursor();
    if (index != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch (index) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                style = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                style = QTextListFormat::ListUpperRoman;
                break;
        }
        cursor.beginEditBlock();

        QTextBlockFormat blockFormat = cursor.blockFormat();
        QTextListFormat listFormat;

        if (cursor.currentList()) {
            listFormat = cursor.currentList()->format();
        } else {
            listFormat.setIndent(blockFormat.indent() + 1);
            blockFormat.setIndent(0);
            cursor.setBlockFormat(blockFormat);
        }
        listFormat.setStyle(style);
        cursor.createList(listFormat);

        cursor.endEditBlock();
    } else {
        QTextBlockFormat blockFormat;
        blockFormat.setObjectIndex(-1);
        cursor.mergeBlockFormat(blockFormat);
    }
}

ImageProcessor::~ImageProcessor() = default;
