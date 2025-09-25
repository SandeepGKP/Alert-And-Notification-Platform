#include "Common.h"

#include <algorithm>

std::string severityToString(Severity s) {
    switch (s) {
        case Severity::Info: return "Info";
        case Severity::Warning: return "Warning";
        case Severity::Critical: return "Critical";
        default: return "Unknown";
    }
}

Severity stringToSeverity(const std::string& s) {
    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "info") return Severity::Info;
    if (lower == "warning") return Severity::Warning;
    if (lower == "critical") return Severity::Critical;
    throw std::invalid_argument("Invalid severity: " + s);
}

std::string deliveryTypeToString(DeliveryType dt) {
    switch (dt) {
        case DeliveryType::InApp: return "InApp";
        case DeliveryType::Email: return "Email";
        case DeliveryType::Sms: return "Sms";
        default: return "Unknown";
    }
}

DeliveryType stringToDeliveryType(const std::string& dt) {
    std::string lower = dt;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "inapp") return DeliveryType::InApp;
    if (lower == "email") return DeliveryType::Email;
    if (lower == "sms") return DeliveryType::Sms;
    throw std::invalid_argument("Invalid delivery type: " + dt);
}

std::string visibilityTypeToString(VisibilityType vt) {
    switch (vt) {
        case VisibilityType::Organization: return "Organization";
        case VisibilityType::Team: return "Team";
        case VisibilityType::User: return "User";
        default: return "Unknown";
    }
}

VisibilityType stringToVisibilityType(const std::string& vt) {
    std::string lower = vt;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "organization") return VisibilityType::Organization;
    if (lower == "team") return VisibilityType::Team;
    if (lower == "user") return VisibilityType::User;
    throw std::invalid_argument("Invalid visibility type: " + vt);
}

std::string alertStatusToString(AlertStatus as) {
    switch (as) {
        case AlertStatus::Active: return "Active";
        case AlertStatus::Archived: return "Archived";
        case AlertStatus::Expired: return "Expired";
        default: return "Unknown";
    }
}

AlertStatus stringToAlertStatus(const std::string& as) {
    std::string lower = as;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "active") return AlertStatus::Active;
    if (lower == "archived") return AlertStatus::Archived;
    if (lower == "expired") return AlertStatus::Expired;
    throw std::invalid_argument("Invalid alert status: " + as);
}

std::string alertReadStatusToString(AlertReadStatus ars) {
    switch (ars) {
        case AlertReadStatus::Unread: return "Unread";
        case AlertReadStatus::Read: return "Read";
        case AlertReadStatus::Snoozed: return "Snoozed";
        default: return "Unknown";
    }
}

AlertReadStatus stringToAlertReadStatus(const std::string& ars) {
    std::string lower = ars;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "unread") return AlertReadStatus::Unread;
    if (lower == "read") return AlertReadStatus::Read;
    if (lower == "snoozed") return AlertReadStatus::Snoozed;
    throw std::invalid_argument("Invalid read status: " + ars);
}
