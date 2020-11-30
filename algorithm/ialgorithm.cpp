#include "ialgorithm.h"
#include "libs/async/cexecute.h"
#include "vision/cdebugwidget.h"
#include <QDebug>
#include <QTime>
#include <QGraphicsTextItem>

using namespace Vision;

IAlgorithm::IAlgorithm()
{

}

int IAlgorithm::hregionToGraphics(Halcon::Hobject &region, QImage &src, QImage &dst)
{
    CHECK_RETURN_HOBJECT(region);
    CHECK_RETURN_QIMAGE(src);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if (src.format() != QImage::Format_RGB888)
        dst = src.convertToFormat(QImage::Format_RGB888);
    else
        dst = src;
    HTuple num;
    count_obj(region, &num);
    for (int i = 1; i <= num[0].I(); ++i) {
        int r = qrand() % 255;
        int g = qrand() % 255;
        int b = qrand() % 255;
        QColor color(r,g,b);
        Hobject obj;
        select_obj(region, &obj, i);
        HTuple rows, cols;
        get_region_points(obj, &rows, &cols);
        for (int j = 0; j < rows.Num(); ++j) {
            dst.setPixelColor(QPoint(cols[j].I(), rows[j].I()), color);
        }
    }
    src = dst;
    return ALG_RERURN_OK;
}

int IAlgorithm::hxldToGraphics(Hobject &xld, QImage &src, QImage &dst, QColor& color)
{
    CHECK_RETURN_HOBJECT(xld);
    CHECK_RETURN_QIMAGE(src);
    if (src.format() != QImage::Format_RGB888)
        dst = src.convertToFormat(QImage::Format_RGB888);
    else
        dst = src;
    HTuple num;
    count_obj(xld, &num);
    for (int i = 1; i <= num[0].I(); ++i) {
        Hobject obj;
        select_obj(xld, &obj, i);
        HTuple rows, cols;
        get_contour_xld(obj, &rows, &cols);
        for (int j = 0; j < rows.Num(); ++j)
            dst.setPixelColor(QPoint(cols[j].I(), rows[j].I()), color);
    }
    src = dst;
    return ALG_RERURN_OK;
}

int IAlgorithm::showText(Graphics::CJScene *scene, QString text, int row, int col, int fontSize, QColor color)
{
    if(!scene)
        return ALG_PAM_ERROR;
    if(text.isEmpty())
        return ALG_PAM_ERROR;
    Async::CExecute(true) <= [ = ]() {
        QGraphicsTextItem *textitem = new QGraphicsTextItem(text);
        textitem->setPos(col, row);
        textitem->setFont(QFont("Microsoft YaHei", fontSize, QFont::Normal));
        textitem->setDefaultTextColor(color);
        scene->addItem(textitem);
    };
    return ALG_RERURN_OK;
}

QImage IAlgorithm::hobjectToQimage(Hobject &hobject)
{
    QImage image;
    Hlong nchannels;
    uchar *ptrR, *ptrG, *ptrB;
    Hlong width, height;
    uchar *data ;
    QVector<QRgb> colorTable;

    if (H_EMPTY_REGION != hobject.Id()) {
        convert_image_type(hobject, &hobject, "byte");
        get_image_size(hobject, &width, &height);
        count_channels(hobject, &nchannels);
        if (3 == nchannels) {
            // RGB图像
            get_image_pointer3( hobject, (Hlong *)&ptrR, (Hlong *)&ptrG, (Hlong *)&ptrB, NULL, NULL, NULL);
            image = QImage(width, height, QImage::Format_RGB888);
            for (int i = 0; i < height; i++) {
                data = image.scanLine(i);
                for (int j = 0; j < width; j++) {
                    int w = i * width + j;
                    data[j * 3] = ptrR[w];
                    data[j * 3 + 1] = ptrG[w];
                    data[j * 3 + 2] = ptrB[w];
                }
            }
        } else if (1 == nchannels) {
            // 灰度图像
            for (int i = 0; i < 256; i++) {
                colorTable.append(qRgb(i, i, i));
            }

            get_image_pointer1(hobject, (Hlong *)&ptrR, NULL, NULL, NULL);
            image = QImage(width, height, QImage::Format_Indexed8);
            for (int i = 0; i < height; i++) {
                data = image.scanLine(i);
                for (int j = 0; j < width; j++) {
                    data[j] = ptrR[i * width + j];
                }
            }

            image.setColorTable(colorTable);
        }
    }
    return image;
}

void IAlgorithm::clearScene(Graphics::CJScene *scene)
{
    if (!scene)
        return ;
    QList<QGraphicsItem *> items = scene->items();
    //qDebug() << "items size: " << items.size();
    Async::CExecute(true) <= [ = ]() {
        for (int i = 0; i < items.size() - 1; ++i)
            delete items[i];
    };
}

QImage IAlgorithm::himageToqimage(const HImage &image)
{
    HTuple w, h;
    HTuple type;
    auto data = image.GetImagePointer1(&type, &w, &h);
    return QImage((uchar *)data, w[0].I(), h[0].I(), QImage::Format_Grayscale8);
}

int IAlgorithm::detectImpression(Hobject &src, Halcon::Hobject& roi,int opensize,int min,int max,int minWidth,Hobject& showRegion)
{
    CHECK_RETURN_HOBJECT(src);
    CHECK_RETURN_HOBJECT(roi);
    if(opensize == 0 || min == 0 || max == 0 || minWidth == 0)
        return ALG_PAM_ERROR;
    Hobject imgreduced,regions,connectedRegions,selectRegion;
    set_check("~give_error");
    reduce_domain(src,roi,&imgreduced);
    bin_threshold(imgreduced,&regions);
    opening_circle(regions,&regions,opensize);
    showRegion = regions;
    connection(regions,&connectedRegions);
    select_shape(connectedRegions,&selectRegion,"area","and",min,max);
    HTuple num;
    count_obj(selectRegion,&num);
    if(num[0].I() == 0)
        return ALG_RESULT_1;
    HTuple row1,col1,row2,col2;
    CHECK_RETURN_HERROR(smallest_rectangle1(selectRegion,&row1,&col1,&row2,&col2));
    if(row1.Num() == 0)
        return ALG_RESULT_2;
    for(int i = 0;i < row1.Num();++i)
    {
        int width = abs(row1[i].I() - row2[i].I());
        if(width < minWidth)
            return ALG_RESULT_3;
    }
    set_check("give_error");
    return ALG_RERURN_OK;
}
