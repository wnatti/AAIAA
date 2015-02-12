#include "ErrorHandler.h"

namespace core
{
	void ErrorHandler::logError(int lineNumber, std::string filename, std::string errorMessage)
	{
		LOGE("s% FILE: s% LINE: i%", errorMessage.c_str(), filename.c_str(), lineNumber);
		abort();
	}
}