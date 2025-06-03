//
// Created by ziga zoric on 03.06.25.
//

#ifndef USAGEPROVIDER_H
#define USAGEPROVIDER_H



class UsageProvider {
public:
    virtual ~UsageProvider();
    virtual float getCurrentUsage() = 0;

};



#endif //USAGEPROVIDER_H
