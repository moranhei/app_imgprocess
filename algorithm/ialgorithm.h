#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <QImage>
#include <assert.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include "error.h"

namespace Algorithm{

/*!
 * \brief The IAlgorithm class
 * 所有算法函数开始必须检测形参是否可用，是否在范围以内
 * 所有算法函数必须以int返回，0 表示OK，其余为NG，宏定义在error.h文件
 * 函数命名需按照驼峰命名法
 * 此外OpenCV中比较简单的核心函数，不建议自己定义类进行封装；
 * 但是进行封装的目的是为了后面自己重写进行联系
 */
class IAlgorithm
{
public:
    IAlgorithm();
    /**
     * @brief showMessage  显示程序运行相关错误信息
     * @param message  输入信息
     */
    static void showErrorMessage(QString msg);
    /**
     * @brief showInfoMessage  显示程序运行相关提示信息
     * @param message
     */
    static void showInfoMessage(QString msg);
    /**
     * @brief Mat格式图像转化为QImage
     * @param 输入图像
     * @return
     */
    static QImage mat2QImage(cv::Mat src);
    /**
     * @brief QImage格式图像转化为Mat
     * @param s输入图像
     * @return
     */
    static cv::Mat qImage2Mat(QImage src);
};
}

#endif

