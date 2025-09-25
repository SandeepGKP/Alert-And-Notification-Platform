#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "Alert.h"
#include "UserAlertPreference.h"

struct AlertMetrics {
    int totalCreated;
    int totalActive;
    int totalExpired;
    int totalArchived;
    std::unordered_map<std::string, int> bySeverity;
    std::unordered_map<std::string, int> byStatus;
};

struct DeliveryMetrics {
    int totalDelivered;
    int totalRead;
    int totalSnoozed;
    double deliveryRate; // delivered/total users
    double readRate; // read/delivered
    double snoozeRate; // snoozed/delivered
};

class Analytics {
public:
    Analytics() = default;

    // Update metrics (would be called on operations)
    void onAlertCreated(const Alert& alert);
    void onAlertUpdated();
    void onUserDeliveredAlert(const std::string& alertId, const std::string& userId);
    void onUserReadAlert(const std::string& alertId, const std::string& userId);
    void onUserSnoozedAlert(const std::string& alertId, const std::string& userId);

    // Get metrics
    AlertMetrics getAlertMetrics() const;
    DeliveryMetrics getDeliveryMetrics() const;
    std::unordered_map<std::string, DeliveryMetrics> getPerAlertMetrics() const;

private:
    AlertMetrics alertMetrics;
    DeliveryMetrics deliveryMetrics;
    std::unordered_map<std::string, DeliveryMetrics> perAlertMetrics; // alertId -> metrics
    std::unordered_map<std::string, std::unordered_set<std::string>> alertDeliveries; // alertId -> userIds delivered
    std::unordered_map<std::string, std::unordered_set<std::string>> alertReads; // alertId -> userIds read
    std::unordered_map<std::string, std::unordered_set<std::string>> alertSnoozes; // alertId -> userIds snoozed
};

// Global analytics instance
extern Analytics globalAnalytics;
