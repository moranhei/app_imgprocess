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
     * @brief 归一化滤波器
     * @param src:[in]输入图像
     * @param kernel:[in]滤波核
     * @return 输出图像
     */
    static QImage normalized(QImage src, int kernel);
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
    /**
     * @brief sobel滤波，其实质时一阶求导，可以对边缘提取和图像增强
     * @param src:[in]输入图像
     * @param kernel:[in]滤波核
     * @return 输出图像
     */
    static QImage sobel(QImage src, int kernel);
    /**
     * @brief 拉普拉斯滤波，本质是二阶求导，对精细的细节处理更好
     * @param src:[in]输入图像
     * @param kernel:[in]滤波核
     * @return 输出图像
     */
    static QImage laplacian(QImage src, int kernel);
    /**
     * @brief canny滤波，边缘检测算子
     * @param src:[in]输入图像
     * @param kernel:[in]滤波核
     * @param lowThreshold:[in]灰度阈值
     * @return 输出图像
     */
    static QImage canny(QImage src, int kernel, int lowThreshold);

};
}

#endif // CENHANCE_H
