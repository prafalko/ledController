/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef MYDATETIME_H
#define MYDATETIME_H

extern "C"
{
  #include <stdio.h>
}

#include "settings.h"

struct MyDate{
  MyDate(uint8_t rmonth = 0U, uint8_t rday = 0U) :
    month(rmonth),
    day(rday)
  {}
  
  uint8_t month; //counts from 0!!!
  uint8_t day;   //counts from 0!!!

  bool operator<=(const MyDate& rmyDate) const
  {
    if (month > rmyDate.month)
      return false;

    if (month < rmyDate.month)
      return true;

    if (day <= rmyDate.day)
      return true;

    return false;
  }

  bool operator>=(const MyDate& rmyDate) const
  {
    if (month < rmyDate.month)
      return false;

    if (month > rmyDate.month)
      return true;

    if (day >= rmyDate.day)
      return true;

    return false;
  }

  bool operator<(const MyDate& rmyDate) const
  {
    if (month > rmyDate.month)
      return false;

    if (month < rmyDate.month)
      return true;

    if (day < rmyDate.day)
      return true;

    return false;
  }

  bool operator>(const MyDate& rmyDate) const
  {
    if (month < rmyDate.month)
      return false;

    if (month > rmyDate.month)
      return true;

    if (day > rmyDate.day)
      return true;

    return false;
  }
}; // struct MyDate

struct MyTime{
  MyTime(uint8_t rhours = 0U
        ,uint8_t rminutes = 0U
#if USE_SECONDS
        ,uint8_t rseconds = 0U
#endif
         ) :
    hours(rhours),
    minutes(rminutes)
#if USE_SECONDS
    ,seconds(rseconds)
#endif
  {}
  
  uint8_t hours;
  uint8_t minutes;
#if USE_SECONDS
  uint8_t seconds;
#endif

  bool operator<=(const MyTime& rmyTime) const
  {
    if (hours > rmyTime.hours)
      return false;

    if (hours < rmyTime.hours)
      return true;

    if (minutes > rmyTime.minutes)
      return false;

#if USE_SECONDS
    if (minutes < rmyTime.minutes)
      return true;

    if (seconds <= rmyTime.seconds)
      return true;
#else
    if (minutes <= rmyTime.minutes)
      return true;
#endif

    return false;
  }

  bool operator>=(const MyTime& rmyTime) const
  {
    if (hours < rmyTime.hours)
      return false;

    if (hours > rmyTime.hours)
      return true;

    if (minutes < rmyTime.minutes)
      return false;

#if USE_SECONDS
    if (minutes > rmyTime.minutes)
      return true;

    if (seconds >= rmyTime.seconds)
      return true;
#else
    if (minutes >= rmyTime.minutes)
      return true;
#endif

    return false;
  }
}; // struct MyTime

struct MyDateTime{
  MyDateTime(uint8_t rmonth = 0U
            , uint8_t rday = 0U
            , uint8_t rhours = 0U
            , uint8_t rminutes = 0U
#if USE_SECONDS
            , uint8_t rseconds = 0U
#endif
            ) :
    myDate(rmonth, rday),
#if USE_SECONDS
    myTime(rhours, rminutes, rseconds)
#else
    myTime(rhours, rminutes)
#endif
  {}
     
  MyDate myDate;
  MyTime myTime;

  bool operator<=(const MyDateTime& rmyDateTime) const
  {
    if (myDate > rmyDateTime.myDate)
      return false;

    if (myDate < rmyDateTime.myDate)
      return true;

    if (myTime <= rmyDateTime.myTime)
      return true;

    return false;
  }

  bool operator>=(const MyDateTime& rmyDateTime) const
  {
    if (myDate < rmyDateTime.myDate)
      return false;

    if (myDate > rmyDateTime.myDate)
      return true;

    if (myTime >= rmyDateTime.myTime)
      return true;

    return false;
  }
}; // struct MyDateTime

#endif // MYDATETIME_H
