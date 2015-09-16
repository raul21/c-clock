#include <stdio.h>
int timestamp = 1442413098;
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
   while (count <= days - 365){
      if (is_bisect_year(year + 1970)){
         count += 366;
      }else{
         count += 365;
      }
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
 * Receives the year and returns the answer to the question "is this year a bisect year?"
 * 0 - no, 1 - yes
 */
int is_bisect_year (int year){
   if (year % 4 != 0 || ((year % 100 != 0) && (year % 400 == 0))){
      return 0;
   }else{
      return 1;
   }
   return 0;
}

/**
 * Receives the timestamp and returns the answer to the question "is the current year a bisect year?"
 * 0 - no, 1 - yes
 */
int is_current_yer_bisect_year (int timestamp){
   int current_year = get_current_year(timestamp);
   return is_bisect_year(current_year);
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
   /* the current year */
   int year = get_current_year(time);

   /* the number of days passed in the current year is: */
   int tyd = days_passed_current_year(time);

   /* margin contains the limits of each month based on tyd variable */
   int margin [13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

   /* if tyd is smaller than 31 we are in the first month and exit */
   if (tyd <= margin[1]) {return 1;}

   int k;
   for (k = 1; k < sizeof(margin); k++){
      if (tyd > margin[k] + is_bisect_year(year)  && tyd <= margin[k + 1] + is_bisect_year(year)){
         return k + 1;
      } 
   } 
   return 0;
}

/**
 * Receives the timestamp and returns the current day
 *
 */
int get_current_day (int time){
   /* the number of days passed in the current year plus one day:  */
   int tyd = days_passed_current_year(time) + 1;

   int margin [13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
   
   
   /* add_one_day is 1 if the current year is a bisect year and 0 if not. It adds one day if necessary */
   int add_one_day = is_bisect_year(get_current_year(time));
   int h;

   int k;
   for (k = 0; k < sizeof(margin); k++){
      /* first two months doesn't matter if the year is bisect or not */
      if (k < 2){
         h = 0;
      }else{
         h = add_one_day;
      }
      if (tyd > margin[k] + h && tyd <= margin[k + 1] + h){
         return tyd - (margin[k] + h);
      }
   }
}

/**
 * Receives the timestamp and returns the current hour
 *
 */
int get_current_hour (int time){
   return get_hours(time) - get_days(time) * 24;
}

/**
 * Receives the timestamp and returns the current minute
 *
 */
int get_current_minute (int time){
   return get_minutes(time) - get_hours(time) * 60;
}

/**
 * Receives the timestamp and returns the current second
 *
 */
int get_current_second (int time){
   return get_seconds(time) - get_minutes(time) * 60;
}

