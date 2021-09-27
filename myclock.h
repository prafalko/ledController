/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef MYCLOCK_H
#define MYCLOCK_H

#include "mydatetime.h"
#include "settings.h"

extern "C"
{
  #include <stdio.h>
}
  
class MyClock
{
  public:
    MyClock(const MyDateTime& dateTime = {});
    MyClock(uint8_t month, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds = 0);
    void clockTick();

    void setDateTime(const MyDateTime& dateTime);
    const MyDateTime& getDateTime() const;
    const uint8_t& getTimeSeconds() const;

    bool operator<=(const MyDateTime& rmyClock) const;
    bool operator>=(const MyDateTime& rmyClock) const;

  private:
    void updateClock();
    
    MyDateTime mDateTime;
#if USE_SECONDS
    uint8_t* mSecondsPtr = &mDateTime.myTime.seconds;
#else
    uint8_t mSeconds; //MyDateTime doesn't keep seconds if USE_SECONDS is set to false, so we need a separate second counter to observe elapsing time
    uint8_t* mSecondsPtr = &mSeconds;
#endif
}; 

#endif // MYCLOCK_H
