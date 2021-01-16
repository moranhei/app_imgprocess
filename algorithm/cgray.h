#ifndef CGRAY_H
#define CGRAY_H

#include <QImage>
#include <algorithm/ialgorithm.h>

namespace Algorithm {

/**
 * @brief 当前类实现图像的灰度变换
 */
class CGray : public IAlgorithm
{
public:
    CGray();

    /**
     * @brief 图像二值化
     * 其中小于threshold像素被置为0；大于threshold像素被置为255；相当于threshold(src, threshold, 255)的效果
     * @param src:[in]输入图像
     * @param threshold:[in]阈值
     * @return 返回0和1二值化图像
     */
    static QImage bin(QImage src, qint32 threshold);
    /**
     * @brief 图像灰度化
     * @param src:[in]输入图像
     * @return 输出灰度图像
     */
    static QImage gray(QImage src);
    /**
     * @brief 固定阈值分割
     * @param src:[in]输入图像
     * @param minGray:[in]阈值下限
     * @param maxGray:[in]阈值上限
     * @return 返回满足条件像素所在位置（置为255）的二值图像
     */
    static QImage threshold(QImage src, qint32 minGray, qint32 maxGray);
    /**
     * @brief 图像灰度变换
     * @param src:[in]输入图像
     * @param mult:[in]灰度乘积系数
     * @param add:[in]灰度偏移
     * @return 输出图像
     */
    static QImage scaleImage(QImage src, qreal mult, qreal add);
    /**
     * @brief 直方图均衡化
     * @param src:[in]输入图像
     * @return 输出图像
     */
    static QImage equHistoImage(QImage src);
    /**
     * @brief 伽马变换(指数变换); matDst = mult * matSrc ^ gamma
     * @param src:[in]输入图像
     * @param mult:[in]乘积系数
     * @param gamma:[in]伽马系数，系数小于1时图像低灰度部分图像被拉升，大于1图像高灰度部分图像被降低
     * @return 输出图像
     */
    static QImage gamma(QImage src, qreal mult, qreal gamma);

};
}
#endif // CGRAY_H
