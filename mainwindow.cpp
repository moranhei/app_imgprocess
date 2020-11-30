#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>

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
}

