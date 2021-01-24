#include "cerror.h"

using namespace Utils;

CError::CError()
{

}

CError::CError(int code)
{
    m_code = code;
}

CError::CError(int code, const QString &info)
{
    m_code = code;
    m_info = info;
}

CError::CError(const CError &other)
{
    m_code = other.code();
    m_info = other.info();
}
