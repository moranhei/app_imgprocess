#include "cenhance.h"

using namespace Algorithm;

CEnhance::CEnhance()
{

}

QImage CEnhance::normalized(QImage src, int kernel)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::blur(matSrc, matDst, cv::Size(kernel, kernel), cv::Point(-1, -1), cv::BORDER_DEFAULT);
    return mat2QImage(matDst);
}

QImage CEnhance::gaussian(QImage src, int kernel)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::GaussianBlur(matSrc, matDst, cv::Size(kernel, kernel), 0, 0);
    return mat2QImage(matDst);
}

QImage CEnhance::median(QImage src, int kernel)
{
    assert(kernel > 0);
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::medianBlur(matSrc, matDst, kernel);
    return mat2QImage(matDst);
}

QImage CEnhance::sobel(QImage src, int kernel)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::GaussianBlur(matSrc, matSrc, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, cv::COLOR_BGR2GRAY);
    cv::Mat gradX, gradY, absGradX, absGradY;
    //! 对X方向做sobel运算，sobel(输入图像，输出图像，输出图像像素位数，X方向导数阶数，Y方向导数阶数，滤波核，乘积系数，偏移量，边缘处理方法)
    cv::Sobel(matSrc, gradX, CV_16S, 1, 0, kernel, 1, 0, cv::BORDER_DEFAULT);
    cv::Sobel(matSrc, gradY, CV_16S, 0, 1, kernel, 1, 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(gradX, absGradX); //!< 将数据格式转化为uint8
    cv::convertScaleAbs(gradY, absGradY);
    //! matDst = absGradX * 0.5 + absGradY * 0.5 + 0
    cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0,  matDst);
    return mat2QImage(matDst);

}

QImage CEnhance::laplacian(QImage src, int kernel)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::GaussianBlur(matSrc, matSrc, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, cv::COLOR_BGR2GRAY);
    cv::Laplacian(matSrc, matDst, CV_16S, kernel, 1, 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(matDst, matDst);
    return mat2QImage(matDst);
}

QImage CEnhance::canny(QImage src, int kernel, int lowThreshold)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, cv::COLOR_BGR2GRAY);
    cv::blur(matSrc, matSrc, cv::Size(3, 3)); //!< 平均滤波
    //! 低于lowThreshold会被认为不是边缘，高于lowThreshold*3会被认为高阈值，kernel为算子大小
    cv::Canny(matSrc, matDst, lowThreshold, lowThreshold*3, kernel);
    return mat2QImage(matDst);
}
