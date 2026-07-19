#include <iostream>

#include "FFUFCommand.h"

std::string FFUFCommand::buildCommandFlags() {
    std::string cmdFlags = "";

    //add url
    cmdFlags += "-u " + url + " ";
    cmdFlags += "-w " + wordlistPath + " ";
    cmdFlags += "-t " + std::to_string(threads) + " ";
    cmdFlags += "-timeout " + std::to_string(timeout) + " ";
    if (redirects) cmdFlags += "-r ";
    if (autoCal) cmdFlags += "-ac ";
    if (recursion) {
        cmdFlags += "-recursion ";
        cmdFlags += "-recursion-depth " + std::to_string(recursionDepth) + " ";
    }
    if (ignoreBody) cmdFlags += "-ignore-body ";
    if (http2) cmdFlags += "-http2 ";
    if (ignoreWordlistComments) cmdFlags += "-ic ";
    if (!extensions.empty()) cmdFlags += "-e " + extensions + " ";
    if (!filterOutStatuses.empty()) cmdFlags += "-fc " + filterOutStatuses + " ";
    if (!matchStatuses.empty()) cmdFlags += "-mc " + matchStatuses + " ";

    //dont expect input and respsond in json
    cmdFlags += "-noninteractive -json";

    std::cout << cmdFlags << std::endl;

    return cmdFlags;
}
