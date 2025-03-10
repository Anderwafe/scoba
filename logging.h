#ifndef H_SCOBA_LOGGING
#define H_SCOBA_LOGGING

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

#define SCOBA_LOGLEVEL_INFO  0
#define SCOBA_LOGLEVEL_WARN  1
#define SCOBA_LOGLEVEL_ERROR 2
#define SCOBA_LOGLEVEL_NONE  3

#ifndef SCOBA_LOGLEVEL
#ifndef NDEBUG
#define SCOBA_LOGLEVEL SCOBA_LOGLEVEL_INFO
#else
#define SCOBA_LOGLEVEL SCOBA_LOGLEVEL_ERROR
#endif
#endif

#if SCOBA_LOGLEVEL <= SCOBA_LOGLEVEL_INFO
#define SCOBA_LOGINFO(stream, ...) do {                                               \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:info: in func %s (", __FILE__, __LINE__, __func__); \
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define SCOBA_LOGINFO(stream, ...) NULL
#endif

#if SCOBA_LOGLEVEL <= SCOBA_LOGLEVEL_WARN
#define SCOBA_LOGWARN(stream, ...) do {                                               \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:warn: in func %s (", __FILE__, __LINE__, __func__); \
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define SCOBA_LOGWARN(stream, ...) NULL
#endif

#if SCOBA_LOGLEVEL <= SCOBA_LOGLEVEL_ERROR
#define SCOBA_LOGERROR(stream, ...) do {                                              \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:error: in func %s (", __FILE__, __LINE__, __func__);\
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define SCOBA_LOGERROR(stream, ...) NULL
#endif

#ifndef NDEBUG
#define SCOBA_LOGDEBUG(stream, ...) do {                                              \
    FILE* _stream = stream;                                                     \
    fprintf(_stream, "%s:%d:debug: in func %s (", __FILE__, __LINE__, __func__);\
    fprintf(_stream, __VA_ARGS__);                                              \
    fprintf(_stream, ")\n");                                                    \
} while(0)
#else
#define SCOBA_LOGDEBUG(stream, ...) NULL
#endif

#endif
