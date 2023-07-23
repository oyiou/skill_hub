//
// Created by leever on 2022/10/10.
//

#include "MapWidget.h"
#include <QSlider>
#include <QGridLayout>
#include <QFile>

MapWidget::MapWidget() {
    readMap();
    zoom = 50;

    int width = map.width();
    int height = map.height();
    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(-width/2.0, -height/2.0, width, height);
    setScene(scene);
    setCacheMode(CacheBackground);

    auto *slider = new QSlider;
    slider->setOrientation(Qt::Vertical);
    slider->setRange(1, 100);
    slider->setTickInterval(10);
    slider->setValue(50);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slotZoom(int)));

    auto *zoomInLabel = new QLabel;
    zoomInLabel->setScaledContents(true);
    zoomInLabel->setPixmap(QPixmap("zoomIn.png"));

    auto *zoomOutLabel = new QLabel;
    zoomOutLabel->setScaledContents(true);
    zoomOutLabel->setPixmap(QPixmap("zoomOut.png"));

    auto label1 = new QLabel(tr("GraphicsView:"));
    viewCoord = new QLabel;
    auto label2 = new QLabel(tr("GraphicsScene:"));
    sceneCoord = new QLabel;
    auto label3 = new QLabel(tr("map:"));
    mapCoord = new QLabel;

    auto *gridLayout = new QGridLayout;
    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(viewCoord, 0, 1);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(sceneCoord, 1, 1);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(mapCoord, 2, 1);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    auto *coordFrame = new QFrame;
    coordFrame->setLayout(gridLayout);

    auto *zoomLayout = new QVBoxLayout;
    zoomLayout->addWidget(zoomInLabel);
    zoomLayout->addWidget(slider);
    zoomLayout->addWidget(zoomOutLabel);

    auto *coordLayout = new QVBoxLayout;
    coordLayout->addWidget(coordFrame);
    coordLayout->addStretch();

    auto *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(zoomLayout);
    mainLayout->addLayout(coordLayout);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(30,30,30,30);
    mainLayout->setSpacing(10);
    setLayout(mainLayout);

    setWindowTitle("Map Widget");
    setMinimumSize(600, 400);
}

void MapWidget::readMap() {
    QString mapName;
    QFile mapFile("maps.txt");
    int ok = mapFile.open(QIODevice::ReadOnly);
    if (ok) {
        QTextStream textStream(&mapFile);
        if (!textStream.atEnd()) {
            textStream >> mapName;
            textStream >> x1 >> y1 >> x2 >> y2;
        }
    }
    map.load(mapName);
}

void MapWidget::slotZoom(int value) {
    qreal s;
    if (value > zoom) {
        s = pow(1.01, (value - zoom));
    } else {
        s = pow(1 / 1.01, (zoom / value));
    }
    scale(s, s);
    zoom = value;
}

void MapWidget::drawBackground(QPainter *painter, const QRectF &rectF) {
    painter->drawPixmap(int(sceneRect().left()), int(sceneRect().top()), map);
}

void MapWidget::mouseMoveEvent(QMouseEvent *mouseEvent) {
    QPoint viewPoint = mouseEvent->pos();
    viewCoord->setText(QString::number(viewPoint.x()) + "," + QString::number(viewPoint.y()));

    QPointF scenePoint = mapToScene(viewPoint);
    sceneCoord->setText(QString::number(scenePoint.x()) + "," + QString::number(scenePoint.y()));

    QPointF latLon = mapTopMap(scenePoint);
    mapCoord->setText(QString::number(latLon.x()) + "," + QString::number(latLon.y()));
}

QPointF MapWidget::mapTopMap(QPointF pointF) {
    QPointF latLon;
    qreal w = sceneRect().width();
    qreal h = sceneRect().height();

    qreal lon = y1 - ((h/2 + pointF.y()) * abs(y1 - y2) / h);
    qreal lat = x1 - ((w/2 + pointF.x()) * abs(x1 - x2) / w);

    latLon.setX(lat);
    latLon.setY(lon);

    return latLon;
}

MapWidget::~MapWidget() = default;
