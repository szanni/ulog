ulog
====

A simple, cross platform, and thread safe logging library written in C99.

Supported platforms are Windows and all Unix systems supporting at least POSIX 2001 (Linux, macOS, BSDs, ...).

Usage
-----

### Setup

To use the single file header library simply drop `ulog.h` into your source directory and include it.

```c
#include "ulog.h"
```

You will need to specify a file to hold the implementation. Do so by defining `ULOG_IMPLEMENTATION`
prior to including `ulog.h` in **one** of your `.c` files.

```c
#define ULOG_IMPLEMENTATION
#include "ulog.h"
```

There are multiple compile time configuration parameters that can be set. Either
do this by `#define` in your source code prior to `ULOG_IMPLEMENTATION` or
via a compiler directive.

```c
#define ULOG_LOG_LEVEL ULOG_TRACE
#define ULOG_PRINT_ERRNO 0
#define ULOG_IMPLEMENTATION
#include "ulog.h"
```

- `ULOG_LOG_LEVEL` specifies the minimum log level.
  Available log levels are: `ULOG_TRACE`, `ULOG_DEBUG`, `ULOG_INFO`, `ULOG_WARN`, `ULOG_ERROR`, `ULOG_FATAL`.
- `ULOG_PRINT_ERRNO` specifies whether or not to print `errno` from `<stderr.h>`. `0` to not print,
  `1` to print.

### Logging

Use the following functions to log a message. All of these functions are thread safe. They are also blocking
due to the locking of the output file, so make sure to not use them in critical sections.

```c
ulog_trace("trace message");
ulog_debug("debug message");
ulog_info("info message");
ulog_warn("warn message");
ulog_error("error message");
ulog_fatal("fatal message");
```

Depending on `ULOG_LOG_LEVEL` set during compilation some of these messages will be silenced.

All of the function accept a formatting string akin to `printf`.

```c
ulog_trace("trace message %d %d", 4, 2);
```

Example
-------

```c
#define ULOG_IMPLEMENTATION
#include "ulog.h"

int
main(void)
{
	ulog_trace("trace message");
	ulog_debug("debug message");
	ulog_info("info message");
	ulog_warn("warn message");
	ulog_error("error message");
	ulog_fatal("fatal message");

	return 0;
}
```

Which will output:
```
TRACE <example.c:7>: trace message
DEBUG <example.c:8>: debug message
INFO <example.c:9>: info message
WARN <example.c:10>: warn message
ERROR <example.c:11>: error message
FATAL <example.c:12>: fatal message
```

License
-------

zlib license, see LICENSE for more details.

