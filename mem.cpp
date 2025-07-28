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