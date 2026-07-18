#ifndef ROUTEHUNTER_FFUFCOMMAND_H
#define ROUTEHUNTER_FFUFCOMMAND_H

#include <iostream>

class FFUFCommand {
public:
    std::string url;
    unsigned short threads;
    std::string wordlistPath = "../wordlists/";
    bool redirects;
    bool autoCal;
    bool recursion;
    unsigned short recursionDepth = 0;
    bool ignoreBody;
    bool http2;
    bool ignoreWordlistComments;
    std::string extensions;
    std::string filterOutStatuses;
    std::string matchStatuses;
    unsigned short timeout;
};

#endif //ROUTEHUNTER_FFUFCOMMAND_H
