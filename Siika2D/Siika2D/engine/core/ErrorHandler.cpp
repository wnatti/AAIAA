#include "ErrorHandler.h"

namespace core
{
	ErrorHandler* ErrorHandler::_instance;

	ErrorHandler::ErrorHandler()
	{

	}

	ErrorHandler::~ErrorHandler()
	{

	}

	ErrorHandler* ErrorHandler::getInstance()
	{
		if (_instance == nullptr)
			_instance = new ErrorHandler();
		return _instance;
	}

	void ErrorHandler::destroy()
	{
		delete _instance;
		_instance = nullptr;
	}

	void ErrorHandler::checkForError(bool expression, int lineNumber, std::string filename, std::string errorMessage)
	{
		if (!expression)
		{
			// Convert lineNumber int to string
			std::stringstream tempStream;
			tempStream << lineNumber;

			// Print string to logcat
			std::string logString;
			logString = errorMessage + " File: " + filename + " Line: " + tempStream.str();
			LOGE(logString.c_str());

			// If we are debugging abort on error
			#ifdef _DEBUG
				abort();
			#endif
		}
	}
}