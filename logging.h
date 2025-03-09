#ifndef H_SCOBA_LOGGING
#define H_SCOBA_LOGGING

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

#define LOGLEVEL_INFO  0
#define LOGLEVEL_WARN  1
#define LOGLEVEL_ERROR 2
#define LOGLEVEL_NONE  3

#ifndef LOG_LEVEL
#ifndef NDEBUG
#define LOG_LEVEL LOGLEVEL_INFO
#else
#define LOG_LEVEL LOGLEVEL_ERROR
#endif
#endif

#if LOG_LEVEL <= LOGLEVEL_INFO
#define LOGINFO(stream, ...) do {                                               \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:info: in func %s (", __FILE__, __LINE__, __func__); \
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define LOGINFO(stream, ...) NULL
#endif

#if LOG_LEVEL <= LOGLEVEL_WARN
#define LOGWARN(stream, ...) do {                                               \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:warn: in func %s (", __FILE__, __LINE__, __func__); \
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define LOGWARN(stream, ...) NULL
#endif

#if LOG_LEVEL <= LOGLEVEL_ERROR
#define LOGERROR(stream, ...) do {                                              \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:error: in func %s (", __FILE__, __LINE__, __func__);\
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define LOGERROR(stream, ...) NULL
#endif

#ifndef NDEBUG
#define LOGDEBUG(stream, ...) do {                                              \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:debug: in func %s (", __FILE__, __LINE__, __func__);\
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define LOGDEBUG(stream, ...) NULL
#endif

#endif
