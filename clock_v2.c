#include <stdio.h>
int timestamp = 1440163000;

int main () {
   return 0;
}

/**
 * Receives the timestamp and returns the total number of seconds  
 *
 */
int get_seconds (int time){
   return time;
}

/**
 * Receives the timestamp and returns the total amount of minutes
 *
 */
int get_minutes (int time){
   return time / 60;
}

/**
 * Receives the timestamp and returns the total number of the hours
 *
 */
int get_hours (int time){
   return time / 3600;
}

/**
 * Receives the timestamp and returns the total number of days 
 *
 */
int get_days (int time){
   return time / (3600 * 24);
}

/**
 * Receives the timestamp and returns the number of passed years
 *
 */
int get_years (int time){
   int days = get_days(time);
   int year = 0;
   int count = 0;
   while (1){
      if ((year % 4 != 0) || ((year % 100 != 0) && (year % 400 == 0))){
         count += 365;
      }else{
         count += 366;
      }
      if (count>days) {break;}
      year++;
   }
   return year;
}

/**
 * Receives he timestamp and returns the current year
 *
 */
int get_current_year (int time){
   return 1970 + get_years(time);	
}

/**
 * Receives the timestamp and returns the number of bisect years
 *
*/
int get_bisect_years_number (int time){
   return (get_current_year(time) - 1970) / 4;
}

/**
 * Receives the timestamp and returns the answer to the question "is the current year a bisect year?"
 * 0 - no, 1 - yes
 */
int is_bisect_year (int timestamp){
   int current_year = get_current_year(timestamp);
   if (current_year % 4 != 0 || ((current_year % 100 != 0) && (current_year % 400 ==0))){
      return 0;
   }else{
      return 1;
   }
}

/**
 * Receives the timestamp and returns the number of days passed in the current year
 *
 */
int days_passed_current_year (int time){
   return get_days(time) - ((get_years(time) * 365) + get_bisect_years_number(time));
}

/**
 * Receives the timestamp and returns the current month
 *
 */
int get_current_month (int time){
   /* the number of days passed in the current year is: */
   int tyd = days_passed_current_year(time);
   int i;
   if (is_bisect_year(time) == 0){
      i = 0;
   }else{
      i = 1;
   }
   if (tyd > 0 && tyd <= 31){
      return 1;
   }else if (tyd > 31 && tyd <= 59 + i){
      return 2;
   }else if (tyd > 59 + i && tyd <= 90 + i){
      return 3;
   }else if (tyd > 90 + i && tyd <= 120 + i){
      return 4;
   }else if (tyd > 120 + i && tyd <= 151 + i){
      return 5;
   }else if (tyd > 151 + i && tyd <= 181 + i){
      return 6;
   }else if (tyd > 181 + i && tyd <= 212 + i){
      return 7;
   }else if (tyd > 212 + i && tyd <= 243 + i){
      return 8;
   }else if (tyd > 243 + i && tyd <= 273 + i){
      return 9;
   }else if (tyd > 273 + i && tyd <= 304 + i){
      return 10;
   }else if (tyd > 304 + i && tyd <= 334 + i){
      return 11;
   }else if (tyd > 334 + i && tyd <= 365 + i){
      return 12;
   }
   return 0;
}

/**
 * Receives the timestamp and returns the current day
 *
 */
int get_current_day (int time){
   return 0;
}

/**
 * Receives the timestamp and returns the current hour
 *
 */
int get_current_hour (int time){
   return 0;
}

/**
 * Receives the timestamp and returns the current minute
 *
 */
int get_current_minute (int time){
   return 0;
}

/**
 * Receives the timestamp and returns the current second
 *
 */
int get_current_second (int time){
   return 0;
}

