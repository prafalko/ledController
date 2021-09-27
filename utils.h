/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include "consts.h"
#include "mydatetime.h"

namespace utils
{
  inline bool isNight(const MyDateTime& dateTime)
  {
    return dateTime.myTime <= consts::sunrises[dateTime.myDate.month] ||
           dateTime.myTime >= consts::sunsets[dateTime.myDate.month];
  }

  char* formatDateTime(char* dateTimeBuff, const MyDateTime& dateTime, uint8_t secs);
  
} // namespace utils

#endif // UTILS_H
