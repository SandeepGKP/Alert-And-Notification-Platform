#include "UserAlertPreference.h"

std::string UserAlertPreference::todayDate() const {
    auto nowStr = timePointToString(now());
    return nowStr.substr(0, 10); // YYYY-MM-DD
}

UserAlertPreference::UserAlertPreference(std::string id, std::string userId, std::string alertId,
                                         AlertReadStatus readStatus, std::optional<std::string> lastSnoozeDate)
    : id_(std::move(id)), userId_(std::move(userId)), alertId_(std::move(alertId)),
      readStatus_(readStatus), lastSnoozeDate_(std::move(lastSnoozeDate)) {}

const std::string& UserAlertPreference::getId() const { return id_; }
const std::string& UserAlertPreference::getUserId() const { return userId_; }
const std::string& UserAlertPreference::getAlertId() const { return alertId_; }
AlertReadStatus UserAlertPreference::getReadStatus() const { return readStatus_; }
std::optional<std::string> UserAlertPreference::getLastSnoozeDate() const { return lastSnoozeDate_; }

void UserAlertPreference::setReadStatus(AlertReadStatus status) { readStatus_ = status; }

void UserAlertPreference::snoozeToday() {
    readStatus_ = AlertReadStatus::Snoozed;
    lastSnoozeDate_ = todayDate();
}

bool UserAlertPreference::isRead() const {
    return readStatus_ == AlertReadStatus::Read;
}

bool UserAlertPreference::isSnoozedToday() const {
    if (!lastSnoozeDate_.has_value()) return false;
    return lastSnoozeDate_.value() == todayDate() && readStatus_ == AlertReadStatus::Snoozed;
}
