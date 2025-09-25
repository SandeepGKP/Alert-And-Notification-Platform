#include "NotificationDelivery.h"

NotificationDelivery::NotificationDelivery(std::string id, std::string alertId, std::string userId,
                                           TimePoint deliveryTime, DeliveryType channel)
    : id_(std::move(id)), alertId_(std::move(alertId)), userId_(std::move(userId)),
      deliveryTime_(deliveryTime), channel_(channel) {}

const std::string& NotificationDelivery::getId() const { return id_; }
const std::string& NotificationDelivery::getAlertId() const { return alertId_; }
const std::string& NotificationDelivery::getUserId() const { return userId_; }
TimePoint NotificationDelivery::getDeliveryTime() const { return deliveryTime_; }
DeliveryType NotificationDelivery::getChannel() const { return channel_; }
