#include "cmatching.h"

#include <QIcon>

using namespace Assistant;

CMatching::CMatching(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(u8"模板匹配");
    setWindowIcon(QIcon(":/Image/assistant/Matching.png"));
}
