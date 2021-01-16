#ifndef CENHANCE_H
#define CENHANCE_H

#include <QImage>
#include <algorithm/ialgorithm.h>

namespace Algorithm {

/**
 * @brief 当前类实现图像增强，具体为图像滤波相关函数
 */
class CEnhance : public IAlgorithm
{
public:
    CEnhance();

    /**
     * @brief 高斯滤波
     * @param src:[in]输入图像
     * @param kernel:[in]滤波核尺寸
     * @return 输出图像
     */
    static QImage gaussian(QImage src, int kernel);
    /**
     * @brief 中值滤波
     * @param src:[in]输入图像
     * @param kernel:[in]滤波核的尺寸
     * @return 输出图像
     */
    static QImage median(QImage src, int kernel);

};
}

#endif // CENHANCE_H
