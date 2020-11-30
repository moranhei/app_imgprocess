#ifndef IALGORITHM_H
#define IALGORITHM_H

#include "libs/graphics/crectitem.h"
#include "libs/graphics/cjscene.h"
#include "error.h"
#include <HalconCpp.h>

using namespace Halcon;
namespace Vision{
/*!
 * \brief The IAlgorithm class
 * 所有算法函数开始必须检测形参是否可用，是否在范围以内
 * 所有算法函数必须以int返回，0 表示OK，其余为NG，宏定义在error.h文件
 * 函数命名需按照驼峰命名法
 */
class IAlgorithm
{
public:
    IAlgorithm();
    static int hregionToGraphics(Halcon::Hobject& region,QImage& src,QImage& dst);
    static int hxldToGraphics(Halcon::Hobject& xld,QImage& src,QImage&dst,QColor& color);
    static int showText(Graphics::CJScene* scene,QString text,int row,int col,int fontSize,QColor color);
    static QImage hobjectToQimage(Halcon::Hobject& hobject);
    static void clearScene(Graphics::CJScene* scene);
    static QImage himageToqimage(const HImage &image);
    static int detectImpression(Halcon::Hobject& src,Halcon::Hobject& roi,int opensize,int min,int max,int minWidth,Hobject& showRegion);
};
}

#endif

