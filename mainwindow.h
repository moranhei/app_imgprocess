#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>

#include <qimggraphicsitem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief on_actionNew_triggered  新建图像文件
     */
    void on_actionNew_triggered();
    /**
     * @brief on_actionOpen_triggered  打开图像文件
     */
    void on_actionOpen_triggered();
    /**
     * @brief on_actionSave_triggered  保存文件
     */
    void on_actionSave_triggered();
    /**
     * @brief on_actionSaveAs_triggered  文件另存为
     */
    void on_actionSaveAs_triggered();
    void on_mouseMovePoint(QPoint point); //!< 鼠标移动
    void on_keyPress(QKeyEvent *enent);
    /**
     * @brief on_actionExit_triggered  退出软件
     */
    void on_actionExit_triggered();
    /**
     * @brief on_actionZoom_triggered  图像放大
     */
    void on_actionZoom_triggered();
    /**
     * @brief on_actionReduction_triggered  图像缩小
     */
    void on_actionReduction_triggered();
    /**
     * @brief on_actionAdaptive_triggered  自适应窗口
     */
    void on_actionAdaptive_triggered();
    /**
     * @brief on_actionClockwiseRotation_triggered  顺时针旋转90°
     */
    void on_actionClockwiseRotation_triggered();
    /**
     * @brief on_actionAnticlockwiseRotation_triggered  逆时针旋转90°
     */
    void on_actionAnticlockwiseRotation_triggered();
    /**
     * @brief on_actionCenterRotation_triggered  中心旋转
     */
    void on_actionCenterRotation_triggered();
    /**
     * @brief on_actionFlipLeftRight_triggered  左右翻转
     */
    void on_actionFlipLeftRight_triggered();
    /**
     * @brief on_actionFlipUpDown_triggered  上下翻转
     */
    void on_actionFlipUpDown_triggered();

    void on_actionFullScreen_triggered();

    void on_actionExitFullScreen_triggered();

signals:
    /**
     * @brief wheelEvent  针对鼠标滚轮的操作，即放大图像
     */
    void wheelEvent();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
//    QGraphicsPixmapItem *itemPixmap;
    QLabel *lbPixelPosition;
    QLabel *lbPixelVaule;
    QImgGraphicsItem *itemPixmap;
    /**
     * @brief init  窗口启动时初始化相关操作
     */
    void init();

public:
    /**
     * @brief showImg  公用图像显示函数，便于后于图像直接写入并显示在界面控件中
     * @param qImg  输入图像
     */
    void showImage(QImage qImg);
    QImage qImageFile;

protected:
};
#endif // MAINWINDOW_H
