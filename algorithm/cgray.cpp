#include "cgray.h"

using namespace Algorithm;

CGray::CGray()
{

}

QImage CGray::bin(QImage src, qint32 threshold)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    //! 获得图像的通道数
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
    cv::threshold(matSrc, matDst, threshold, 255, cv::THRESH_BINARY);
    return mat2QImage(matDst);
}

QImage CGray::gray(QImage src)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cvtColor(matSrc, matDst, CV_BGR2GRAY);
    else
        matDst = matSrc;
    return mat2QImage(matDst);
}

QImage CGray::threshold(QImage src, qint32 minGray, qint32 maxGray)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
    cv::threshold(matSrc, matSrc, maxGray, 255, cv::THRESH_TOZERO_INV);
    cv::threshold(matSrc, matDst, minGray, 255, cv::THRESH_BINARY);
    return mat2QImage(matDst);
}

QImage CGray::scaleImage(QImage src, qreal mult, qreal add)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    //! 矩阵变换:  matSrc * mult + add = matDst;参数为负数表示源和目标矩阵通道数相同
    matSrc.convertTo(matDst, -1, mult, add);
    //! 将图像像素值映射到[0, 255]范围
    cv::normalize(matDst, matDst, 0, 255, cv::NORM_MINMAX);
    //! 对图像像素值做线性变换，返回值为整型，即会将数据转换为uint8类型，实际上即[0-255]的范围
    cv::convertScaleAbs(matDst, matDst);
    return mat2QImage(matDst);
}

QImage CGray::equHistoImage(QImage src)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
    cv::equalizeHist(matSrc, matDst);
    return mat2QImage(matDst);
}

QImage CGray::gamma(QImage src, qreal mult, qreal gamma)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    uchar lutData[256];
    //! 创建查找表，0-255像素对应的值与表中数据一一对应
    for (int i = 0; i < 256; i++){
        lutData[i] = static_cast<uchar>(mult * pow(i/255.0, gamma)*255.0); //! 将查找表的数据映射到[0,255]
    }
    cv::Mat lut(1, 256, CV_8UC1, lutData);
    cv::LUT(matSrc, lut, matDst);
    return mat2QImage(matDst);
}
