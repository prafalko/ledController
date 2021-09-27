/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/
 
#include "utils.h"

namespace utils
{
  
char* formatDateTime(char* dateTimeBuff, const MyDateTime& dateTime, uint8_t secs)
{
  if (!dateTimeBuff)
    return dateTimeBuff;

  sprintf(dateTimeBuff, "%02d/%02d %02d:%02d:%02d\0", dateTime.myDate.day + 1U,
                                                      dateTime.myDate.month + 1U,
                                                      dateTime.myTime.hours,
                                                      dateTime.myTime.minutes,
                                                      secs);

  return dateTimeBuff;
}

} // namespace utils
