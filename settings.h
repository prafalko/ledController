/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

// this define enables/disabled logging data to Serial
#define ENABLE_LOGGER 0

// this define controls if seconds are also used and compared.
// it's more accurate, but also more time and memory consuming
// 0 (false) preferred
#define USE_SECONDS 0

// define pin number where high state will be used to indicate if it is a night time (movement detector enabled)
#define IS_NIGHT_INDICATOR 13U

// define input and output pin numbers for the first circuit
#define PIR_SIGNAL_1 12U
#define LEDS_OUTPUT_1 11U

// define input and output pin numbers for the second circuit
#define PIR_SIGNAL_2 9U
#define LEDS_OUTPUT_2 8U

// 0 - restore date and time if possible
// 1 - do not try to restore date and time; put the default date/time defined below
#define OVERRIDE_DATE_TIME 0

// start-up date and time if date and time cannot be restored from the memory or OVERRIDE_DATE_TIME is enabled
// !! day and month need to be subtracted by 1 (count from 0)
#define MONTH 8U
#define DAY 23U
#define HOURS 23U
#define MINUTES 20U
#define SECONDS 0U

// magic number indicating that the date and time is saved on eeprom
#define DATE_TIME_VALID uint16_t(0x2305)

#endif // SETTINGS_H
