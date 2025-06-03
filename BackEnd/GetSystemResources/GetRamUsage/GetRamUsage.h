//
// Created by ziga zoric on 03.06.25.
//

#ifndef GETRAMUSAGE_H
#define GETRAMUSAGE_H
#include "../UsageProvider.h"


class GetRamUsage : UsageProvider{
public:
    ~GetRamUsage() override = default;
    float getCurrentUsage() override;

};



#endif //GETRAMUSAGE_H
