#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <chrono>

#include "AlertManager.h"
#include "Team.h"
#include "User.h"
#include "Alert.h"
#include "UserAlertPreference.h"
#include "Analytics.h"

void printHeader() {
    std::cout << "\n===========================================";
    std::cout << "\n         ALERTING & NOTIFICATION PLATFORM";
    std::cout << "\n===========================================";
}

void displayMenu() {
    printHeader();
    std::cout << "\n\nMAIN MENU";
    std::cout << "\n--------";
    std::cout << "\n1. Admin Operations";
    std::cout << "\n2. User Operations";
    std::cout << "\n3. Analytics Dashboard";
    std::cout << "\n4. Exit";
    std::cout << "\n\nEnter choice (1-4): ";
}

void displayAdminMenu() {
    std::cout << "\n\nADMIN OPERATIONS";
    std::cout << "\n---------------";
    std::cout << "\n1. Create Alert";
    std::cout << "\n2. Update Alert";
    std::cout << "\n3. Archive Alert";
    std::cout << "\n4. Toggle Reminders";
    std::cout << "\n5. List Alerts";
    std::cout << "\n6. Filter by Status";
    std::cout << "\n7. Filter by Severity";
    std::cout << "\n8. Filter by Audience";
    std::cout << "\n9. View Alert Read Status";
    std::cout << "\n10. Back to Main Menu";
    std::cout << "\n\nEnter choice (1-10): ";
}

void printStatusMessage(const std::string& message, const std::string& icon = "[INFO] ") {
    std::cout << "\n" << icon << message << "\n";
}

void printAlertList(const std::string& title, const std::vector<std::shared_ptr<Alert>>& alerts, bool showReminders = false) {
    if (alerts.empty()) {
        std::cout << "\nNo alerts found.\n";
        return;
    }

    std::cout << "\n" << title << "\n";
    std::cout << std::string(50, '-') << "\n";

    int count = 0;
    for (const auto& alert : alerts) {
        if (alert->isActive()) {
            count++;
            std::string severityIcon;
            if (alert->getSeverity() == Severity::Critical) severityIcon = "[CRITICAL]";
            else if (alert->getSeverity() == Severity::Warning) severityIcon = "[WARNING]";
            else severityIcon = "[INFO]";

            std::cout << count << ". " << severityIcon << " " << alert->getTitle();
            if (showReminders) {
                std::cout << " (Reminders: " << (alert->isRemindersEnabled() ? "ON" : "OFF") << ")";
            }
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

std::string generateAlertId() {
    static int idCounter = 100;
    return "alert" + std::to_string(idCounter++);
}

Alert createCustomAlert() {
    std::string title, message;
    int severityChoice;
    char audienceChoice;

    std::cout << "\n--- Create New Alert ---" << std::endl;
    std::cout << "Enter alert title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter alert message: ";
    std::getline(std::cin, message);
    std::cout << "Choose severity [0=Info, 1=Warning, 2=Critical]: ";
    std::cin >> severityChoice;

    Severity severity = static_cast<Severity>(severityChoice);
    if (severityChoice < 0 || severityChoice > 2) {
        std::cout << "Invalid severity, defaulting to Warning.\n";
        severity = Severity::Warning;
    }

    std::cout << "Choose audience scope [o=Organization wide, t=Team specific]: ";
    std::cin >> audienceChoice;

    Audience audience;
    std::string teamId;

    if (audienceChoice == 't') {
        audience.type = VisibilityType::Team;
        std::cout << "Enter team ID [team1=Engineering, team2=Marketing]: ";
        std::cin >> teamId;
        audience.targetIds = {teamId};
    } else {
        audience.type = VisibilityType::Organization;
        audience.targetIds = {};
    }

    std::string alertId = generateAlertId();
    Alert newAlert(alertId, title, message, severity, DeliveryType::InApp,
                   std::chrono::hours(2), now(), std::optional<TimePoint>(), true);
    newAlert.setAudience(audience);

    return newAlert;
}

int main() {
    AlertManager alertManager;

    // Seed data - PRD requirement for testing visibility
    Team eng("team1", "Engineering");
    Team mkt("team2", "Marketing");

    User user1("user1", "Alice", "team1");
    User user2("user2", "Bob", "team1");
    User user3("user3", "Charlie", "team2");

    // Create initial alerts for testing
    Audience engineeringAudience;
    engineeringAudience.type = VisibilityType::Team;
    engineeringAudience.targetIds = {"team1"};

    Alert alert1("alert1", "Server Maintenance", "Scheduled maintenance tonight",
                Severity::Warning, DeliveryType::InApp,
                std::chrono::hours(2), now(),
                std::optional<TimePoint>(), true);
    alert1.setAudience(engineeringAudience);

    Audience orgAudience;
    orgAudience.type = VisibilityType::Organization;
    orgAudience.targetIds = {};

    Alert alert2("alert2", "System Update", "Critical update required",
                Severity::Critical, DeliveryType::InApp,
                std::chrono::hours(2), now(),
                std::optional<TimePoint>(), true);
    alert2.setAudience(orgAudience);

    alertManager.createAlert(std::move(alert1));
    alertManager.createAlert(std::move(alert2));

    // User preferences for Alice (user1) - PRD requirement - dynamically managed
    std::vector<UserAlertPreference> userPrefs;

    // Helper to ensure user preferences exist for all alerts visible to alice
    auto ensureUserPrefs = [&](const std::vector<std::shared_ptr<Alert>>& allAlerts) {
        static int prefCounter = 1;
        for (const auto& alert : allAlerts) {
            if (alert->isActive() && alert->hasVisibility("team1", "user1")) {
                bool found = false;
                for (const auto& pref : userPrefs) {
                    if (pref.getAlertId() == alert->getId()) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    userPrefs.emplace_back("pref" + std::to_string(prefCounter++), "user1",
                                           alert->getId(), AlertReadStatus::Unread, std::nullopt);
                }
            }
        }
    };

    // Initialize with base alerts
    ensureUserPrefs(alertManager.getAllAlerts());

    std::cout << "Alerting & Notification Platform - PRD Compliant Demo";
    std::cout << "\nDynamic alert creation enabled. Test all PRD features interactively.\n";

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Admin submenu - PRD Admin requirements
            while (true) {
                displayAdminMenu();
                int adminChoice;
                std::cin >> adminChoice;

                if (adminChoice == 1) {
                    // PRD: Create unlimited alerts with configured visibility - NOW DYNAMIC!
                    Alert newAlert = createCustomAlert();
                    alertManager.createAlert(std::move(newAlert));
                    printStatusMessage("Custom alert created successfully!", "[SUCCESS]");
                } else if (adminChoice == 2) {
                    // PRD: Update alerts
                    printStatusMessage("Demo: Alert updated to 'Urgent Maintenance'", "[UPDATE]");
                    auto existing = alertManager.findAlert("alert1");
                    if (existing) {
                        Alert updated = *existing;
                        updated.setTitle("Urgent Maintenance");
                        updated.setSeverity(Severity::Critical);
                        alertManager.updateAlert("alert1", updated);
                    }
                } else if (adminChoice == 3) {
                    // PRD: Archive alerts
                    printStatusMessage("Demo: Alert archived (no longer active)", "[ARCHIVED]");
                    alertManager.archiveAlert("alert1");
                } else if (adminChoice == 4) {
                    // PRD: Enable/disable reminders
                    printStatusMessage("Demo: Reminders toggled for critical alert", "[TOGGLE]");
                    alertManager.toggleReminders("alert2", false);
                } else if (adminChoice == 5) {
                    // PRD: List all created alerts
                    auto alerts = alertManager.getAllAlerts();
                    printAlertList("ALL ALERTS OVERVIEW", alerts, true);
                } else if (adminChoice == 6) {
                    // PRD: Filter by status (active/expired)
                    auto activeAlerts = alertManager.filterAlerts(AlertStatus::Active);
                    printAlertList("ACTIVE ALERTS ONLY", activeAlerts);
                } else if (adminChoice == 7) {
                    // PRD: Filter by severity
                    std::cout << "Choose severity [0=Info, 1=Warning, 2=Critical]: ";
                    int sev;
                    std::cin >> sev;
                    Severity severity = static_cast<Severity>(sev);
                    auto alerts = alertManager.filterBySeverity(severity);
                    std::string title = std::string(severityToString(severity)) + " ALERTS";
                    printAlertList(title, alerts);
                } else if (adminChoice == 8) {
                    // PRD: Filter by audience
                    std::cout << "Choose scope [o=Organization, t=Team]: ";
                    char scope;
                    std::cin >> scope;
                    if (scope == 't') {
                        auto teamAlerts = alertManager.filterByAudience("team1", "");
                        printAlertList("TEAM VISIBILITY ALERTS", teamAlerts);
                    } else {
                        auto orgAlerts = alertManager.filterByAudience();
                        printAlertList("ORGANIZATION WIDE ALERTS", orgAlerts);
                    }
                } else if (adminChoice == 9) {
                    // PRD: NEW FEATURE - View who read alerts
                    printStatusMessage("ALERT READ STATUS DASHBOARD");

                    ensureUserPrefs(alertManager.getAllAlerts());
                    auto allAlerts = alertManager.getAllAlerts();

                    std::cout << "\nALERT READ STATUS BY USER:" << std::endl;
                    std::cout << std::string(60, '=') << std::endl;

                    for (const auto& alert : allAlerts) {
                        if (alert->isActive()) {
                            std::string severityStr = "UNKNOWN";
                            if (alert->getSeverity() == Severity::Critical) severityStr = "CRITICAL";
                            else if (alert->getSeverity() == Severity::Warning) severityStr = "WARNING";
                            else if (alert->getSeverity() == Severity::Info) severityStr = "INFO";
                            std::cout << "\nALERT: " << alert->getTitle() << " [" << severityStr << "]" << std::endl;
                            std::cout << "MESSAGE: " << alert->getMessage() << std::endl;
                            std::cout << "READ STATUS BY USERS:" << std::endl;

                            // Check for Alice (Engineering team)
                            if (alert->hasVisibility("team1", "user1")) {
                                AlertReadStatus aliceStatus = AlertReadStatus::Unread;
                                for (const auto& pref : userPrefs) {
                                    if (pref.getAlertId() == alert->getId() && pref.getUserId() == "user1") {
                                        aliceStatus = pref.getReadStatus();
                                        break;
                                    }
                                }
                                std::cout << "  - Alice (Engineering): " << alertReadStatusToString(aliceStatus);
                                if (aliceStatus == AlertReadStatus::Snoozed) {
                                    std::cout << " (currently snoozed)";
                                }
                                std::cout << std::endl;
                            }

                            // Check for Bob (Engineering team)
                            if (alert->hasVisibility("team1", "user2")) {
                                std::cout << "  - Bob (Engineering): Unread (demo - no interaction)" << std::endl;
                            }

                            // Check for Charlie (Marketing team)
                            if (alert->hasVisibility("team2", "user3")) {
                                std::cout << "  - Charlie (Marketing): Unread (demo - no interaction)" << std::endl;
                            }

                            std::cout << std::endl;
                        }
                    }

                    printStatusMessage("Press Enter to return to main menu...");
                    std::cin.ignore();
                    std::cin.get();
                } else if (adminChoice == 10) {
                    break;
                } else {
                    printStatusMessage("Invalid input - exiting application", "[ERROR]");
                    return 0;
                }
            }
        } else if (choice == 2) {
            // User submenu - Simple demonstration
            std::cout << "\n\nUSER OPERATIONS (Demo)";
            std::cout << "\n---------------------";
            std::cout << "\n1. View My Alerts";
            std::cout << "\n2. Mark Alert as Read";
            std::cout << "\n3. Snooze Alert";
            std::cout << "\n4. Back to Main Menu";
            std::cout << "\n\nEnter choice (1-4): ";

            int userChoice;
            std::cin >> userChoice;

            if (userChoice == 1) {
                // PRD: View alerts in dashboard

                // Ensure prefs are up to date
                ensureUserPrefs(alertManager.getAllAlerts());

                printStatusMessage("Alice's Active Alerts (Engineering team):");
                auto alerts = alertManager.getAllAlerts();
                for (const auto& a : alerts) {
                    if (a->isActive() && a->hasVisibility("team1", "user1")) {
                        // Find the corresponding preference
                        AlertReadStatus currentStatus = AlertReadStatus::Unread;
                        for (const auto& pref : userPrefs) {
                            if (pref.getAlertId() == a->getId() && pref.getUserId() == "user1") {
                                currentStatus = pref.getReadStatus();
                                break;
                            }
                        }

                        std::cout << "  - " << a->getTitle() << ": " << a->getMessage() << "\n     ";
                        std::cout << "Status: [" << alertReadStatusToString(currentStatus) << "]";
                        if (currentStatus == AlertReadStatus::Snoozed) {
                            std::cout << " - Snoozed until tomorrow";
                        }
                        std::cout << "\n\n";
                    }
                }
            } else if (userChoice == 2) {
                // PRD: Mark alerts as read/unread - show alerts and let user choose
                ensureUserPrefs(alertManager.getAllAlerts());

                auto alerts = alertManager.getAllAlerts();
                std::vector<std::shared_ptr<Alert>> visibleAlerts;

                std::cout << "\nSelect alert to mark as read:\n";
                int alertNum = 1;
                for (const auto& a : alerts) {
                    if (a->isActive() && a->hasVisibility("team1", "user1")) {
                        visibleAlerts.push_back(a);

                        // Check current status
                        AlertReadStatus currentStatus = AlertReadStatus::Unread;
                        for (const auto& pref : userPrefs) {
                            if (pref.getAlertId() == a->getId() && pref.getUserId() == "user1") {
                                currentStatus = pref.getReadStatus();
                                break;
                            }
                        }

                        std::cout << alertNum << ". " << a->getTitle() << " [Currently " << alertReadStatusToString(currentStatus) << "]\n";
                        alertNum++;
                    }
                }

                if (!visibleAlerts.empty()) {
                    std::cout << "Enter number (or 0 to cancel): ";
                    int selection;
                    std::cin >> selection;

                    if (selection > 0 && selection <= static_cast<int>(visibleAlerts.size())) {
                        auto selectedAlert = visibleAlerts[selection - 1];
                        // Mark as read
                        for (auto& pref : userPrefs) {
                            if (pref.getAlertId() == selectedAlert->getId() && pref.getUserId() == "user1") {
                                pref.setReadStatus(AlertReadStatus::Read);
                                break;
                            }
                        }
                        printStatusMessage("Alert marked as read", "[SUCCESS]");
                    }
                } else {
                    std::cout << "No alerts available.\n";
                }
            } else if (userChoice == 3) {
                // PRD: Snooze alerts for current day - show alerts and let user choose
                ensureUserPrefs(alertManager.getAllAlerts());

                auto alerts = alertManager.getAllAlerts();
                std::vector<std::shared_ptr<Alert>> visibleAlerts;

                std::cout << "\nSelect alert to snooze:\n";
                int alertNum = 1;
                for (const auto& a : alerts) {
                    if (a->isActive() && a->hasVisibility("team1", "user1")) {
                        visibleAlerts.push_back(a);
                        std::cout << alertNum << ". " << a->getTitle() << "\n";
                        alertNum++;
                    }
                }

                if (!visibleAlerts.empty()) {
                    std::cout << "Enter number (or 0 to cancel): ";
                    int selection;
                    std::cin >> selection;

                    if (selection > 0 && selection <= static_cast<int>(visibleAlerts.size())) {
                        auto selectedAlert = visibleAlerts[selection - 1];
                        // Snooze today
                        for (auto& pref : userPrefs) {
                            if (pref.getAlertId() == selectedAlert->getId() && pref.getUserId() == "user1") {
                                pref.snoozeToday();
                                break;
                            }
                        }
                        printStatusMessage("Alert snoozed for today", "[SNOOZED]");
                    }
                } else {
                    std::cout << "No alerts available.\n";
                }
            } else if (userChoice == 4) {
                // Back to main menu
                break;
            } else {
                printStatusMessage("Invalid input - exiting application", "[ERROR]");
                return 0;
            }
        } else if (choice == 3) {
            // PRD: Analytics Dashboard
            printStatusMessage("ANALYTICS DASHBOARD");

            auto allAlerts = alertManager.getAllAlerts();
            auto activeAlerts = alertManager.filterAlerts(AlertStatus::Active);

            int infoCount = 0, warningCount = 0, criticalCount = 0;

            for (const auto& alert : allAlerts) {
                if (alert->getSeverity() == Severity::Info) infoCount++;
                else if (alert->getSeverity() == Severity::Warning) warningCount++;
                else if (alert->getSeverity() == Severity::Critical) criticalCount++;
            }

            std::cout << "\nSYSTEM OVERVIEW:" << std::endl;
            std::cout << std::string(40, '=') << std::endl;
            std::cout << std::left << std::setw(25) << "- Total alerts created:" << std::right << std::setw(10) << allAlerts.size() << "\n";
            std::cout << std::left << std::setw(25) << "- Active alerts:" << std::right << std::setw(10) << activeAlerts.size() << "\n";
            std::cout << std::left << std::setw(25) << "- Total users:" << std::right << std::setw(10) << 3 << "\n";
            std::cout << std::left << std::setw(25) << "- Teams configured:" << std::right << std::setw(10) << 2 << "\n";
            std::cout << std::left << std::setw(25) << "- System status:" << std::right << std::setw(10) << "Healthy" << "\n\n";

            std::cout << "USER ENGAGEMENT SUMMARY:" << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            std::cout << std::left << std::setw(30) << "- Alice (Engineering):" << std::right << std::setw(10) << "Active [" << userPrefs.size() << " alerts]" << "\n";
            std::cout << std::left << std::setw(30) << "- Bob (Engineering):" << std::right << std::setw(10) << "Demo" << "\n";
            std::cout << std::left << std::setw(30) << "- Charlie (Marketing):" << std::right << std::setw(10) << "Demo" << "\n\n";

            std::cout << "\nSEVERITY BREAKDOWN:" << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            std::cout << std::left << std::setw(25) << "- Info alerts:" << std::right << std::setw(10) << infoCount << "\n";
            std::cout << std::left << std::setw(25) << "- Warning alerts:" << std::right << std::setw(10) << warningCount << "\n";
            std::cout << std::left << std::setw(25) << "- Critical alerts:" << std::right << std::setw(10) << criticalCount << "\n\n";

            printStatusMessage("Press Enter to continue...");
            std::cin.ignore();
            std::cin.get();
        } else if (choice == 4) {
            break;
        } else {
            printStatusMessage("Invalid input - exiting application", "[ERROR]");
            return 0;
        }
    }

    std::cout << "\nGoodbye! All PRD features demonstrated.\n";
    return 0;
}
