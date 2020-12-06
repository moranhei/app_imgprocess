#ifndef QIMGGRAPHICSVIEW_H
#define QIMGGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

/**
 * @brief 当前类用于图像显示等操作
 */
class QImgGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    QImgGraphicsView(QWidget *parent = 0);

protected:
    /* 当鼠标移动时，激发view的mouseMoveEvent事件执行，并执行下述重写函数；
     * 在重写函数中，发送自定义的mouseMovePoint信号；
     * 该信号与对应的槽函数绑定，并执行相关的槽函数；
     */
    void mouseMoveEvent(QMouseEvent *event); //!< 重写鼠标移动事件响应函数
//    void mousePressEvent(QMouseEvent *event); //!< 重写鼠标单击事件响应函数
//    void mouseDoubleClickEvent(QMouseEvent *event); //!< 重写鼠标双击事件响应函数
    void keyPressEvent(QKeyEvent *event); //!< 重写按键事件响应函数

signals:
    void mouseMovePoint(QPoint point); //!< 鼠标移动
//    void mouseClicked(QPoint point); //!< 鼠标单击
//    void mouseDoubleClick(QPoint point); //!< 双击事件
    void keyPress(QKeyEvent *event); //!< 按键事件
};

#endif // QIMGGRAPHICSVIEW_H
