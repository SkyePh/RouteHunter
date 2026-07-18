#include <iostream>

std::string getFFUFPath() {
    #ifdef _WIN32
        #if defined(_M_ARM64)
            return "tools/windows/arm64/ffuf.exe";
        #else
            return "tools/windows/amd64/ffuf.exe";
        #endif

    #elif __APPLE__
        #if defined(__aarch64__) || defined(__arm64__)
            return "tools/macos/arm64/ffuf";
        #else
            return "tools/macos/amd64/ffuf";
        #endif

    #elif __linux__
        #if defined(__aarch64__)
            return "tools/linux/arm64/ffuf";
        #else
            return "tools/linux/amd64/ffuf";
        #endif

    #else
        return "";

    #endif

}