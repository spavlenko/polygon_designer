#pragma once
#include <QtGlobal>

#define PD_ASSERT(cond) Q_ASSERT(cond)

#define PD_FATAL(cond)\
    do \
    { \
    if (!(cond)) \
        { \
            PD_ASSERT(!"Fatal error occured"); \
            std::terminate(); \
        } \
    } while (0)