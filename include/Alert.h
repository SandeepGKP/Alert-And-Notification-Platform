#pragma once

#include "Common.h"

#include <string>
#include <vector>
#include <optional>

struct Audience {
    VisibilityType type;
    std::vector<std::string> targetIds; // empty for org, team ids, user ids

    bool hasAccess(const std::string& teamId, const std::string& userId) const;
};

class Alert {
public:
    explicit Alert(std::string id, std::string title, std::string message, Severity severity,
                   DeliveryType deliveryType, Duration reminderFrequency, TimePoint startTime,
                   std::optional<TimePoint> expiryTime, bool remindersEnabled);

    ~Alert() = default;

    // Getters
    const std::string& getId() const;
    const std::string& getTitle() const;
    const std::string& getMessage() const;
    Severity getSeverity() const;
    DeliveryType getDeliveryType() const;
    Duration getReminderFrequency() const;
    TimePoint getStartTime() const;
    std::optional<TimePoint> getExpiryTime() const;
    bool isRemindersEnabled() const;
    const Audience& getAudience() const;

    // Setters
    void setTitle(const std::string& title);
    void setMessage(const std::string& message);
    void setSeverity(Severity severity);
    void setDeliveryType(DeliveryType deliveryType);
    void setReminderFrequency(Duration frequency);
    void setStartTime(TimePoint startTime);
    void setExpiryTime(std::optional<TimePoint> expiryTime);
    void setRemindersEnabled(bool enabled);
    void setAudience(Audience audience);

    // Computed properties
    bool isActive() const;
    bool hasVisibility(const std::string& teamId, const std::string& userId) const;

private:
    std::string id_;
    std::string title_;
    std::string message_;
    Severity severity_;
    DeliveryType deliveryType_;
    Duration reminderFrequency_;
    TimePoint startTime_;
    std::optional<TimePoint> expiryTime_;
    bool remindersEnabled_;
    Audience audience_;
};
