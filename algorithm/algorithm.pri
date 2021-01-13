# 当前algorithm名称空间用于添加各种基础检测算法

include($$(QTF_3RD_ROOT)/vision/opencv/opencv4_0.pri)
include(baseFunctions/baseFunctions.pri)

HEADERS += \
    $$PWD/ialgorithm.h \
    $$PWD/cgemo.h
    $$PWD/cerror.h

SOURCES += \
    $$PWD/ialgorithm.cpp \
    $$PWD/cgemo.cpp
