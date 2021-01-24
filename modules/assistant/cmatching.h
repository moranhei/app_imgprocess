#ifndef CMATCHING_H
#define CMATCHING_H

#include <QWidget>

namespace Assistant {

/**
 * @brief 图像模板匹配助手
 */
class CMatching : public QWidget
{
    Q_OBJECT
public:
    CMatching(QWidget *parent = 0);
    virtual ~CMatching() {}
};
}
#endif // CMATCHING_H
