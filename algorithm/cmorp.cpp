#include "cmorp.h"

using namespace Algorithm;

CMorp::CMorp()
{

}

QImage CMorp::erode(QImage src, qint32 elem, qint32 kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    cv::erode(matSrc, matDst, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}

QImage CMorp::dilate(QImage src, int elem, int kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    cv::dilate(matSrc, matDst, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}

QImage CMorp::open(QImage src, int elem, int kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    //! cv::MORPH_OPEN指明使用开运算，也可以通过修改该标记位实现腐蚀膨胀等
    cv::morphologyEx(matSrc, matDst, cv::MORPH_OPEN, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}

QImage CMorp::close(QImage src, int elem, int kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    //! cv::MORPH_CLOSE指明使用开运算，也可以通过修改该标记位实现腐蚀膨胀等
    cv::morphologyEx(matSrc, matDst, cv::MORPH_CLOSE, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}

QImage CMorp::gradient(QImage src, int elem, int kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, cv::COLOR_BGR2GRAY);
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    //! cv::MORPH_CLOSE指明使用开运算，也可以通过修改该标记位实现腐蚀膨胀等
    cv::morphologyEx(matSrc, matDst, cv::MORPH_GRADIENT, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}

QImage CMorp::topHat(QImage src, int elem, int kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, cv::COLOR_BGR2GRAY);
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    cv::morphologyEx(matSrc, matDst, cv::MORPH_TOPHAT, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}

QImage CMorp::blackHat(QImage src, int elem, int kernel, int times)
{
    cv::Mat matSrc = qImage2Mat(src);
    cv::Mat matDst;
    if (matSrc.channels() != 1)
        cv::cvtColor(matSrc, matSrc, cv::COLOR_BGR2GRAY);
    int elemType = 0;
    if (elem == 0 )
        elemType = cv::MORPH_RECT;
    else if (elem == 1)
        elemType = cv::MORPH_CROSS;
    else if (elem == 3)
        elemType = cv::MORPH_ELLIPSE;
    cv::Mat element = cv::getStructuringElement(elemType, cv::Size(2 * kernel + 3, 2 * kernel + 3), cv::Point(kernel + 1, kernel + 1));
    cv::morphologyEx(matSrc, matDst, cv::MORPH_BLACKHAT, element, cv::Point(-1, -1), times);
    return mat2QImage(matDst);
}
