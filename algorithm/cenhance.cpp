#include "cenhance.h"

using namespace Algorithm;

CEnhance::CEnhance()
{

}

QImage CEnhance::gaussian(QImage src, int kernel)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::GaussianBlur(matSrc, matDst, cv::Size(kernel,kernel), 0, 0);
    return mat2QImage(matDst);
}

QImage CEnhance::median(QImage src, int kernel)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    cv::medianBlur(matSrc, matDst, kernel);
    return mat2QImage(matDst);
}
