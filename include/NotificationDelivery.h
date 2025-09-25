#pragma once

#include "Common.h"

#include <string>

class NotificationDelivery {
public:
    explicit NotificationDelivery(std::string id, std::string alertId, std::string userId,
                                  TimePoint deliveryTime, DeliveryType channel);
    ~NotificationDelivery() = default;

    // Getters
    const std::string& getId() const;
    const std::string& getAlertId() const;
    const std::string& getUserId() const;
    TimePoint getDeliveryTime() const;
    DeliveryType getChannel() const;

    // No setters as logs are immutable

    // JSON serialization - to be added with JSON library integration

private:
    std::string id_;
    std::string alertId_;
    std::string userId_;
    TimePoint deliveryTime_;
    DeliveryType channel_;
};
