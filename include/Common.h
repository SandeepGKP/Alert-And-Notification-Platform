#pragma once

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>

using namespace std::chrono_literals;

// Common types and enums
enum class Severity {
    Info,
    Warning,
    Critical
};

enum class DeliveryType {
    InApp,
    Email,
    Sms
};

enum class VisibilityType {
    Organization,
    Team,
    User
};

enum class AlertStatus {
    Active,
    Archived,
    Expired
};

enum class AlertReadStatus {
    Unread,
    Read,
    Snoozed
};

// Helper functions
std::string severityToString(Severity s);
Severity stringToSeverity(const std::string& s);
std::string deliveryTypeToString(DeliveryType dt);
DeliveryType stringToDeliveryType(const std::string& dt);
std::string visibilityTypeToString(VisibilityType vt);
VisibilityType stringToVisibilityType(const std::string& vt);
std::string alertStatusToString(AlertStatus as);
AlertStatus stringToAlertStatus(const std::string& as);
std::string alertReadStatusToString(AlertReadStatus ars);
AlertReadStatus stringToAlertReadStatus(const std::string& ars);

using TimePoint = std::chrono::system_clock::time_point;
using Duration = std::chrono::hours;

inline TimePoint now() {
    return std::chrono::system_clock::now();
}

inline std::string timePointToString(const TimePoint& tp) {
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm;
    localtime_s(&tm, &tt);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return buffer;
}

inline TimePoint stringToTimePoint(const std::string& str) {
    std::tm tm;
    std::istringstream iss(str);
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (iss.fail()) {
        throw std::invalid_argument("Invalid time format");
    }
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}
