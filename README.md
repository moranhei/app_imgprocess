# **app_imgprocess**
基于C++的QT应用程序，实现图像的简单处理
---
---
# Thanks for all Reference
### ROI绘制
1. [ImageProcessing](https://github.com/HuangBingjian/ImageProcessing)
2. [继承自QLabel](https://blog.csdn.net/qq_36131739/article/details/104855098)   
3. [继承自QWidget](https://blog.csdn.net/qq_40732350/article/details/103538593)
4. [解决ROI无法拖动问题](https://blog.csdn.net/it_xiangqiang/article/details/111059682)
---
---
# 注释
## **原理阐述**
1. 图像的显示是采用经典的QGraphics相关类，而参考程序大都采用QLabel进行图像显示；
2. 其中对QGraphicsView和QGraphicsItem进行继承，并对相关鼠标和键盘事件进行重写，进而实现图像的翻转，放大，自适应等操作；
3. 在类的继承过程中，相关虚函数必须被重写，例如QGraphicsItem中的boundingRect和paint函数，前者定义了当前Item的范围，在该范围内可以对鼠标的相关动作进行检测；后者函数是Item绘制函数；
4. 所以通过继承Item的方法，可以实现各种形状的绘制，当然基本形状可以利用QT中存在的相关方法实现；
5. 子类对父类的public和protect以及private成员都会继承，但是只能对前两者进行直接操作，私有的只能通过父类的函数进行访问和操作；
6. ImageProcessing-master参考项目中是在界面中添加一个QLabel作为图像界面，然后向其中加载图像，绘制各种形状的图形；
## **计划表**
1. ROI绘制还是采用继承Item的方法；将目前的Item显示图像的方法修改为利用View进行显示；
2. 对QGraphic进行继承并新建名称空间；
3. 框架中似乎忽略了对QGraphicsScene类的相关操作，只有对view和item的相关继承类ImageEditor和CODShape；猜测scene应该是作为ImageEditor的私有变量，当ImageEditor类被实例化后，Scene也会被自动实例化；
4. 尽量将Graphics模块独立出去，不要与主界面发生耦合，如果想在界面中显示相关数据，例如鼠标所在的位置和像素值，可以在视觉界面中添加控件的方式；
5. 在界面的右方添加一个QFrame（继承自QWidget），然后利用addWidget在其中放置View控件；
6. 图像显示的Item作为特殊项，不添加到iShapeList中，放大旋转移动鼠标的操作是View的事件进行响应；而对单个编辑框的操作是对IShape的事件响应；添加一个编辑框就实例化一个IShape；
7. 现在先实现对图像的放大，后续实现图像+编辑框的整体IScene的放大操作；
8. 截至目前，已完成矩形和圆形的ROI绘制移动尺寸改变等操作，ROI选区工具暂时先做这两个，后续开始完善绘图功能；
9. 绘图功能有两种方法，一是直接addFeature，即添加指定尺寸的形状；二是添加鼠标事件即可以绘制不同尺寸的形状；框架中是第一种，ImageProcessing-master参考项目中是第二种；其实两种方法都不难实现，尤其是第二种，综合考虑还是使用第一种，因为自己的软件定位是图像处理，而不是绘图软件；
10. 上述功能基本已经完善，下面开始着手软件算法的添加，首先是利用OpenCV4.0算法库，后续算法自己实现；
11. 参考别人的软件，包括ImageProcessing和Halcon；建议将相关简单函数按照类型封转到类中，然后封装到Algorithm名称空间中；对于像阈值分割，圆拟合和模板匹配等以助手的方式实现，并放到modules名称空间中。而助手的实现则是调用Algorithm名称空间中各个基础函数；
12. 简单函数包括（实际上这些处理都是OpenCV中最基础的函数，这样分开是便于后续自己代码实现这些算法，另外建议函数的接口参数尽量写得丰富一点）：
    - 几何变换：图像剪切，缩放和旋转；
    - 灰度变换：二值化，灰度化，阈值化，线性变换，伽马变换，直方图均衡化等；
    - 图像增强：平滑和锐化，以及各种滤波等；
    - 形态学处理：腐蚀，膨胀，开闭运算等；