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
