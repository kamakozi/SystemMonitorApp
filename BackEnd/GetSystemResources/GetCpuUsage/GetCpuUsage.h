//
// Created by ziga zoric on 03.06.25.
//

#ifndef GETCPUUSAGE_H
#define GETCPUUSAGE_H
#include "../UsageProvider.h"


class GetCpuUsage :UsageProvider{
public:
    ~GetCpuUsage() override = default;
    float getCurrentUsage() override;
};



#endif //GETCPUUSAGE_H
