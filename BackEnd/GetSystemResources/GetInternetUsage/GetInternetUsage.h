//
// Created by ziga zoric on 03.06.25.
//

#ifndef GETINTERNETUSAGE_H
#define GETINTERNETUSAGE_H
#include "../UsageProvider.h"


class GetInternetUsage : UsageProvider{
public:
    ~GetInternetUsage() override = default;
    float getCurrentUsage() override;
};



#endif //GETINTERNETUSAGE_H
