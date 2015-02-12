#include "ErrorHandler.h"

namespace core
{
	void ErrorHandler::logError(int lineNumber, std::string filename)
	{
		LOGE("FILE: %s LINE: %i", filename.c_str(), lineNumber);
	}
}