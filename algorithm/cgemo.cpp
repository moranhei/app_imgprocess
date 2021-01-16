#include "cgemo.h"

using namespace Algorithm;

CGemo::CGemo()
{

}

QImage CGemo::resize(QImage src, qint32 width, qint32 height)
{
    cv::Mat matDst;
    cv::resize(qImage2Mat(src), matDst, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    return mat2QImage(matDst);
}

QImage CGemo::rotate(QImage src, qreal angle)
{
    cv::Mat matDst;
    cv::Mat matSrc = qImage2Mat(src);
    //! cols和rows返回图像的列和行，即X轴和Y轴坐标
    cv::Point2f center( matSrc.cols / 2,  matSrc.rows / 2);
    cv::Mat rotMatrix = cv::getRotationMatrix2D(center, angle, 1);
    //! RotatedRect函数对矩形按照点和角度进行选装；boundingRect函数取旋转后图像的最大外接正矩形
    cv::Rect rect = cv::RotatedRect(center, matSrc.size(), angle).boundingRect();
    //! 对2*3矩阵最后一列的偏移量参数进行校正，即原图像与最大外接矩形的偏移量
    rotMatrix.at<double>(0, 2) += rect.width / 2.0 - center.x;
    rotMatrix.at<double>(1, 2) += rect.height / 2.0 - center.y;
    cv::warpAffine(matSrc, matDst, rotMatrix, rect.size());
    return mat2QImage(matDst);
}

QImage CGemo::flip(QImage src, qint32 flipCode)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::flip(matSrc, matDst, flipCode);
    return mat2QImage(matDst);
}

QImage CGemo::crop(QImage src, qint32 xPos, qint32 yPos, qint32 width, qint32 height)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    qint32 widthDst = matSrc.cols-xPos<=width ? matSrc.cols-xPos : width;
    qint32 heightDst = matSrc.rows-yPos<=width ? matSrc.rows-yPos : height;
    cv::Rect rect(xPos, yPos, widthDst, heightDst);  //左上角点，宽，高
    matDst = matSrc(rect);
    return mat2QImage(matDst);
}
