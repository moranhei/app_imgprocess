﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsItem>
#include <QKeyEvent>

using namespace Modules;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    setWindowTitle("ImageK");
    //! 用于显示像素位置和值
    lbPixelPosition = new QLabel();
    lbPixelVaule = new QLabel();
    ui->statusbar->addPermanentWidget(lbPixelPosition);
    ui->statusbar->addPermanentWidget(lbPixelVaule);
    ui->actionExitFullScreen->setShortcut(QKeySequence(Qt::Key_Escape)); //!< 设置热键为ESC
    ui->actionFullScreen->setShortcut(QKeySequence(Qt::Key_F11));

    scene = new QGraphicsScene;
//    itemPixmap = new QGraphicsPixmapItem();
    //!< 将scene的原点与view的中心重合，但是这样设置会固定场景的大小，当加载的图像大于场景时，图像居中且只显示部分，也不会自动增加滑块
//    scene->setSceneRect(-round(ui->view->width() / 2), -round(ui->view->height() / 2), ui->view->width(), ui->view->height());

    setWindowState(Qt::WindowMaximized);//!< 窗口默认启动最大化
    setWindowIcon(QIcon(":/Image/icon/app_imgprocess.png"));//!< 设置应用程序的图标
    ui->dockWidget_1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    ui->view->setScene(scene);
    ui->view->setMouseTracking(true); //!< 如果鼠标追踪关闭，则只有按下鼠标移动时，才会触发鼠标移动事件
    ui->view->setCursor(Qt::CrossCursor); //设置鼠标样式为十字架
    ui->view->setDragMode(QGraphicsView::RubberBandDrag);
    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //!< 关闭水平和竖直的滚动条
    ui->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->view, SIGNAL(mouseMovePoint(QPoint)),
            this, SLOT(on_mouseMovePoint(QPoint)));
    connect(ui->view, SIGNAL(keyPress(QKeyEvent *)),
            this, SLOT(on_keyPress(QKeyEvent *)));

//    ui->graphicsView->resize(QSize(500, 500));
//    ui->view->setInteractive(true);
//    connect(ui->graphicsView, SIGNAL(keyPress(QKeyEvent *)), this, SLOT(on_keyPress(QKeyEvent *)));

    //!< 软件启动会自动新建一个空白图元，避免图元未实例化导致异常
    qImageFile = QImage(500, 500, QImage::Format_RGB32);
    qImageFile.fill(qRgb(255, 255, 255));
    showImage(qImageFile);
}

void MainWindow::showImage(QImage qImg)
{
    scene->clear();
    itemPixmap = new QImgGraphicsItem(&QPixmap::fromImage(qImg));
    int widthView = ui->view->width();
    int heightView = ui->view->height();
//    itemPixmap->setQGraphicsView(widthView, heightView);
    itemPixmap->setAcceptDrops(true);
    itemPixmap->setFlag(QGraphicsItem::ItemIsMovable); //!< 该语句实现鼠标长按移动图像
    //! 将图元的中心坐标移动到在scene坐标系中的参数位置；将图元的中心与scene的中心重合，默认图元的左上角点与scene的中心原点重合
//    itemPixmap->setPos(-round(qImg.width() / 2), -round(qImg.height() / 2));
//    itemPixmap->pos();
    scene->addItem(itemPixmap);
//    scene->setSceneRect(QRectF(-widthView / 2, -heightView / 2, widthView, heightView));
    ui->view->setSceneRect(QRectF(-widthView / 2, -heightView / 2, widthView, heightView)); //!< 固定视图中场景大小，第一第二个参数为视图原点在场景坐标系中的位置
    ui->view->setFocus(); //!< 将界面的焦点设置到当前view控件
}


void MainWindow::on_actionNew_triggered()
{
    QImage defaultImage = QImage(500, 500, QImage::Format_Grayscale8);
    defaultImage.fill(255);
    showImage(defaultImage);

//    QGraphicsScene *scene = new QGraphicsScene;
//    scene->setSceneRect(-100, -100, 100, 100);
//    qDebug() << scene->width() << " " << scene->height() << " " << scene->sceneRect();
//    QGraphicsTextItem *itemText = new QGraphicsTextItem("Hello QT");
//    QGraphicsRectItem *itemRect = new QGraphicsRectItem;
//    itemRect->setRect(0, 0, 300, 300);
//    QGraphicsLineItem *itemLine = new QGraphicsLineItem;
//    itemLine->setLine(0, 0, 600, 0);
////    ui->graphicsView->setAlignment(Qt::AlignCenter);
////    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
////    itemLine->setPos(scene->sceneRect().topLeft());
//    qDebug() << u8"中心点:" << scene->sceneRect().center();
//    qDebug() << u8"左上角点:" << scene->sceneRect().topLeft();
//    scene->addItem(itemLine);
//    scene->addItem(itemText);
//    scene->addItem(itemRect);
////        scene->addRect(100, 100, 400, 300);  //!< 在场景中添加相对于试视图的指定位置和尺寸的矩形
//    ui->view->setScene(scene);
//    ui->view->show();
}

void MainWindow::on_actionOpen_triggered()
{
    QString imgName = QFileDialog::getOpenFileName(this, QString(u8"选择文件"), QString("/home"), QString("Images(*.png *.bmp *.jpg)"));
    if (imgName.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, u8"警告:", u8"文件名为空!");
        msgBox.exec();
        return;
    } else {
        if (!qImageFile.load(imgName)) {
            qCritical() << u8"错误代码:" << ERR_IMAGE_IS_EMPTY;
            return;
        }

        showImage(qImageFile);
//        itemPixmap->setFlag(QGraphicsItem::ItemIsMovable);
//        itemPixmap->setPos(100,100);
//        ui->view->show();

//        scene->addPixmap(QPixmap::fromImage(qImageFile));
//        ui->graphicsView->setScene(scene);
//        ui->graphicsView->show();
        qDebug() << u8"item数目:" << scene->selectedItems().count();
    }
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSaveAs_triggered()
{

}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    //鼠标移动事件，point是 GraphicsView的坐标,物理坐标
    QPointF pointScene = ui->view->mapToScene(point); //转换到Scene坐标
//    ui->label->setText(QString::asprintf(u8"View坐标：%d,%d", point.x(), point.y()));
//    ui->label_2->setText(QString::asprintf(u8"Scene坐标：%.0f,%.0f", pointScene.x(), pointScene.y()));
    ui->label_1->setText(QString::number(point.x()));
    ui->label_2->setText(QString::number(point.y()));
    ui->label_3->setText(QString::number(pointScene.x()));
    ui->label_4->setText(QString::number(pointScene.y()));
    if (qImageFile.isNull()) {
        qCritical() << u8"错误代码:" << ERR_IMAGE_IS_EMPTY;
        return;
    }
    //! 当前设置下，场景原点与图元原点重合，如果图元没有自适应大小，则某点在场景和图元中的位置相同；
    //! 但是如果图元自适应大小后，某点在场景和图元中的位置成倍数关系，这时通过mapFromScene可以进行转换，将场景坐标转换为图元中坐标；
    //! 但是因为场景与图元原点重合，故需要偏移半个图元大小尺寸，除非利用setPos将图元中心移动到左上角点
    QPointF pointPix = itemPixmap->mapFromScene(pointScene) + QPointF(qImageFile.width() * 0.5, qImageFile.height() * 0.5);
    qDebug() << itemPixmap->scenePos(); //!< 返回的是图元中心在场景中的位置，如果返回为(0,0)表示图元中心与场景中心重合
    if ((pointPix.x() >= qImageFile.width()) | (pointPix.x() < 0) | (pointPix.y() >= qImageFile.height()) | (pointPix.y() < 0)) {
        lbPixelPosition->setText(u8"像素坐标:(00,00)");
        lbPixelVaule->setText(u8"像素值:(00,00,00)");
        return;
    }
    QRgb pixelVaule =  qImageFile.pixel(pointPix.toPoint());
    lbPixelPosition->setText(u8"像素坐标:(" + QString::number(pointPix.toPoint().x()) + u8"," + QString::number(pointPix.toPoint().y()) + u8")");
    lbPixelVaule->setText(u8"像素值:(" + QString::number(qRed(pixelVaule)) + u8"," + QString::number(qGreen(pixelVaule)) + u8"," + QString::number(qBlue(pixelVaule)) + u8")");
//    ui->statusbar->showMessage(u8"像素坐标:(" + QString::number(pointPix.x()) + u8"," + QString::number(pointPix.y()) + u8")"); //!< 注意：直接加point.x()会报错
//    ui->statusbar->showMessage(u8"像素值:(" + QString::number(qRed(pixelVaule)) + u8"," + QString::number(qGreen(pixelVaule)) + u8"," + QString::number(qBlue(pixelVaule)) + u8")"); //!< 注意：直接加point.x()会报错
}

void MainWindow::on_keyPress(QKeyEvent *event)
{
//    if (scene->selectedItems().count()!=1){
//        ui->statusbar->showMessage(u8"选择的Item数:" + QString::number(scene->selectedItems().count()));
//        return; //没有选中的绘图项，或选中的多于1个
//    }

//    QGraphicsItem   *item=scene->selectedItems().at(0);

    if (event->key() == Qt::Key_Delete) //删除
        scene->removeItem(itemPixmap);
    else if (event->key() == Qt::Key_Space) { //顺时针旋转90度
        //!< 设置旋转中心（场景坐标系），假设图像尺寸120*240，那么下方设置后的旋转中心为场景坐标系中的(60,120)
//        itemPixmap->setTransformOriginPoint(round(qImageFile.width() / 2), round(qImageFile.height() / 2));
        itemPixmap->setRotation(90 + itemPixmap->rotation());
    } else if (event->key() == Qt::Key_PageUp) { //放大
        if (itemPixmap->scale() >= 50)
            return;
//        itemPixmap->setTransformOriginPoint(itemPixmap->pos()); //!< 以图元的中心进行放大
        itemPixmap->setScale(1.1 * itemPixmap->scale()); //!< 默认以中心进行放大
    } else if (event->key() == Qt::Key_PageDown) { //缩小
        if (itemPixmap->scale() <= itemPixmap->getScaleDefault()) {
            itemPixmap->resetItemPos();
            return;
        }
//        itemPixmap->setTransformOriginPoint(round(qImageFile.width() / 2), round(qImageFile.height() / 2)); //!< 以图元的中心进行缩小
        itemPixmap->setScale(0.9 * itemPixmap->scale());
    } else if (event->key() == Qt::Key_Left) //左移
        itemPixmap->setX(-1 + itemPixmap->x());
    else if (event->key() == Qt::Key_Right) //右移
        itemPixmap->setX(1 + itemPixmap->x());
    else if (event->key() == Qt::Key_Up) //上移
        itemPixmap->setY(-1 + itemPixmap->y());
    else if (event->key() == Qt::Key_Down) //下移
        itemPixmap->setY(1 + itemPixmap->y());
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionZoom_triggered()
{
    if (itemPixmap->scale() >= 50)
        return;
    itemPixmap->setScale(1.1 * itemPixmap->scale()); //!< 默认以中心进行放大
}

void MainWindow::on_actionReduction_triggered()
{
    if (itemPixmap->scale() <= itemPixmap->getScaleDefault()) {
        itemPixmap->resetItemPos();
        return;
    }
    itemPixmap->setScale(0.9 * itemPixmap->scale());
}

void MainWindow::on_actionAdaptive_triggered()
{
    int widthView = ui->view->width();
    int heightView = ui->view->height();
//    qDebug() << u8"视图宽度:" << widthView;
    itemPixmap->setQGraphicsView(widthView, heightView);
    itemPixmap->resetItemPos();
}

void MainWindow::on_actionClockwiseRotation_triggered()
{
    itemPixmap->setRotation(90 + itemPixmap->rotation());
}

void MainWindow::on_actionAnticlockwiseRotation_triggered()
{
    itemPixmap->setRotation(-90 + itemPixmap->rotation());
}

void MainWindow::on_actionCenterRotation_triggered()
{
    itemPixmap->setScale(-1 * itemPixmap->scale()); //!< 中心旋转，即旋转180度
}

void MainWindow::on_actionFlipLeftRight_triggered()
{
    //! 另外一种图像放大方法
    //! 且setTransform是QT中建议的图像变换方法，其包括了缩放旋转等相关操作
//    QTransform transform;
//    transform.scale(1.2, 1.5); //!< 分别设置沿X轴和Y轴的放大倍数
//    itemPixmap->setTransform(transform, true);

    QTransform transform;
    transform.rotate(180, Qt::YAxis); //视图绕x轴旋转180度
    itemPixmap->setTransform(transform, true); //!< 选择true表示每次的翻转对象都是基于上一次的翻转结果
//    ui->view->setTransform(transform);
}

void MainWindow::on_actionFlipUpDown_triggered()
{
    QTransform transform;
    transform.rotate(180, Qt::XAxis); //视图绕x轴旋转180度
    itemPixmap->setTransform(transform, true);
}

void MainWindow::on_actionFullScreen_triggered()
{
    showFullScreen();
}

void MainWindow::on_actionExitFullScreen_triggered()
{
    showMaximized();
}

void MainWindow::on_actionBack_triggered()
{

}

void MainWindow::on_actionNext_triggered()
{

}

void MainWindow::on_btnRectangle_clicked()
{
    CIShape *itemShape = new CIShape;
    itemShape->setShapeType(RectAngle);
    itemShape->setAcceptDrops(true);
    itemShape->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(itemShape);
    ui->view->setFocus();


//    QDialog *roiDialog = new QDialog;
//    newLabel = new Modules::CDrawLabel(this);
//    newLabel->setShapeType(Modules::RectAngle);
//    newLabel->setText("China");
//    newLabel->setMinimumSize(qImageFile.width(), qImageFile.height());
//    QVBoxLayout * layout = new QVBoxLayout();//铺满布局
////    newLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);//铺满布局

//    layout->addWidget(newLabel);
//    roiDialog->setLayout(layout);
//    roiDialog->show();
}

void MainWindow::on_btnOval_clicked()
{
    CIShape *itemShape = new CIShape;
    itemShape->setShapeType(Ellipse);
    itemShape->setAcceptDrops(true);
    itemShape->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(itemShape);
    ui->view->setFocus();
}
