#ifndef CGEMO_H
#define CGEMO_H

#include <QImage>
#include <algorithm/ialgorithm.h>

namespace Algorithm {
/**
 * @brief 图像几何变换类
 */
class CGemo : public IAlgorithm
{
public:
    CGemo();
    /**
     * @brief 对图像进行尺寸变换；
     * 当输入长宽比与原图像不同，变换后的图像会被压缩或者拉伸
     * @param src:[in]输入图像
     * @param length:[in]变换后图像长度
     * @param width:[in]变换后图像宽度
     * @return 变换后图像
     */
    static QImage resize(QImage src, int length, int width);
    static QImage rotate(QImage src, int angle, QPoint pt);
    static QImage flip(QImage src, int flipcode);
    static QImage crop(QImage src, int length, int width);
};
}

#endif // CGEMO_H
