#pragma once

#include <vector>
#include <memory>

#include "Alert.h"

class AlertManager {
public:
    AlertManager() = default;
    ~AlertManager() = default;

    // Admin operations
    void createAlert(Alert alert);
    void updateAlert(const std::string& alertId, const Alert& updatedAlert);
    void archiveAlert(const std::string& alertId);
    void toggleReminders(const std::string& alertId, bool enable);

    std::vector<std::shared_ptr<Alert>> getAllAlerts() const;
    std::vector<std::shared_ptr<Alert>> filterAlerts(AlertStatus status = AlertStatus::Active) const;
    std::vector<std::shared_ptr<Alert>> filterBySeverity(Severity severity) const;
    std::vector<std::shared_ptr<Alert>> filterByAudience(const std::string& teamId = "", const std::string& userId = "") const;

    // Find
    std::shared_ptr<Alert> findAlert(const std::string& alertId) const;

private:
    std::vector<std::shared_ptr<Alert>> alerts_;
};
