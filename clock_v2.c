#include <stdio.h>
#include <time.h>

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
   for (k = 1; k < 13; k++){
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
   for (k = 0; k < 13; k++){
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
 * Receives the year and returns the last sunday of the march for the given year
 *
 */
int get_march_last_sunday (int year){
   int days[28] = {27, 26, 25, 30, 29, 28, 27, 25, 31, 30, 29, 27, 26, 25, 31, 29, 28, 27, 26, 31, 30, 29, 28, 26, 25, 31, 30, 28};
   /* Our calendar skipped eleven days in september 1752 */
   int k = year;
   if (year > 1752) { k += 11;}
   return days[k % 28];

}

/**
 * Receives the year and returns the last sunday of the october for the given year
 *
 */
int get_october_last_sunday (year){
   int days[28] = {30, 29, 28, 26, 25, 31, 30, 28, 27, 26, 25, 30, 29, 28, 27, 25, 31, 30, 29, 27, 26, 25, 31, 29, 28, 27, 26, 31};
   /* Our calendar skipped eleven days in september 1752 */
   int k = year;
   if (year > 1753) { k += 11;}
   return days[k % 28];
}

/**
 * Receives the timestamp and returns the real hour - summer or winter hour
 *
 */
int get_real_hour (int time) {
   int real_hour = get_current_hour(time);

   int current_date[5];
   current_date[0] = get_current_month(time);
   current_date[1] = get_current_day(time);
   current_date[2] = get_current_hour(time);
   current_date[3] = get_current_minute(time);
   current_date[4] = get_current_second(time);
   int spring_date[5];
   spring_date[0] = 3;
   spring_date[1] = get_march_last_sunday(get_current_year(time));
   spring_date[2] = 3;
   spring_date[3] = 0;
   spring_date[4] = 0;
   int autumn_date[5];
   autumn_date[0] = 10;
   autumn_date[1] = get_october_last_sunday(get_current_year(time));
   autumn_date[2] = 4;
   autumn_date[3] = 0;
   autumn_date[4] = 0;

   if (compare_dates(spring_date, current_date) && compare_dates(current_date, autumn_date)){
      real_hour++;
   }
   return real_hour;
}

/**
 * Receives two dates and returns 1 if the first date is previous to the second one
 * A *_date array contains, in order, month, day, hour, minute, second so the dates must be in the same year
 */
int compare_dates (int first_date[5], int second_date[5]){
   int i;
   for (i = 0; i < 5; i++){
      if (first_date[i] < second_date[i]){
         return 1;
      }else if (first_date[i] == second_date[i]){
         continue;
      }else{
         return 0;
      }
   }
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

/**
 * Receives the timestamp and returns the number of passed weeks
 *
 */
int get_weeks (int time) {
   return get_days(time) / 7;
}

/**
 * Receives the timestamp and returns the day of the week
 *
 */
int get_week_day (int time){
   int week_day = get_days(time) - get_weeks(time) * 7;
   switch (week_day){
      case 0: return 5;
      case 1: return 6;
      case 2: return 7;
      case 3: return 1;
      case 4: return 2;
      case 5: return 3;
      case 6: return 4;
   }
}

/**
 * Receives the timestamp and returns the name of the day of the week
 *
 */
char * get_week_day_name (int time) {
   int week_day = get_week_day(time);
   char * week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
   return week[week_day - 1];   
}

/**
 * Receives the timestamp and displays the clock
 *
 */
void display (int time) {
   printf ("%i %i\n", get_current_year(time), get_current_month(time));
   printf ("%i %s\n", get_current_day(time), get_week_day_name(time));
   printf ("%i : %i %i\n", get_real_hour(time), get_current_minute(time), get_current_second(time));
}  

int main () {
   int timestamp = (int) time (NULL);
   display (timestamp);
   return 0;
}

