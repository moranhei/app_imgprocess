#ifndef CGEMO_H
#define CGEMO_H

#include <QImage>
#include <algorithm/ialgorithm.h>

namespace Algorithm {

/**
 * @brief 当前类实现图像的几何变换
 */
class CGemo : public IAlgorithm
{
public:
    CGemo();
    /**
     * @brief 对图像进行尺寸变换；
     * 当输入长宽比与原图像不同，变换后的图像会被压缩或者拉伸
     * @param src:[in]输入图像
     * @param width:[in]变换后图像宽度
     * @param height:[in]变换后图像高度
     * @return 输出图像
     */
    static QImage resize(QImage src, qint32 width, qint32 height);
    /**
     * @brief 对图像绕中心点逆时针旋转指定角度
     * 本来计划可以绕任意点，但是最后的旋转后图像的大小很难确定
     * @param src:[in]输入图像
     * @param angle:[in]输入角度（非弧度）
     * @return
     */
    static QImage rotate(QImage src, qreal angle);
    /**
     * @brief 对图像进行翻转变换
     * @param src:[in]输入图像
     * @param flipcCode:[in]0表示绕X轴翻转，大于0表示绕Y轴旋转，小于0表示绕X和Y轴旋转
     * @return 输出图像
     */
    static QImage flip(QImage src, qint32 flipCode);
    /**
     * @brief 剪切图像
     * 如果超出图像范围，则减取最大图像
     * @param src:[in]输入图像
     * @param xPos:[in]图像左上角X轴坐标
     * @param yPos:[in]图像左上角Y轴坐标
     * @param height:[in]图像宽度
     * @param height:[in]图像高度
     * @return 输出图像
     */
    static QImage crop(QImage src, qint32 xPos, qint32 yPos, qint32 width, qint32 height);
};
}

#endif // CGEMO_H
