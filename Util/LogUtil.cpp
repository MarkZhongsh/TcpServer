#include <stdarg.h>
#include <stdio.h>

#include "LogUtil.h"


void LogUtil::Log(const char *fmt, ...)
{
#ifdef DEBUG
    char *buf = NULL;

    va_list v1;
    va_start(v1, fmt);

    vasprintf(&buf, fmt, v1);

    va_end(v1);

    printf("%s\n",buf);
    
#endif
}
