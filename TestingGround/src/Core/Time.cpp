#include <chrono>
#include <ctime>
#include <string>
#include "Time.hpp"

std::string Time::GetCurrentDateAndTime()
{
    // Get the current system time
    auto now = std::chrono::system_clock::now();

    // Convert the system time to a time_t (time since epoch)
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a struct tm (broken down time)
    std::tm* timeInfo = std::localtime(&time);

    // Create a formatted string
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return buffer;
}