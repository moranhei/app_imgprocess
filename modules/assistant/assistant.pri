#当前模块为助手模块，即添加 阈值分割助手，模板匹配助手以及尺寸测量助手等
#有两种方法，一是添加包含界面的设计类，另一种是直接添加类，而界面的设计直接通过程序实现；为了联系，两种方法可以都尝试下。

HEADERS += \
    $$PWD/cmatching.h \
    $$PWD/csegment.h \
    $$PWD/cmeasurement.h

SOURCES += \
    $$PWD/cmatching.cpp \
    $$PWD/csegment.cpp \
    $$PWD/cmeasurement.cpp

