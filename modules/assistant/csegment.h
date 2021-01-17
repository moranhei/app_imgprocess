#ifndef CSEGMENT_H
#define CSEGMENT_H

#include <QLabel>
#include <QSlider>
#include <QtGui>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "../graphicsExp/cimageeditor.h"
#include "../../algorithm/cgray.h"

namespace Assistant {

class CSegment : public QWidget
{
    Q_OBJECT
public:
    CSegment(QWidget *parent = 0);
    void setImage(QImage img);

private:
    QLabel *labLowGray, *labHighGray;
    QSlider *sliderLowGray, *sliderHighGray;
    QWidget *segmentWidget;
    QMenuBar *menuBar;
    GraphicsExp::CImageEditor *imageEditor;

public slots:
    void openImage();
    void imageProcess();

private:
    QImage qImageFile;


};
}
#endif // CSEGMENT_H
