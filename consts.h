/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef CONSTS_H
#define CONSTS_H

#include "mydatetime.h"
#include "version.h"

namespace consts
{
  const char versionNumber[] = VERSION_NUMBER;
  
  const uint8_t monthsLimit = 12U;
  const uint8_t daysLimit = 31U;
  const uint8_t hoursLimit = 24U;
  const uint8_t minutesLimit = 60U;
  const uint8_t secondsLimit = 60U;
  
  const uint8_t january = 0U;
  const uint8_t february = 1U;
  const uint8_t march = 2U;
  const uint8_t april = 3U;
  const uint8_t may = 4U;
  const uint8_t june = 5U;
  const uint8_t july = 6U;
  const uint8_t august = 7U;
  const uint8_t september = 8U;
  const uint8_t october = 9U;
  const uint8_t november = 10U;
  const uint8_t december = 11U;

  // all times in UTC+1, no summer time (also in MyClock)
  const MyTime sunrises[] = { MyTime(7U, 45U), // January
                              MyTime(7U, 0U),  // February
                              MyTime(5U, 55U), // March
                              MyTime(4U, 40U), // April
                              MyTime(3U, 40U), // May
                              MyTime(3U, 15U), // June
                              MyTime(3U, 30U), // July
                              MyTime(4U, 15U), // August
                              MyTime(5U, 15U), // September
                              MyTime(6U, 5U),  // October
                              MyTime(7U, 0U),  // November
                              MyTime(7U, 45U)  // December
  };

  const MyTime sunsets[] = { MyTime(15U, 50U), // January
                             MyTime(16U, 45U), // February
                             MyTime(17U, 40U), // March
                             MyTime(18U, 40U), // April
                             MyTime(19U, 30U), // May
                             MyTime(20U, 5U),  // June
                             MyTime(19U, 55U), // July
                             MyTime(19U, 10U), // August
                             MyTime(17U, 55U), // September
                             MyTime(16U, 45U), // October
                             MyTime(15U, 55U), // November
                             MyTime(15U, 25U)  // December
  };
  
} // namespace consts

#endif // CONSTS_H
