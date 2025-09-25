#include "User.h"

User::User(std::string id, std::string name, std::string teamId)
    : id_(std::move(id)), name_(std::move(name)), teamId_(std::move(teamId)) {}

const std::string& User::getId() const {
    return id_;
}

const std::string& User::getName() const {
    return name_;
}

const std::string& User::getTeamId() const {
    return teamId_;
}

void User::setName(const std::string& name) {
    name_ = name;
}

void User::setTeamId(const std::string& teamId) {
    teamId_ = teamId;
}
