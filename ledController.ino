/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2021 by Patrycja Rafalko                                *
 *                                                                         *
 *   https://github.com/prafalko                                           *
 *                                                                         *
 ***************************************************************************/

#include "myclock.h"
#include "settings.h"
#include "utils.h"

#include <EEPROM.h>

namespace
{
  MyClock myClock(MONTH, DAY, HOURS, MINUTES, SECONDS); //set current date and time to the hardcoded values when turning power on
  bool myClockUpdated(false);
  uint8_t ticsCounter(0U);
}

void setUpInterrupt()
{
  cli(); // stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;// initialize counter value
  // set compare match register for 1Hz increments
  OCR1A = 15624;// = ((16MHz / 1024 (prescaler)) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); // allow interrupts
}

ISR(TIMER1_COMPA_vect)
{
  myClock.clockTick();
  myClockUpdated = true;
}

MyDateTime readDateTimeFromMemory()
{
  int address = 0;
  decltype(DATE_TIME_VALID) isDataValid;
  MyDateTime dateTime{};
  EEPROM.get(address, isDataValid);

  if (isDataValid != DATE_TIME_VALID)
  {
#if ENABLE_LOGGER
    Serial.println("Date and time are not saved on eeprom.");
#endif
    return dateTime;
  }
  
  address += sizeof(isDataValid);
  EEPROM.get(address, dateTime);

#if ENABLE_LOGGER
    Serial.println("Current date and time were read successfully.");
#endif

  return dateTime;
}

void writeDateTimeToMemory(const MyDateTime& dateTime)
{
  int address = 0;
  EEPROM.put(address, DATE_TIME_VALID);
  address += sizeof(DATE_TIME_VALID);
  EEPROM.put(address, dateTime);

#if ENABLE_LOGGER
    Serial.println("Current date and time were saved successfully.");
#endif
}

void enableDisableLedsIfNeeded(const MyDateTime& dateTime)
{
  const bool isNight = utils::isNight(dateTime);
  digitalWrite(IS_NIGHT_INDICATOR, isNight);

  if (!isNight)
  {
    return; // it is daytime, do not check for a movement
  }

  const bool isMovementDetected1 = digitalRead(PIR_SIGNAL_1);
  digitalWrite(LEDS_OUTPUT_1, isMovementDetected1 ? HIGH : LOW);

#if (PIR_SIGNAL_2 && LEDS_OUTPUT_2)
  const bool isMovementDetected2 = digitalRead(PIR_SIGNAL_2);
  digitalWrite(LEDS_OUTPUT_2, isMovementDetected2 ? HIGH : LOW);
#endif
}

void printDateTime(const MyDateTime& dateTime, const uint8_t secs)
{
  char* dateTimeStr = new char[10];
  utils::formatDateTime(dateTimeStr, dateTime, secs);

  Serial.print("Current date/time: ");
  Serial.print(dateTimeStr);
  Serial.print("\t");

  delete[] dateTimeStr;
}

void printStates(const MyDateTime& dateTime)
{
  const bool isNight = utils::isNight(dateTime);
  Serial.print("Is night: ");
  Serial.print(isNight ? "T\t" : "F\t");

  const bool movement1 = digitalRead(PIR_SIGNAL_1);
  Serial.print("PIR1 state: ");
  Serial.print(movement1 ? "T\t" : "F\t");

  const bool led1 = digitalRead(LEDS_OUTPUT_1);
  Serial.print("LED1 state: ");
  Serial.print(led1 ? "T\t" : "F\t");

#if (PIR_SIGNAL_2 && LEDS_OUTPUT_2)
  const bool movement2 = digitalRead(PIR_SIGNAL_2);
  Serial.print("PIR2 state: ");
  Serial.print(movement2 ? "T\t" : "F\t");

  const bool led2 = digitalRead(LEDS_OUTPUT_2);
  Serial.print("LED2 state: ");
  Serial.print(led2 ? "T\t" : "F\t");
#endif // (PIR_SIGNAL_2 && LEDS_OUTPUT_2)
}

void setup()
{
  setUpInterrupt();

#if ENABLE_LOGGER
  Serial.begin(9600);
  Serial.print("LED CONTROLLER BY PATRYCJA RAFALKO v");
  Serial.println(consts::versionNumber);
#endif

#if OVERRIDE_DATE_TIME
  const MyDateTime readDateTime;
#else
  const MyDateTime readDateTime = readDateTimeFromMemory();
#endif

  const MyDateTime emptyDateTime = {};
  if (memcmp(&readDateTime, &emptyDateTime, sizeof(MyDateTime)) == 0)
  {
    // no date time saved in memory
    myClockUpdated = false;
#if ENABLE_LOGGER
    Serial.println("Can't restore date and time, setting values to default.");
#endif
  }
  else
  {
    // date and time was read from memory successfully
    myClock.setDateTime(readDateTime);
    myClockUpdated = true;

#if ENABLE_LOGGER
    Serial.println("Date and time successfully restored.");
#endif
  }

  // is night indicator output setup
  pinMode(IS_NIGHT_INDICATOR, OUTPUT);

  // 1. leds input/output
  pinMode(PIR_SIGNAL_1, INPUT);
  pinMode(LEDS_OUTPUT_1, OUTPUT);

#if (PIR_SIGNAL_2 && LEDS_OUTPUT_2)
  // 2. leds input/output
  pinMode(PIR_SIGNAL_2, INPUT);
  pinMode(LEDS_OUTPUT_2, OUTPUT);
#endif
}

void loop()
{
  if (myClockUpdated){
    const MyDateTime& dateTime = myClock.getDateTime();
    const uint8_t& secs = myClock.getTimeSeconds();

    enableDisableLedsIfNeeded(dateTime);

#if ENABLE_LOGGER
    printDateTime(dateTime, secs);
    printStates(dateTime);
    Serial.println();
#endif // ENABLE_LOGGER
    
    ticsCounter++;
    if (ticsCounter > consts::secondsLimit)
    {
      // save date and time to eeprom every minute
      writeDateTimeToMemory(dateTime);
      ticsCounter = 0;
    }

    myClockUpdated = false;
  }
}
