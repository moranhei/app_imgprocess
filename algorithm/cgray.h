#ifndef CGRAY_H
#define CGRAY_H

#include <QImage>
#include <algorithm/ialgorithm.h>

namespace Algorithm {

/**
 * @brief 当前类实现图像的灰度变换
 */
class CGray
{
public:
    CGray();

    /**
     * @brief 图像二值化
     * @param src:[in]输入图像
     * @param threshold:[in]阈值
     * @return 输出图像
     */
    static QImage bin(QImage src, qint32 threshold);
    /**
     * @brief 图像灰度化
     * @param src:[in]输入图像
     * @return 输出图像
     */
    static QImage gray(QImage src);
    /**
     * @brief 固定阈值分割
     * @param src:[in]输入图像
     * @param minGray:[in]阈值下限
     * @param maxGray:[in]阈值上限
     * @return 输出图像
     */
    static QImage threshold(QImage src, qint32 minGray, qint32 maxGray);
    /**
     * @brief 图像灰度变换
     * @param src:[in]输入图像
     * @param mult:[in]灰度乘积系数
     * @param add:[in]灰度偏移
     * @return 输出图像
     */
    static QImage scaleImage(QImage src, qint32 mult, qint32 add);
    /**
     * @brief 直方图均衡化
     * @param src:[in]输入图像
     * @return 输出图像
     */
    static QImage equHistoImage(QImage src);

};
}
#endif // CGRAY_H
