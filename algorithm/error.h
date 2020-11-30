#pragma once


#define ALG_RERURN_OK           0
#define ALG_PAM_ERROR           200
#define ALG_HALCON_FUNC_ERROR   201
#define ALG_RESULT_1            202
#define ALG_RESULT_2            203
#define ALG_RESULT_3            204



//halcon error check
#define CHECK_HOBJECT(obj)      \
if(H_EMPTY_REGION == obj.Id())  \
{                               \
    return;                     \
}                               \

#define CHECK_RETURN_HOBJECT(obj)       \
if(H_EMPTY_REGION == obj.Id())          \
{                                       \
    return ALG_PAM_ERROR;               \
}                                       \

#define CHECK_RETURN_HERROR(err)            \
if(err != H_MSG_TRUE)                       \
{                                           \
    return ALG_HALCON_FUNC_ERROR;           \
}

#define CHECK_HERROR(err)            \
if(err != H_MSG_TRUE)                \
{                                    \
    return ;                         \
}

#define CHECK_RETURN_QIMAGE(img)       \
if(img.isNull())                       \
{                                      \
    return ALG_PAM_ERROR;              \
}
