#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "algorithm/cerror.h"

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
    setWindowState(Qt::WindowMaximized);//!< 窗口默认启动最大化
    setWindowIcon(QIcon(":/Image/icon/app_imgprocess.png"));//!< 设置应用程序的图标
    ui->dockTools->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    ui->graphicsView->resize(QSize(500, 500));

}


void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QImage qImgFile;
    QString imgName = QFileDialog::getOpenFileName(this, QString("选择文件"), QString("/home"), QString("Images(*.png *.bmp *.jpg)"));
    if (imgName.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, u8"警告:", u8"文件名为空!");
        msgBox.exec();
        return;
    } else {
        if (qImgFile.load(imgName))
            qCritical() << u8"错误代码:" << ERR_IMAGE_IS_EMPTY;

        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(qImgFile));
//        scene->addRect(100, 100, 400, 300);  //!< 在场景中添加相对于试视图的指定位置和尺寸的矩形
        ui->graphicsView->setScene(scene);
//        ui->graphicsView->set
//        ui->graphicsView->resize(qImgFile.width() + 10, qImgFile.width() + 10);
        ui->graphicsView->show();

    }
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSaveAs_triggered()
{

}
