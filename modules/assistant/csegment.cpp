#include "csegment.h"

using namespace Assistant;

CSegment::CSegment(QWidget *parent) : QWidget(parent)
{
    //! 在QDialog或者QWidget中添加菜单按钮的过程是：
    //! 现在dialog或widget中添加QMenuBar(菜单栏)；然后在QMenuBar中添加QMenu(菜单)，最后在QMenu中添加QAction(动作)即按键
    //! 对应的对象需要new出来，各对象的父节点(QWidget *parent = nullptr)要选择正确，或者保持默认即不选
    setWindowTitle(u8"阈值分割");
    setWindowIcon(QIcon(":/Image/assistant/Segment.png"));

    menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu(u8"文件(&F)");
    menuBar->addMenu(fileMenu);

    QAction *openImageAct = new QAction(QIcon(":/Image/file/Open.png"), u8"打开(&O)");
    fileMenu->addAction(openImageAct);
    connect(openImageAct, SIGNAL(triggered()), this, SLOT(openImage()));

    //!　使用QHBoxLayout和QVBoxLayout的布局方式，不如QGridLayout布局，尤其是当控件较多时
    QHBoxLayout *layoutLowGray = new QHBoxLayout(); //!< 水平布局
    labLowGray = new QLabel(u8"低阈值:");
    labLowGray->setAlignment(Qt::AlignLeft);
    sliderLowGray = new QSlider(Qt::Horizontal);    //! 滑动条
    sliderLowGray->setRange(0, 255);
    sliderLowGray->setValue(20);
    connect(sliderLowGray, SIGNAL(sliderReleased()), this, SLOT(imageProcess()));
    layoutLowGray->addWidget(labLowGray);
    layoutLowGray->addWidget(sliderLowGray);

    QHBoxLayout *layoutHighGray = new QHBoxLayout(); //!< 水平布局
    labHighGray = new QLabel(u8"高阈值:");
    labHighGray->setAlignment(Qt::AlignLeft);
    sliderHighGray = new QSlider(Qt::Horizontal);       //! 滑动条
    sliderHighGray->setRange(0, 255);
    sliderHighGray->setValue(200);
    connect(sliderHighGray, SIGNAL(sliderReleased()), this, SLOT(imageProcess()));
    layoutHighGray->addWidget(labHighGray);
    layoutHighGray->addWidget(sliderHighGray);

//    QVBoxLayout *layout = new QVBoxLayout(segmentWidget); //!< 垂直布局
    QVBoxLayout *layout = new QVBoxLayout(); //!< 下述两语句与上面语句作用相同
    setLayout(layout);
    imageEditor = new GraphicsExp::CImageEditor();
    layout->addWidget(menuBar);
    layout->addWidget(imageEditor);
    layout->addLayout(layoutLowGray);
    layout->addLayout(layoutHighGray);
}

void CSegment::setImage(QImage img)
{
    qImageFile = img;
    imageEditor->updateImage(qImageFile);
    imageEditor->fitImage();
}

void CSegment::openImage()
{
    QString imgName = QFileDialog::getOpenFileName(this, QString(u8"选择文件"), QString("/home"), QString("Images(*.png *.bmp *.jpg)"));
    if (imgName.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, u8"警告:", u8"文件名为空!");
        msgBox.exec();
        return;
    } else {
        if (!qImageFile.load(imgName)) {
//            qCritical() << u8"错误代码:" << ERR_IMAGE_IS_EMPTY;
            return;
        }
        imageEditor->updateImage(qImageFile);
        imageEditor->fitImage();
    }
}

void CSegment::imageProcess()
{
    if(sliderLowGray->value() > sliderHighGray->value()){
        sliderHighGray->setValue(sliderHighGray->value());
        sliderLowGray->setValue(sliderHighGray->value());
    }
    QImage bin = Algorithm::CGray::threshold(qImageFile, sliderLowGray->value(), sliderHighGray->value());
    imageEditor->updateImage(bin);
    imageEditor->fitImage();
    qDebug() << u8"当前低阈值和高阈值为:" << sliderLowGray->value() << sliderHighGray->value();
}
