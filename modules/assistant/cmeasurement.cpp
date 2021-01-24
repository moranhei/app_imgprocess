#include "cmeasurement.h"

using namespace Assistant;

CMeasurement::CMeasurement(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(u8"尺寸测量");
    setWindowIcon(QIcon(":/Image/assistant/Measurement.png"));

    menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu(u8"文件(&F)");
    menuBar->addMenu(fileMenu);

    QAction *openImageAct = new QAction(QIcon(":/Image/file/Open.png"), u8"打开(&O)");
    fileMenu->addAction(openImageAct);
    connect(openImageAct, SIGNAL(triggered()), this, SLOT(openImage()));

    QVBoxLayout *layout = new QVBoxLayout(); //!< 下述两语句与上面语句作用相同
    setLayout(layout);
    imageEditor = new GraphicsExp::CImageEditor();

    btnProcess = new QPushButton(QIcon(":/Image/assistant/Process.png"), u8"开始处理");
    connect(btnProcess, SIGNAL(clicked()), this, SLOT(imageProcess()));
    layout->addWidget(menuBar);
    layout->addWidget(imageEditor);
    layout->addWidget(btnProcess);
}

void CMeasurement::setImage(QImage img)
{
    qImageFile = img;
    imageEditor->updateImage(qImageFile);
    imageEditor->fitImage();
}

void CMeasurement::openImage()
{
    QString imgName = QFileDialog::getOpenFileName(this, QString(u8"选择文件"), QString("/home"), QString("Images(*.png *.bmp *.jpg)"));
    if (imgName.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, u8"警告:", u8"文件名为空!");
        msgBox.exec();
        return;
    } else {
        if (!qImageFile.load(imgName)) {
            qCritical() << u8"打开文件失败!";
            return;
        }
        imageEditor->updateImage(qImageFile);
        imageEditor->fitImage();
    }
}

void CMeasurement::imageProcess()
{
    //! 利用阈值寻找轮廓，然后绘制出来
    std::vector<BlobStruct> blobsFeature;
    QImage thresholdImage = Algorithm::CGray::threshold(qImageFile, 0, 250);
    cv::Mat srcMat = Algorithm::IAlgorithm::qImage2Mat(thresholdImage);
    std::vector<std::vector<cv::Point>> tempContours;
    cv::findContours(srcMat, tempContours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE); //!< 对阈值分割的二值图像寻找轮廓
    //! 计算每个轮廓的尺寸信息
    blobsFeature.clear();
    for (int contourIdx = 0; contourIdx < tempContours.size(); contourIdx++) {
        //! 求取轮廓的Hu矩
        cv::Moments moms = cv::moments(cv::Mat(tempContours[contourIdx]));
        if (moms.m00 <= 1) continue;
        //! 最小外接旋转矩形
        cv::RotatedRect r = cv::minAreaRect(tempContours[contourIdx]);
        double width = r.size.width;
        double height = r.size.height;
        cv::Point2f center;
        float radius;
        //! 最小外接圆
        cv::minEnclosingCircle(tempContours[contourIdx], center, radius);

        double diameter = radius * 2;
        double area = moms.m00;
        //! 计算圆弧的长度，或者封闭圆弧的周长
        double perimeter = cv::arcLength(cv::Mat(tempContours[contourIdx]), true);
        //! 计算圆度，即实际面积推出的半径与周长推出的半径的比值
        double circularity = 4 * CV_PI * area / (perimeter * perimeter);
        std::vector<cv::Point> hull;
        //! 查找点集的凸包
        cv::convexHull(cv::Mat(tempContours[contourIdx]), hull);
        //! 计算轮廓点集的面积
        double S = cv::contourArea(cv::Mat(tempContours[contourIdx]));
        double hullArea = cv::contourArea(cv::Mat(hull));
        //! 求取凸度（轮廓点集的实际面积/轮廓凸包的面积）
        double convexity = S / hullArea;
        //! 利用Hu矩求取轮廓的质心
        double x = moms.m10 / moms.m00;
        double y = moms.m01 / moms.m00;

        BlobStruct blob;
        blob.center.setX(x); //!< 中心横坐标
        blob.center.setY(y); //!< 中心纵坐标
        blob.area = area; //!< 面积
        blob.width = width; //!< 宽度
        blob.height = height; //!< 长度
        blob.circularity = circularity; //!< 圆度
        blob.diameter = diameter; //!< 直径
        blob.convexity = convexity; //!< 凸度
        blobsFeature.push_back(blob);
    }

    //! 绘制所有的轮廓点，即阈值分割出的区域边界
    for (qint32 i = 0; i < tempContours.size(); i++) {
        QVector<QPointF> pts;
        for (qint32 j = 0; j < tempContours[i].size(); j++) {
            cv::Point &pt = tempContours[i][j];
            pts.append(QPointF(pt.x, pt.y));
        }
        //! 当前该函数绘制点集存在问题
        imageEditor->addFeaturePts(pts);
    }

    //! ==利用canny寻找边缘，然后再寻找轮廓，再拟合成矩形等，求其尺寸== //
    //!输入图片灰度化
//    cv::Mat dstMat;
//    cv::cvtColor(Algorithm::IAlgorithm::qImage2Mat(qImageFile), dstMat, cv::COLOR_BGR2GRAY);
//   //! 对灰度图片执行高斯滤波
//    cv::GaussianBlur(dstMat, dstMat, cv::Size(7, 7), 0);
//    //! 对滤波结果做边缘检测获取目标
//    cv::Mat edgeMat = cv::Mat(dstMat.rows, dstMat.cols, dstMat.type());
//    cv::Canny(dstMat, edgeMat, 50, 100);
//    //! 使用膨胀和腐蚀操作进行闭合对象边缘之间的间隙
//    cv::dilate(edgeMat, edgeMat, 3);
//    cv::erode(edgeMat, edgeMat, 3);
//    std::vector<std::vector<cv::Point>> tempContours;
//    cv::findContours(edgeMat, tempContours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE); //!< 对阈值分割的二值图像寻找轮廓
    //! 求取轮廓后，后续操作与第一部分，同理
    //! ==== //
}
