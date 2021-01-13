#include "ialgorithm.h"
#include <QDebug>
#include <QTime>
#include <QGraphicsTextItem>

using namespace Algorithm;

IAlgorithm::IAlgorithm()
{
}

void IAlgorithm::showErrorMessage(QString msg)
{

}

void IAlgorithm::showInfoMessage(QString msg)
{

}

QImage IAlgorithm::mat2QImage(Mat src)
{
    if (src.type() == CV_8UC1) {
        QImage image(src.cols, src.rows, QImage::Format_Indexed8);
        image.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            image.setColor(i, qRgb(i, i, i));
        }
        uchar *pSrc = src.data;
        for (int row = 0; row < src.rows; row ++) {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, src.cols);
            pSrc += src.step;
        }
        return image;
    } else if (src.type() == CV_8UC3) {
        const uchar *pSrc = (const uchar *)src.data;
        QImage image(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    } else if (src.type() == CV_8UC4) {
        const uchar *pSrc = (const uchar *)src.data;
        QImage image(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
        return image.copy();
    } else {
        return QImage();
    }
}

Mat IAlgorithm::qImage2Mat(QImage src)
{
    using namespace cv;
    Mat dst;
    switch (src.format()) {
    //! 前三种图像格式均使用同一种转换函数（8位深度4通道）
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        dst = cv::Mat(src.height(), src.width(), CV_8UC4, (void *)src.constBits(), src.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        dst = cv::Mat(src.height(), src.width(), CV_8UC3, (void *)src.constBits(), src.bytesPerLine());
        cv::cvtColor(dst, dst, COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
    case QImage::Format_Grayscale8:
        dst = cv::Mat(src.height(), src.width(), CV_8UC1, (void *)src.constBits(), src.bytesPerLine());
        break;
    }
    return dst;
}
