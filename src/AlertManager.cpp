#include "AlertManager.h"

#include <algorithm>
#include <memory>

void AlertManager::createAlert(Alert alert) {
    alerts_.push_back(std::make_shared<Alert>(std::move(alert)));
}

void AlertManager::updateAlert(const std::string& alertId, const Alert& updatedAlert) {
    auto it = std::find_if(alerts_.begin(), alerts_.end(),
                           [&](const auto& a) { return a->getId() == alertId; });
    if (it != alerts_.end()) {
        **it = updatedAlert;
    }
}

void AlertManager::archiveAlert(const std::string& alertId) {
    // In production, set status to Archived, but for now remove
    auto it = std::find_if(alerts_.begin(), alerts_.end(),
                           [&](const auto& a) { return a->getId() == alertId; });
    if (it != alerts_.end()) {
        alerts_.erase(it);
    }
}

void AlertManager::toggleReminders(const std::string& alertId, bool enable) {
    auto it = std::find_if(alerts_.begin(), alerts_.end(),
                           [&](const auto& a) { return a->getId() == alertId; });
    if (it != alerts_.end()) {
        (*it)->setRemindersEnabled(enable);
    }
}

std::vector<std::shared_ptr<Alert>> AlertManager::getAllAlerts() const {
    return alerts_;
}

std::vector<std::shared_ptr<Alert>> AlertManager::filterAlerts(AlertStatus status) const {
    std::vector<std::shared_ptr<Alert>> filtered;
    for (const auto& alert : alerts_) {
        // Simplified: active means isActive()
        if (status == AlertStatus::Active && alert->isActive()) {
            filtered.push_back(alert);
        }
    }
    return filtered;
}

std::vector<std::shared_ptr<Alert>> AlertManager::filterBySeverity(Severity severity) const {
    std::vector<std::shared_ptr<Alert>> filtered;
    for (const auto& alert : alerts_) {
        if (alert->getSeverity() == severity) {
            filtered.push_back(alert);
        }
    }
    return filtered;
}

std::vector<std::shared_ptr<Alert>> AlertManager::filterByAudience(const std::string& teamId, const std::string& userId) const {
    std::vector<std::shared_ptr<Alert>> filtered;
    for (const auto& alert : alerts_) {
        if (alert->hasVisibility(teamId.empty() ? "" : teamId, userId.empty() ? "" : userId)) {
            filtered.push_back(alert);
        }
    }
    return filtered;
}

std::shared_ptr<Alert> AlertManager::findAlert(const std::string& alertId) const {
    auto it = std::find_if(alerts_.begin(), alerts_.end(),
                           [&](const auto& a) { return a->getId() == alertId; });
    return it != alerts_.end() ? *it : nullptr;
}
