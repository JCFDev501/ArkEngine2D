// Jaylin Ferrell

// This is a small and improving implementation of my logging system

#include "Debug_Log.h"
#include <iostream>
#include <fstream>

///////////////////////////////////////////////////////////////////////////
/// This will let users log certain events that occur in the engine or game.
///	Once the user logs the event the entry will be written to a text file.
///////////////////////////////////////////////////////////////////////////
void ArksEngine::Debug_Log::Log(const std::string& msg) const
{

	SetConsoleTextAttribute(m_hConsole, 10);
	// Print message to console
	std::cout << "Log: " << msg << std::endl;

	// Write log to txt file.....

	// Open a log file
	std::ofstream arkELogs;

	arkELogs.open("ArkELogs.txt", std::ios::app);

	// Write to the file
	arkELogs << "Log: " << msg << "\n";

	// Close the file
	arkELogs.close();
}

void ArksEngine::Debug_Log::Warning(const std::string& msg) const
{
	SetConsoleTextAttribute(m_hConsole, 14);

	// Print message to console
	std::cout << "Warning: " << msg << std::endl;

	// Write log to txt file.....

	// Open a log file
	std::ofstream arkELogs;

	arkELogs.open("ArkELogs.txt", std::ios::app);

	// Write to the file
	arkELogs << "Log: " << msg << "\n";

	// Close the file
	arkELogs.close();
}

void ArksEngine::Debug_Log::Error(const std::string& msg) const
{
	SetConsoleTextAttribute(m_hConsole, 12);
	// Print message to console
	std::cout << "Error: " << msg << std::endl;

	// Write log to txt file.....

	// Open a log file
	std::ofstream arkELogs;

	arkELogs.open("ArkELogs.txt", std::ios::app);

	// Write to the file
	arkELogs << "Log: " << msg << "\n";

	// Close the file
	arkELogs.close();
}

/**
 * \brief
 * Clears the current log file i Call this in greetings so i can make sure that all previous logs are gone.
 */
void ArksEngine::Debug_Log::ArksEClearLogs()
{
	// Open a log file
	std::ofstream arkELogs;

	arkELogs.open("ArkELogs.txt");

	// Clear logs
	arkELogs.clear();

	// Close the file
	arkELogs.close();
}
