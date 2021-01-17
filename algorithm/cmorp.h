#ifndef CMORP_H
#define CMORP_H

#include <QImage>
#include <algorithm/ialgorithm.h>

namespace Algorithm {

/**
 * @brief 当前类实现图像形态学处理
 */
class CMorp : public IAlgorithm
{
public:
    CMorp();
    /**
     * @brief 图像腐蚀操作
     * @param src:[in]输入图像
     * @param elem:[in]用于腐蚀的结构元的形状
     * @param kernel:[in]用于腐蚀的结构元的大小
     * @param times:[in]递归腐蚀次数
     * @return 输出图像
     */
    static QImage erode(QImage src, qint32 elem, qint32 kernel, int times);
    /**
     * @brief 图像膨胀操作
     * @param src:[in]输入图像
     * @param elem:[in]用于膨胀的结构元的形状
     * @param kernel:[in]用于膨胀的结构元大小
     * @param times:[in]递归膨胀次数
     * @return 输出图像
     */
    static QImage dilate(QImage src, int elem, int kernel, int times);
    /**
     * @brief 图像开运算，即先腐蚀再膨胀
     * @param src:[in]输入图像
     * @param elem:[in]用于开操作的结构元的形状
     * @param kernel:[in]用于开运算的结构元大小
     * @param times:[in]递归开运算次数
     * @return 输出图像
     */
    static QImage open(QImage src, int elem, int kernel, int times);
    /**
     * @brief 图像闭运算，即先膨胀z再腐蚀
     * @param src:[in]输入图像
     * @param elem:[in]用于闭操作的结构元的形状
     * @param kernel:[in]用于闭运算的结构元大小
     * @param times:[in]递归闭运算次数
     * @return 输出图像
     */
    static QImage close(QImage src, int elem, int kernel, int times);
    /**
     * @brief 形态学梯度，图像膨胀结果减去图形腐蚀后结果,只能对灰度图像进行处理
     * @param src:[in]输入图像
     * @param elem:[in]用于形态学梯度计算的结构元的形状
     * @param kernel:[in]用于形态学梯度计算的结构元大小
     * @param times:[in]递归运算次数
     * @return 输出图像
     */
    static QImage gradient(QImage src, int elem, int kernel,int times);
    /**
     * @brief 顶帽操作，原图与开运算结果图之差，突出暗背景上的亮点，只能对灰度图像操作
     * @param src:[in]输入图像
     * @param elem:[in]用于顶帽操作的结构元的形状
     * @param kernel:[in]用于顶帽操作的结构元大小
     * @param times:[in]递归运算次数
     * @return 输出图像
     */
    static QImage topHat(QImage src, int elem, int kernel, int times);
    /**
     * @brief 黑帽操作，闭操作的结果图与原图之差，突出亮背景上的暗点，只能对灰度图像操作
     * @param src:[in]输入图像
     * @param elem:[in]用于黑帽操作的结构元的形状
     * @param kernel:[in]用于黑帽操作的结构元大小
     * @param times:[in]递归运算次数
     * @return 输出图像
     */
    static QImage blackHat(QImage src, int elem, int kernel, int times);
};
}


#endif // CMORP_H
