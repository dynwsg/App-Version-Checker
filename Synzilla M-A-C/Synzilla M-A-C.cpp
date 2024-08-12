#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <thread>
#include <chrono>

void loadingAnimation() {
    std::cout << "Checking Synzilla Database";
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << ".";
    }
    std::cout << std::endl;
}

void displayVersionInfo(const std::string& appVersion, const std::string& actualVersion) {
    std::cout << "\n--- Version Outdated ---" << std::endl;
    std::cout << "Your Application Version: " << appVersion << std::endl;
    std::cout << "Actual Version from Server: " << actualVersion << std::endl;
    std::cout << "---------------------------" << std::endl;
}

int main() {
    std::string appVersion = "BETA:0.1"; // replace with actual version
    const char* url = "https://8d0c1fcb-5200-41f4-9d0d-b1949132593d-00-30jaebz0c8viv.spock.replit.dev/version.txt"; // ex: the site should say some like 0.1 or etc.

    system(("curl -s -o temp_version.txt " + std::string(url)).c_str()); // fetches the version n saves it to a file then deletes it after comparision lel.

    std::ifstream versionFile("temp_version.txt");
    std::string actualVersion;

    if (versionFile.is_open()) {
        std::getline(versionFile, actualVersion);
        versionFile.close();
    }
    else {
        std::cerr << "Unable to open version file." << std::endl;
        return 1;
    }

    loadingAnimation();

    if (appVersion != actualVersion) {
        displayVersionInfo(appVersion, actualVersion);
        std::cout << "ALERT: This version: " << appVersion
            << " is most likely tampered with. For your safety, Synzilla has saved a restore-point." << std::endl;
    }
    else {
        std::cout << "Versions match! Everything is up to date." << std::endl;
    }

    std::remove("temp_version.txt");

    std::cout << "Closing in 3 seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}
