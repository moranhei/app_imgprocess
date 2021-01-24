#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsItem>
#include <QKeyEvent>

#include "algorithm/cgemo.h"
#include "algorithm/cgray.h"
#include "algorithm/cenhance.h"
#include "algorithm/cmorp.h"
#include "algorithm/ialgorithm.h"

using namespace GraphicsExp;

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

void MainWindow::closeEvent(QCloseEvent *event)
{
    QString mesg = u8"确定关闭该软件吗?";
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning, u8"警告:", mesg, QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Cancel);
    msgBox->setButtonText (QMessageBox::Ok, QString(u8"确 定"));
    msgBox->setButtonText (QMessageBox::Cancel, QString(u8"取 消"));
    int rb = msgBox->exec();
    if (rb == QMessageBox::Ok) {
        event->accept(); //!< 窗口接受关闭信号，并关闭当前mainwindow窗口
        QCoreApplication::exit(); //!< 上述通常只能删除对应的窗口，但是一个程序通常会有几个窗口，该语句为终止应用程序会关闭所有窗口
    } else if (rb == QMessageBox::Cancel)
        event->ignore();
    delete msgBox;
}

void MainWindow::init()
{
    setWindowTitle("ImageK");
//    setAttribute(Qt::WA_DeleteOnClose, false); //!< 若为true则删除当前部件，若为false则只隐藏不删除
    //! 用于显示像素位置和值
    lbPixelPosition = new QLabel();
    lbPixelVaule = new QLabel();
    ui->statusbar->addPermanentWidget(lbPixelPosition);
    ui->statusbar->addPermanentWidget(lbPixelVaule);
    ui->actionExitFullScreen->setShortcut(QKeySequence(Qt::Key_Escape)); //!< 设置热键为ESC
    ui->actionFullScreen->setShortcut(QKeySequence(Qt::Key_F11));
    setWindowState(Qt::WindowMaximized);//!< 窗口默认启动最大化
    setWindowIcon(QIcon(":/Image/icon/app_imgprocess.png"));//!< 设置应用程序的图标

    QHBoxLayout *layout = new QHBoxLayout(ui->frame);
    imageEditor = new CImageEditor;
    layout->addWidget(imageEditor);
    ui->dockWidget_1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //!< 软件启动会自动新建一个空白图元，避免图元未实例化导致异常
    qImageFile = QImage(500, 500, QImage::Format_RGB32);
    qImageFile.fill(qRgb(255, 255, 255));
    imageEditor->updateImage(qImageFile);
    imageEditor->fitImage();

//    QImage src = Algorithm::CGemo::resize(imageEditor->getImage(), 200, 200);
//    imageEditor->updateImage(src);
}

void MainWindow::on_actionNew_triggered()
{
    QImage defaultImage = QImage(500, 500, QImage::Format_Grayscale8);
    defaultImage.fill(255);
    imageEditor->updateImage(defaultImage);
    imageEditor->fitImage();

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
            Utils::CError(-1, u8"图像加载失败!");
//            qCritical() << u8"错误代码:" << ERR_IMAGE_IS_EMPTY;
            return;
        }

        imageEditor->updateImage(qImageFile);
        imageEditor->fitImage();

//        QImage src = Algorithm::CGray::gray(imageEditor->getImage());
//        QImage src = Algorithm::CEnhance::canny(imageEditor->getImage(), 3,30);
        QImage src = Algorithm::CMorp::erode(imageEditor->getImage(), 0, 3, 1);
        imageEditor->updateImage(src);
        imageEditor->fitImage();

//        QImage src = Algorithm::CGemo::crop(imageEditor->getImage(), 100, 100, 150, 150);
//        imageEditor->updateImage(src);
//        qDebug() << u8"item数目:" << scene->selectedItems().count();
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
//    //鼠标移动事件，point是 GraphicsView的坐标,物理坐标
//    QPointF pointScene = ui->view->mapToScene(point); //转换到Scene坐标
////    ui->label->setText(QString::asprintf(u8"View坐标：%d,%d", point.x(), point.y()));
////    ui->label_2->setText(QString::asprintf(u8"Scene坐标：%.0f,%.0f", pointScene.x(), pointScene.y()));
//    ui->label_1->setText(QString::number(point.x()));
//    ui->label_2->setText(QString::number(point.y()));
//    ui->label_3->setText(QString::number(pointScene.x()));
//    ui->label_4->setText(QString::number(pointScene.y()));
//    if (qImageFile.isNull()) {
//        qCritical() << u8"错误代码:" << ERR_IMAGE_IS_EMPTY;
//        return;
//    }
//    //! 当前设置下，场景原点与图元原点重合，如果图元没有自适应大小，则某点在场景和图元中的位置相同；
//    //! 但是如果图元自适应大小后，某点在场景和图元中的位置成倍数关系，这时通过mapFromScene可以进行转换，将场景坐标转换为图元中坐标；
//    //! 但是因为场景与图元原点重合，故需要偏移半个图元大小尺寸，除非利用setPos将图元中心移动到左上角点
//    QPointF pointPix = itemPixmap->mapFromScene(pointScene) + QPointF(qImageFile.width() * 0.5, qImageFile.height() * 0.5);
//    qDebug() << itemPixmap->scenePos(); //!< 返回的是图元中心在场景中的位置，如果返回为(0,0)表示图元中心与场景中心重合
//    if ((pointPix.x() >= qImageFile.width()) | (pointPix.x() < 0) | (pointPix.y() >= qImageFile.height()) | (pointPix.y() < 0)) {
//        lbPixelPosition->setText(u8"像素坐标:(00,00)");
//        lbPixelVaule->setText(u8"像素值:(00,00,00)");
//        return;
//    }
//    QRgb pixelVaule =  qImageFile.pixel(pointPix.toPoint());
//    lbPixelPosition->setText(u8"像素坐标:(" + QString::number(pointPix.toPoint().x()) + u8"," + QString::number(pointPix.toPoint().y()) + u8")");
//    lbPixelVaule->setText(u8"像素值:(" + QString::number(qRed(pixelVaule)) + u8"," + QString::number(qGreen(pixelVaule)) + u8"," + QString::number(qBlue(pixelVaule)) + u8")");
////    ui->statusbar->showMessage(u8"像素坐标:(" + QString::number(pointPix.x()) + u8"," + QString::number(pointPix.y()) + u8")"); //!< 注意：直接加point.x()会报错
////    ui->statusbar->showMessage(u8"像素值:(" + QString::number(qRed(pixelVaule)) + u8"," + QString::number(qGreen(pixelVaule)) + u8"," + QString::number(qBlue(pixelVaule)) + u8")"); //!< 注意：直接加point.x()会报错
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
    //! 当执行QWidget::close函数时,首先向部件发送QCloseEvent事件(不管部件是否可见)，然后判断部件是否接受QCloseEvent事件；最后执行该事件
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
    imageEditor->fitImage();
//    int widthView = ui->view->width();
//    int heightView = ui->view->height();
////    qDebug() << u8"视图宽度:" << widthView;
//    itemPixmap->setQGraphicsView(widthView, heightView);
//    itemPixmap->resetItemPos();
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
//    CIShape *itemShape = new CIShape;
//    itemShape->setShapeType(RectAngle);
//    itemShape->setAcceptDrops(true);
//    itemShape->setFlag(QGraphicsItem::ItemIsMovable);
//    scene->addItem(itemShape);
//    ui->frame->setFocus();


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

    imageEditor->addRectShape(QPointF(50, 50), QPointF(150, 50), QPointF(150, 150), QPointF(50, 150), Qt::green, 4.0);
//    ui->frame->setFocus();

}

void MainWindow::on_btnOval_clicked()
{
    imageEditor->addFeatureRect(QPointF(50, 50), QPointF(150, 150), Qt::blue, 4.0);
    imageEditor->addFeatureCircle(QPointF(0, 0), 50, Qt::black, 4.0);
    imageEditor->addFeatureEllipse(QPointF(-50, -50), QPointF(150, 50), Qt::red, 4.0);
    imageEditor->addFeatureText(u8"Benedace", QPointF(-200, -200));

    QVector<QPointF> points;
    points.append(QPointF(10.0, 80.0));
    points.append(QPointF(20.0, 10.0));
    points.append(QPointF(80.0, 30.0));
    points.append(QPointF(90.0, 70.0));
    imageEditor->addFeaturePoly(points, Qt::yellow, 4.0);

    QVector<QPointF> points2;
    points2.append(QPointF(20.0, 90.0));
    points2.append(QPointF(30.0, 20.0));
    points2.append(QPointF(90.0, 40.0));
    points2.append(QPointF(100.0, 80.0));
    imageEditor->addFeaturePts(points2, Qt::red, 5.0);
    //    CIShape *itemShape = new CIShape;
//    itemShape->setShapeType(Ellipse);
//    itemShape->setAcceptDrops(true);
//    itemShape->setFlag(QGraphicsItem::ItemIsMovable);
//    scene->addItem(itemShape);
//    ui->frame->setFocus();
}

void MainWindow::on_btnCircle_clicked()
{
    imageEditor->addCircleShape(QPointF(0, 0), 50, Qt::green, 4.0);
}
void MainWindow::on_segmentAssistant_triggered()
{
    segmentWidget = new Assistant::CSegment();
    segmentWidget->setImage(imageEditor->getImage());
    segmentWidget->show();

    //! ==直接新建并构建界面== //
//    //! 在QDialog或者QWidget中添加菜单按钮的过程是：
//    //! 现在dialog或widget中添加QMenuBar(菜单栏)；然后在QMenuBar中添加QMenu(菜单)，最后在QMenu中添加QAction(动作)即按键
//    //! 对应的对象需要new出来，各对象的父节点(QWidget *parent = nullptr)要选择正确，或者保持默认即不选
//    QWidget *segmentWidget = new QWidget();
//    segmentWidget->setWindowTitle(u8"阈值分割");
//    segmentWidget->setWindowIcon(QIcon(":/Image/assistant/Segment.png"));

//    QMenuBar *menuBar = new QMenuBar();
//    QMenu *fileMenu = new QMenu(u8"文件(&F)");
//    menuBar->addMenu(fileMenu);

//    QAction *openImageAct = new QAction(QIcon(":/Image/file/Open.png"), u8"打开(&O)");
//    fileMenu->addAction(openImageAct);
//    connect(openImageAct, SIGNAL(triggered()), this, SLOT(openImageSeg()));

//    //!　使用QHBoxLayout和QVBoxLayout的布局方式，不如QGridLayout布局，尤其是当控件较多时
//    QHBoxLayout *layoutLowGray = new QHBoxLayout(); //!< 水平布局
//    QLabel *labLowGray = new QLabel(u8"低阈值:");
//    labLowGray->setAlignment(Qt::AlignLeft);
//    QSlider *sliderLowGray= new QSlider(Qt::Horizontal);		// 滑动条
//    sliderLowGray->setRange(0, 255);
//    sliderLowGray->setValue(20);
//    connect(sliderLowGray, SIGNAL(valueChanged(int)), this, SLOT(imageProcess(int)));
//    layoutLowGray->addWidget(labLowGray);
//    layoutLowGray->addWidget(sliderLowGray);

//    QHBoxLayout *layoutHighGray = new QHBoxLayout(); //!< 水平布局
//    QLabel *labHighGray = new QLabel(u8"高阈值:");
//    labHighGray->setAlignment(Qt::AlignLeft);
//    QSlider *sliderHighGray= new QSlider(Qt::Horizontal);		// 滑动条
//    sliderHighGray->setRange(0, 255);
//    sliderHighGray->setValue(200);
//    layoutHighGray->addWidget(labHighGray);
//    layoutHighGray->addWidget(sliderHighGray);

////    QVBoxLayout *layout = new QVBoxLayout(segmentWidget); //!< 垂直布局
//    QVBoxLayout *layout = new QVBoxLayout(); //!< 下述两语句与上面语句作用相同
//    segmentWidget->setLayout(layout);
//    imageEditor = new CImageEditor;
//    layout->addWidget(menuBar);
//    layout->addWidget(imageEditor);
//    layout->addLayout(layoutLowGray);
//    layout->addLayout(layoutHighGray);
//    segmentWidget->show();
    //! ==== //
}

void MainWindow::on_matchingAssistant_triggered()
{
    matchingWidget = new Assistant::CMatching();
    matchingWidget->show();
}

void MainWindow::on_measureAssistant_triggered()
{
    measurementWidget = new Assistant::CMeasurement();
    measurementWidget->setImage(imageEditor->getImage());
    measurementWidget->show();
}
