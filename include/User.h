#pragma once

#include <string>

class User {
public:
    explicit User(std::string id, std::string name, std::string teamId);
    ~User() = default;

    // Getters
    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getTeamId() const;

    // Setters
    void setName(const std::string& name);
    void setTeamId(const std::string& teamId);

    // JSON serialization - to be added with JSON library integration

private:
    std::string id_;
    std::string name_;
    std::string teamId_;
};
