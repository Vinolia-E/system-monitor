#include "header.h"
#include <cstdlib>
#include <cctype>

vector<Proc> getProcesses()
{
    vector<Proc> processes;
    DIR* proc_dir = opendir("/proc");
    if (!proc_dir) return processes;
    
    struct dirent* entry;
    while ((entry = readdir(proc_dir)) != nullptr) {
        if (isdigit(entry->d_name[0])) {
            Proc proc = {0};
            proc.pid = atoi(entry->d_name);
            
            string stat_path = "/proc/" + string(entry->d_name) + "/stat";
            ifstream stat_file(stat_path);
            if (stat_file.is_open()) {
                string line;
                getline(stat_file, line);
                if (!line.empty()) {
                    char name[256];
                    sscanf(line.c_str(), "%d %s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lld %lld %*d %*d %*d %*d %*d %*d %lld %lld",
                           &proc.pid, name, &proc.state, &proc.utime, &proc.stime, &proc.vsize, &proc.rss);
                    proc.name = string(name);
                    if (proc.name.front() == '(' && proc.name.back() == ')') {
                        proc.name = proc.name.substr(1, proc.name.length() - 2);
                    }
                    processes.push_back(proc);
                }
            }
        }
    }
    closedir(proc_dir);
    return processes;
}

// Implemented `getMemInfo()` to parse `/proc/meminfo` and extract total and 
// available memory in bytes. The function computes used memory by subtracting 
// available from total and returns the values in a `MemInfo` struct.
MemInfo getMemInfo()
{
    MemInfo info = {0, 0, 0};
    ifstream file("/proc/meminfo");
    string line;
    while (getline(file, line)) {
        if (line.find("MemTotal:") != string::npos) {
            sscanf(line.c_str(), "MemTotal: %lld kB", &info.total);
            info.total *= 1024;
        } else if (line.find("MemAvailable:") != string::npos) {
            sscanf(line.c_str(), "MemAvailable: %lld kB", &info.available);
            info.available *= 1024;
        }
    }
    info.used = info.total - info.available;
    return info;
}

MemInfo getSwapInfo()
{
    MemInfo info = {0, 0, 0};
    ifstream file("/proc/meminfo");
    string line;
    while (getline(file, line)) {
        if (line.find("SwapTotal:") != string::npos) {
            sscanf(line.c_str(), "SwapTotal: %lld kB", &info.total);
            info.total *= 1024;
        } else if (line.find("SwapFree:") != string::npos) {
            long long free;
            sscanf(line.c_str(), "SwapFree: %lld kB", &free);
            info.available = free * 1024;
        }
    }
    info.used = info.total - info.available;
    return info;
}