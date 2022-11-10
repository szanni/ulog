/*--
 * Copyright (c) 2016, Angelo Haller <angelo@szanni.org>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim
 *    that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */
/* ulog version 0.1.0 */

#ifndef ULOG_H
#define ULOG_H

#ifdef _WIN32
#define ULOG_LOCKFILE _lock_file
#define ULOG_UNLOCKFILE _unlock_file
#else
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif
#define ULOG_LOCKFILE flockfile
#define ULOG_UNLOCKFILE funlockfile
#endif //_WIN32
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

enum {
	ULOG_TRACE,
	ULOG_DEBUG,
	ULOG_INFO,
	ULOG_WARN,
	ULOG_ERROR,
	ULOG_FATAL
};

void
_ulog(int log_level, const char *file, int line, int err, const char *format, ...);

#define ulog_trace(...) _ulog(ULOG_TRACE, __FILE__, __LINE__, errno, __VA_ARGS__)
#define ulog_debug(...) _ulog(ULOG_DEBUG, __FILE__, __LINE__, errno, __VA_ARGS__)
#define ulog_info(...) _ulog(ULOG_INFO, __FILE__, __LINE__, errno, __VA_ARGS__)
#define ulog_warn(...) _ulog(ULOG_WARN, __FILE__, __LINE__, errno, __VA_ARGS__)
#define ulog_error(...) _ulog(ULOG_ERROR, __FILE__, __LINE__, errno, __VA_ARGS__)
#define ulog_fatal(...) _ulog(ULOG_FATAL, __FILE__, __LINE__, errno, __VA_ARGS__)

#endif //ULOG_H

#ifdef ULOG_IMPLEMENTATION
#ifndef ULOG_C
#define ULOG_C

#ifndef ULOG_LOG_LEVEL
#define ULOG_LOG_LEVEL ULOG_TRACE
#endif

#ifndef ULOG_PRINT_ERRNO
#define ULOG_PRINT_ERRNO 0
#endif

static const char *_ulog_log_level_string[] = {
	"TRACE",
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL"
};

void
_ulog(int log_level, const char *file, int line, int err, const char *format, ...)
{
	va_list ap;

	if (log_level < ULOG_LOG_LEVEL)
		return;

	ULOG_LOCKFILE(stderr);
	{
#if ULOG_PRINT_ERRNO > 0
		fprintf(stderr, "%s [%s] <%s:%d>: ", _ulog_log_level_string[log_level], strerror(err), file, line);
#else
		(void)err; // silence unused warning
		fprintf(stderr, "%s <%s:%d>: ", _ulog_log_level_string[log_level], file, line);
#endif

		va_start(ap, format);
		vfprintf(stderr, format, ap);
		va_end(ap);

		fprintf(stderr, "%c", '\n');
	}
	ULOG_UNLOCKFILE(stderr);
}

#endif //ULOG_C
#endif //ULOG_IMPLEMENTATION

