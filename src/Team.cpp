#include "Team.h"

Team::Team(std::string id, std::string name) : id_(std::move(id)), name_(std::move(name)) {}

const std::string& Team::getId() const {
    return id_;
}

const std::string& Team::getName() const {
    return name_;
}

void Team::setName(const std::string& name) {
    name_ = name;
}
