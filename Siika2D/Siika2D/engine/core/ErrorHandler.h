#pragma once

#include <sstream>

#include <android/log.h>

#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "s2d_error", __VA_ARGS__))

namespace core
{
	class ErrorHandler;
}

/**
Singleton class.

Used for assertion-like error handling.
Handler logs custom message to logcat(tag: s2d_error).
Aborts program on error while debugging is defined.

*/
class core::ErrorHandler
{
public:
	/**
		Returns existing instance of ErrorHandler if it exists, otherwise creates a new one. 
	*/
	static ErrorHandler* getInstance();

	/**
		Delete instance of ErrorHandler
	*/
	static void destroy();

	/**
		Aborts in debug if expression is false. 
		Prints error message with filename and line number to logcat.

		Use __LINE__ macro for lineNumber and __FILE__ for filename
	*/
	void checkForError(bool expression, int lineNumber, std::string filename, std::string errorMessage);

private:
	ErrorHandler();
	~ErrorHandler();

	static ErrorHandler* _instance;

	

};