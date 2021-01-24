#ifndef CERROR_H
#define CERROR_H

#include <QString>

namespace Utils {
/**
 * @brief 当前类用于程序运行过程中反馈错误信息
 */
class CError
{
public:
    CError();
    CError(int code);
    CError(int code, const QString &info);
    CError(const CError &other);

    inline int code() const {return m_code;}
    inline QString info()const {return m_info;}
    //! 如果当前类中的m_code为0，表示之前执行正常
    inline bool success()const {return m_code == 0;}

private:
    int m_code;
    QString m_info;
};

}

#endif // CERROR_H
