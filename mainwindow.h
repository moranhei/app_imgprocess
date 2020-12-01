#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    /**
     * @brief init  窗口启动时初始化相关操作
     */
    void init();
};
#endif // MAINWINDOW_H
