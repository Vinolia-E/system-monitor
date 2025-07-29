#include "header.h"
#include <cstdlib>
#include <cstring>

// get cpu id and information, you can use `proc/cpuinfo`
string CPUinfo()
{
    ifstream file("/proc/cpuinfo");
    string line;
    while (getline(file, line)) {
        if (line.find("model name") != string::npos) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                return line.substr(pos + 2);
            }
        }
    }
    return "Unknown CPU";
}

const char *getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}
// {
//     char CPUBrandString[0x40];
//     unsigned int CPUInfo[4] = {0, 0, 0, 0};

//     // unix system
//     // for windoes maybe we must add the following
//     // __cpuid(regs, 0);
//     // regs is the array of 4 positions
//     __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
//     unsigned int nExIds = CPUInfo[0];

//     memset(CPUBrandString, 0, sizeof(CPUBrandString));

//     for (unsigned int i = 0x80000000; i <= nExIds; ++i)
//     {
//         __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

//         if (i == 0x80000002)
//             memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
//         else if (i == 0x80000003)
//             memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
//         else if (i == 0x80000004)
//             memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
//     }
//     string str(CPUBrandString);
//     return str;
// }

// getOsName, this will get the OS of the current computer
const char *getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}

string getUsername()
{
    char* user = getenv("USER");
    return user ? string(user) : "Unknown";
}

string getHostname()
{
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        return string(hostname);
    }
    return "Unknown";
}
