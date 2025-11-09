#include <iostream>
#include <string>
#include "SocialNet.hpp"

int main() {
    SocialNet net;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            net.processCommand(line);
        }
    }

    return 0;
}