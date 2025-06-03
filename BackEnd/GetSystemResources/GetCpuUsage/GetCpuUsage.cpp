//
// Created by ziga zoric on 03.06.25.
//

#include "GetCpuUsage.h"
#include <sys/sysctl.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <unistd.h>

float GetCpuUsage::getCurrentUsage() {
    host_cpu_load_info_data_t cpuLoad;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;

    kern_return_t err = host_statistics(mach_host_self(),HOST_CPU_LOAD_INFO,reinterpret_cast<host_info_t>(&cpuLoad),&count);

    if (err != KERN_SUCCESS) {
        return -1.0f;
    }

    static unsigned long long lastUser = 0, lastSystem = 0, lastNice = 0, lastIdle = 0;

    unsigned long long user = cpuLoad.cpu_ticks[CPU_STATE_USER];
    unsigned long long system = cpuLoad.cpu_ticks[CPU_STATE_SYSTEM];
    unsigned long long nice = cpuLoad.cpu_ticks[CPU_STATE_NICE];
    unsigned long long idle = cpuLoad.cpu_ticks[CPU_STATE_IDLE];

    unsigned long long userDiff = user - lastUser;
    unsigned long long systemDiff = system - lastSystem;
    unsigned long long niceDiff = nice - lastNice;
    unsigned long long idleDiff = idle - lastIdle;

    lastUser = user;
    lastSystem = system;
    lastNice = nice;
    lastIdle = idle;

    unsigned long long total = userDiff + systemDiff + niceDiff + idleDiff;
    if (total == 0) return -1.0f;

    float usage = static_cast<float>(userDiff + systemDiff + niceDiff) / static_cast<float>(total) * 100.0f;

    return usage;
}
