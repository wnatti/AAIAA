#pragma once

#include <string>
#include <android/log.h>
#include <cstdlib>

#ifndef NDEBUG
#define s2d_assert(expression, errorMessage, filename, lineNumber) if(!expression)(core::ErrorHandler::logError(lineNumber, filename, errorMessage))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "s2d_error", __VA_ARGS__))
#endif

namespace core
{
	class ErrorHandler;
}

/**
	Static class.

	Used for assertion-like error handling.
	Handler logs custom message to logcat(tag: s2d_error).
	Aborts program on error while debugging is defined.
*/
class core::ErrorHandler
{
public:

	/**
		Prints error message with filename and line number to logcat.
		Aborts program.
		Use __LINE__ macro for lineNumber and __FILE__ for filename.
	*/
	static void logError(int lineNumber, std::string filename, std::string errorMessage);
};