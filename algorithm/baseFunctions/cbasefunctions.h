#ifndef CBASEFUNCTIONS_H
#define CBASEFUNCTIONS_H

#include <QString>

namespace Algorithm{  namespace BaseFunctions {
    /**
     * @brief showMessage  显示程序运行相关错误信息
     * @param message  输入信息
     */
    static void showErrorMessage(QString message);
    /**
     * @brief showInfoMessage  显示程序运行相关提示信息
     * @param message
     */
    static void showInfoMessage(QString message);
}
}

class CBaseFunctions
{
public:
    CBaseFunctions();
};

#endif // CBASEFUNCTIONS_H
