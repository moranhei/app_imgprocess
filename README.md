# **app_imgprocess**
基于C++的QT应用程序，实现图像的简单处理
---
---
# Thanks for all Reference
### ROI绘制
1. [继承自QLabel](https://blog.csdn.net/qq_36131739/article/details/104855098)   
2. [继承自QWidget](https://blog.csdn.net/qq_40732350/article/details/103538593)
---
---
# 注释
## **原理阐述**
1. 图像的显示是采用经典的QGraphics相关类，而参考程序大都采用QLabel进行图像显示；
2. 其中对QGraphicsView和QGraphicsItem进行继承，并对相关鼠标和键盘事件进行重写，进而实现图像的翻转，放大，自适应等操作；
3. 在类的继承过程中，相关虚函数必须被重写，例如QGraphicsItem中的boundingRect和paint函数，前者定义了当前Item的范围，在该范围内可以对鼠标的相关动作进行检测；后者函数是Item绘制函数；
4. 所以通过继承Item的方法，可以实现各种形状的绘制，当然基本形状可以利用QT中存在的相关方法实现；
## **PLAN**
1. ROI绘制还是采用继承Item的方法；将目前的Item显示图像的方法修改为利用View进行显示；
2. 对QGraphic进行继承并新建名称空间；
3. 框架中似乎忽略了对QGraphicsScene类的相关操作，只有对view和item的相关继承类ImageEditor和CODShape；猜测scene应该是作为ImageEditor的私有变量，当ImageEditor类被实例化后，Scene也会被自动实例化；
4. 尽量将Graphics模块独立出去，不要与主界面发生耦合，如果想在界面中显示相关数据，例如鼠标所在的位置和像素值，可以在视觉界面中添加控件的方式；
5. 在界面的右方添加一个QFrame（继承自QWidget），然后利用addWidget在其中放置View控件；