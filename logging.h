#ifndef H_SCOBA_LOGGING
#define H_SCOBA_LOGGING

#include <stdio.h>
#include <stddef.h>

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
#define LOGINFO(stream, fmt, ...) fprintf((stream), "%s:%d:info: in func %s (" fmt ")\n", __FILE__, __LINE__, __func__ __VA_OPT__(,) __VA_ARGS__)
#else
#define LOGINFO(stream, fmt, ...) NULL
#endif

#if LOG_LEVEL <= LOGLEVEL_WARN
#define LOGWARN(stream, fmt, ...) fprintf((stream), "%s:%d:warn: in func %s (" fmt ")\n", __FILE__, __LINE__, __func__ __VA_OPT__(,) __VA_ARGS__)
#else
#define LOGWARN(stream, fmt, ...) NULL
#endif

#if LOG_LEVEL <= LOGLEVEL_ERROR
#define LOGERROR(stream, errno, fmt, ...) fprintf((stream), "%s:%d:error: in func %s ([%s]: " fmt ")\n", __FILE__, __LINE__, __func__, strerror(errno) __VA_OPT__(,) __VA_ARGS__)
#else
#define LOGERROR(stream, errno, fmt, ...) NULL
#endif

#endif
