#pragma once

#include "Common.h"

#include <string>
#include <optional>

class UserAlertPreference {
public:
    explicit UserAlertPreference(std::string id, std::string userId, std::string alertId,
                                  AlertReadStatus readStatus, std::optional<std::string> lastSnoozeDate);
    ~UserAlertPreference() = default;

    // Getters
    const std::string& getId() const;
    const std::string& getUserId() const;
    const std::string& getAlertId() const;
    AlertReadStatus getReadStatus() const;
    std::optional<std::string> getLastSnoozeDate() const;

    // Setters
    void setReadStatus(AlertReadStatus status);
    void snoozeToday(); // Sets lastSnoozeDate to today

    // Computed properties
    bool isRead() const;
    bool isSnoozedToday() const; // Checks if lastSnoozeDate is today

    // JSON serialization - to be added with JSON library integration

private:
    std::string todayDate() const;

    std::string id_;
    std::string userId_;
    std::string alertId_;
    AlertReadStatus readStatus_;
    std::optional<std::string> lastSnoozeDate_; // YYYY-MM-DD
};
