#ifndef TPE_ARQUI_TIME_H
#define TPE_ARQUI_TIME_H

/**
 * Retrieves the current amount of seconds from the RTC
 * @return seconds in unsigned int form
 */
unsigned int getSeconds();

/**
 * Retrieves the current amount of minutes from the RTC
 * @return minutes in unsigned int form
 */
unsigned int getMinutes();

/**
 * Retrieves the current amount of hours from the RTC
 * @return hours in unsigned int form
 */
unsigned int getHours();

/**
 * Retrieves the current day from the RTC
 * @return day number in unsigned int form
 */
unsigned int getDay();

/**
 * Retrieves the current month from the RTC
 * @return month number in unsigned int form
 */
unsigned int getMonth();

/**
 * Retrieves the current year from the RTC
 * @return year number in unsigned int form
 */
unsigned int getYear();

/**
 * Prints the current time as hh:mm:ss
 */
void printTime();

/**
 * Prints the current date as dd/mm/yy
 */
void printDate();

#endif //TPE_ARQUI_TIME_H
