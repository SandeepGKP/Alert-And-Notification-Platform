#pragma once

#include <string>

class Team {
public:
    explicit Team(std::string id, std::string name);
    ~Team() = default;

    // Getters
    const std::string& getId() const;
    const std::string& getName() const;

    // Setters
    void setName(const std::string& name);

private:
    std::string id_;
    std::string name_;
};
