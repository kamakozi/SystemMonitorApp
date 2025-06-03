//
// Created by ziga zoric on 03.06.25.
//

#ifndef GETGPUUSAGE_H
#define GETGPUUSAGE_H
#include "../UsageProvider.h"


class GetGpuUsage :UsageProvider{
public:
    ~GetGpuUsage() override = default;
    float getCurrentUsage() override;

};



#endif //GETGPUUSAGE_H
