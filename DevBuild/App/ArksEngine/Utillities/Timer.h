#pragma once
#include <chrono>
#include <iostream>

class Timer {
public:
    // Constructor does not Start the timer
    Timer(int targetTime) : m_TargetTime(targetTime), m_IsRunning(false)
	{
    }

    // Start or restart the timer
    void Start()
	{
        m_Start = std::chrono::system_clock::now();
        m_IsRunning = true;
    }

    // Check if the target time has been reached
    bool HasReachedTarget()
	{
        if (!m_IsRunning) 
        {
            return false;
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - m_Start;
        return elapsed_seconds.count() >= m_TargetTime;
    }

    // Reset the timer
    void Reset()
	{
        m_IsRunning = false;
    }

private:
    int m_TargetTime; // Target time in seconds
    std::chrono::time_point<std::chrono::system_clock> m_Start;
    bool m_IsRunning; // Indicates if the timer is running
};