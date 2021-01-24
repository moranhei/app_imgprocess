#ifndef CMEASUREMENT_H
#define CMEASUREMENT_H

#include <QLabel>
#include <QSlider>
#include <QtGui>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QWidget>
#include <QBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "../graphicsExp/cimageeditor.h"
#include "../../algorithm/cgray.h"
#include "../../algorithm/cenhance.h"

namespace Assistant {

struct BlobStruct {
    float area;
    float circularity;
    float convexity;
    QPointF center;
    float width;
    float height;
    double diameter;
    double meanThd; //!< 平均灰度
} ;

class CMeasurement : public QWidget
{
    Q_OBJECT
public:
    CMeasurement(QWidget *parent = 0);
    void setImage(QImage img);

private:
    QWidget *segmentWidget;
    QMenuBar *menuBar;
    QPushButton *btnProcess;
    GraphicsExp::CImageEditor *imageEditor;

public slots:
    void openImage();
    void imageProcess();

private:
    QImage qImageFile;
};
}

#endif // CMEASUREMENT_H
