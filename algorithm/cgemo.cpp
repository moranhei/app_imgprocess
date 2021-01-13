#include "cgemo.h"

using namespace Algorithm;

CGemo::CGemo()
{

}

QImage CGemo::resize(QImage src, int length, int width)
{
    Mat matDst;
    cv::resize(qImage2Mat(src), matDst, Size(length, width), 0, 0, INTER_LINEAR);
    return mat2QImage(matDst);
}

QImage CGemo::rotate(QImage src, int angle, QPoint pt)
{
    QImage a;
    return a;
}

QImage CGemo::flip(QImage src, int flipcode)
{
    QImage a;
    return a;
}

QImage CGemo::crop(QImage src, int length, int width)
{
    QImage a;
    return a;
}
