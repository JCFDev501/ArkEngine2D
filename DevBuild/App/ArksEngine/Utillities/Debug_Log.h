// Jaylin Ferrell

//////////////////////////////////////////////////////////////////////////////////////
// ArkEngine Logging system, This will Log to the console and it will write to a file
// and Document all past and current logs
//////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <windows.h> 

namespace ArksEngine
{
	
	class Debug_Log
	{

		HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	public:

		Debug_Log() = default;
		~Debug_Log() = default;

		void Log(const std::string& msg) const;
		void Warning(const std::string& msg) const;
		void Error(const std::string& msg) const;


		

		static void ArksEClearLogs();
	};
}


