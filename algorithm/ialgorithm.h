#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <QImage>
#include <opencv2/opencv.hpp>
#include "error.h"



namespace Algorithm{

using namespace cv;

/*!
 * \brief 基础算法类
 * 所有算法函数开始必须检测形参是否可用，是否在范围以内
 * 所有算法函数必须以int返回，0 表示OK，其余为NG，宏定义在error.h文件
 * 函数命名需按照驼峰命名法
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
    static QImage mat2QImage(Mat src);
    /**
     * @brief QImage格式图像转化为Mat
     * @param s输入图像
     * @return
     */
    static Mat qImage2Mat(QImage src);
};
}

#endif

