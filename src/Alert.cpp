#include "Alert.h"

#include <algorithm>

bool Audience::hasAccess(const std::string& teamId, const std::string& userId) const {
    switch (type) {
        case VisibilityType::Organization:
            return true;
        case VisibilityType::Team:
            return std::find(targetIds.begin(), targetIds.end(), teamId) != targetIds.end();
        case VisibilityType::User:
            return std::find(targetIds.begin(), targetIds.end(), userId) != targetIds.end();
        default:
            return false;
    }
}

Alert::Alert(std::string id, std::string title, std::string message, Severity severity,
             DeliveryType deliveryType, Duration reminderFrequency, TimePoint startTime,
             std::optional<TimePoint> expiryTime, bool remindersEnabled)
    : id_(std::move(id)), title_(std::move(title)), message_(std::move(message)), severity_(severity),
      deliveryType_(deliveryType), reminderFrequency_(reminderFrequency), startTime_(startTime),
      expiryTime_(expiryTime), remindersEnabled_(remindersEnabled) {}

const std::string& Alert::getId() const { return id_; }
const std::string& Alert::getTitle() const { return title_; }
const std::string& Alert::getMessage() const { return message_; }
Severity Alert::getSeverity() const { return severity_; }
DeliveryType Alert::getDeliveryType() const { return deliveryType_; }
Duration Alert::getReminderFrequency() const { return reminderFrequency_; }
TimePoint Alert::getStartTime() const { return startTime_; }
std::optional<TimePoint> Alert::getExpiryTime() const { return expiryTime_; }
bool Alert::isRemindersEnabled() const { return remindersEnabled_; }
const Audience& Alert::getAudience() const { return audience_; }

void Alert::setTitle(const std::string& title) { title_ = title; }
void Alert::setMessage(const std::string& message) { message_ = message; }
void Alert::setSeverity(Severity severity) { severity_ = severity; }
void Alert::setDeliveryType(DeliveryType deliveryType) { deliveryType_ = deliveryType; }
void Alert::setReminderFrequency(Duration frequency) { reminderFrequency_ = frequency; }
void Alert::setStartTime(TimePoint startTime) { startTime_ = startTime; }
void Alert::setExpiryTime(std::optional<TimePoint> expiryTime) { expiryTime_ = expiryTime; }
void Alert::setRemindersEnabled(bool enabled) { remindersEnabled_ = enabled; }
void Alert::setAudience(Audience audience) { audience_ = audience; }

bool Alert::isActive() const {
    auto current = now();
    bool afterStart = current >= startTime_;
    bool beforeExpiry = expiryTime_.has_value() ? current <= expiryTime_.value() : true;
    return afterStart && beforeExpiry;
}

bool Alert::hasVisibility(const std::string& teamId, const std::string& userId) const {
    return audience_.hasAccess(teamId, userId);
}
