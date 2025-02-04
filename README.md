# SCOBA
~~Superior~~ **Stupid C Objects By Anderwafe** - yet another collection of various C libs created for optimize programming experience.

Current version of project consists of next libs:
1. [Logging lib](#logging)
2. [Dynamic array lib](#dynarr) (not prod ready)

# <a name="logging">LOGGING</a>
`#include "logging.h"` // to acquire [logging.h](logging.h) lib

File consists of some macroses for doing logging:
- LOGINFO(FILE* stream, char* fmt, ...)
- LOGWARN(FILE* stream, char* fmt, ...)
- LOGERROR(FILE* stream, int errno, char* fmt, ...)

Each of this macroses takes an arguments `FILE* stream` (stdio, stdout, stderr, etc), `char* fmt, ...` as in `printf()` family functions. `LOGERROR` in addition takes `int errno` - error number which passed to `strerror()` function (`man strerror`).

The format of output string is: `{file}:{line}:{severity}: in func {func} ({fmt})\n`, where:
- `file` is a file name, where log was called;
- `line` is a line in `file`, where log was called;
- `severity` is a called log severity ("info" in `LOGINFO`, "warn" in `LOGWARN`, etc);
- `func` is a function name, where log was called;
- `fmt` is a provided argument.

The `LOG_LEVEL` macros define what `LOG...()` is expand to.
If `LOG_LEVEL <= FUNCTION_LOGLEVEL`, then `LOG...()` will expand to `fprintf()` function.
If `LOG_LEVEL > FUNCTION_LOGLEVEL`, then `LOG...()` will expand to `NULL`, and do nothing.

This library define **four** log levels: LOGLEVEL_INFO (0), LOGLEVEL_WARN (1), LOGLEVEL_ERROR (2) and LOGLEVEL_NONE (3).
By default, if `NDEBUG` and `LOG_LEVEL` is not defined, `LOGLEVEL_INFO` is selected.
            if `NDEBUG` defined and `LOG_LEVEL` is not, `LOGLEVEL_ERROR` is selected.
            and, if `LOG_LEVEL` is defined, then, it is what it is.

If you want to disable all logs, produced by this library, then use:
```#define LOG_LEVEL 0```
in your code.

# <a name="dynarr">Dynamic array</a>
Some info will be....
