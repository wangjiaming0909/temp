#if defined(_WIN32) || defined(WIN32)
#define OS_WIN 1
#else
#define OS_WIN 0
#endif

#if OS_WIN
#define _SECURE_SCL 0
#define _CRT_SECURE_NO_WARNINGS 0
#endif
