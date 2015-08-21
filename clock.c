#include <stdio.h>
int timestamp = 1440163000;

int main () {
	printf ("Nr de secunde este %d\n", get_seconds(timestamp));
	printf ("Nr de minute este %d\n", get_minutes(timestamp));
	printf ("Nr de ore este %d\n", get_hours(timestamp));
	printf ("Nr de zile este %d\n", get_days(timestamp));
	printf ("Nr de ani este %d\n", get_years(timestamp));
	printf ("Suntem in anul %d\n", get_current_year(timestamp));
	printf ("Nr de ani bisecti este %d\n", get_bisect_years_number(timestamp));
	return 0;
}

/**
 *  
 *
 */
int get_seconds (int time){
	return time;
}

/**
 * 
 *
 */
int get_minutes (int time){
	return time / 60;
}

/**
 *
 *
 */
int get_hours (int time){
	return time / 3600;
}

/**
 *
 *
 */
int get_days (int time){
	return time / (3600*24);
}

/**
 *
 *
 */
int get_years (int time){
	int days = get_days(time);
	int year=0;
	int count=0;
	while (1){
		if ((year%4 != 0) || ((year%100 != 0) && (year%400 == 0))){
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
 *
 *
 */
int get_current_year (time){
	return 1970 + get_years(time);
	
}

/**
 *
 *
 */
int get_current_month (time){
	return 0;
}

/**
 *
 *
 */
int get_bisect_years_number (time){
	return (get_current_year(time) - 1970) / 4;
}
