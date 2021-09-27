/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#include "myclock.h"

#include "consts.h"

MyClock::MyClock(const MyDateTime& dateTime) :
  mDateTime(dateTime)
{
}

MyClock::MyClock(uint8_t rmonth, uint8_t rday, uint8_t rhours, uint8_t rminutes, uint8_t rseconds) :
#if USE_SECONDS
  mDateTime(rmonth, rday, rhours, rminutes, rseconds)
#else
  mDateTime(rmonth, rday, rhours, rminutes),
  mSeconds(rseconds)
#endif
{
}

void MyClock::clockTick()
{
  (*mSecondsPtr)++;
  updateClock();
}

void MyClock::setDateTime(const MyDateTime& dateTime)
{
  mDateTime = dateTime;
}

const MyDateTime& MyClock::getDateTime() const
{
  return mDateTime;
}

const uint8_t& MyClock::getTimeSeconds() const
{
#if USE_SECONDS
  return mDateTime.myTime.seconds;
#else
  return mSeconds;
#endif
}

void MyClock::updateClock()
{
  if (*mSecondsPtr >= consts::secondsLimit)
  {
    *mSecondsPtr = 0U;
    mDateTime.myTime.minutes++;
  }
  if (mDateTime.myTime.minutes >= consts::minutesLimit)
  {
    mDateTime.myTime.minutes = 0U;
    mDateTime.myTime.hours++;
  }
  if (mDateTime.myTime.hours >= consts::hoursLimit)
  {
    mDateTime.myTime.hours = 0U;
    mDateTime.myDate.day++;
  }
  switch(mDateTime.myDate.month)
  {
    case consts::january:
    case consts::march:
    case consts::may:
    case consts::july:
    case consts::august:
    case consts::october:
    case consts::december:
      if (mDateTime.myDate.day >= consts::daysLimit)
      {
        mDateTime.myDate.day = 0U;
        mDateTime.myDate.month++;
      }
      break;

    case consts::april:
    case consts::june:
    case consts::september:
    case consts::november:
      if (mDateTime.myDate.day >= consts::daysLimit - 1U)
      {
        mDateTime.myDate.day = 0U;
        mDateTime.myDate.month++;
      }
      break;

    case consts::february:  // (do not bother with leap-years)
      if (mDateTime.myDate.day >= consts::daysLimit - 3U)
      {
        mDateTime.myDate.day = 0U;
        mDateTime.myDate.month++;
      }
      break;
  }
  if(mDateTime.myDate.month >= consts::monthsLimit)
  {
    mDateTime.myDate.month = 0U;
  }
}

bool MyClock::operator<=(const MyDateTime& rmyDateTime) const
{
  return (mDateTime <= rmyDateTime);
}

bool MyClock::operator>=(const MyDateTime& rmyDateTime) const
{
  return (mDateTime >= rmyDateTime);
}
