#pragma once
#pragma warning(disable: 4996)
#include<iostream>
#include"clsString.h"
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;

protected:

	enum enCompareDatesResults { Before = -1, Equals = 0, After = 1 };

	static string DayName(short DayOrder) {
		switch (DayOrder)
		{
		case 0:
			return"Sunday";
			break;
		case 1:
			return"Monday";
			break;
		case 2:
			return"Tuesday";
			break;
		case 3:
			return"Wednesday";
			break;
		case 4:
			return"Thursday";
			break;
		case 5:
			return"Friday";
			break;
		case 6:
			return"Saturday";
			break;
		}
	}

	static string MonthName(short MonthOrder) {
		switch (MonthOrder)
		{
		case 1:
			return "Jan";
		case 2:
			return "Feb";
		case 3:
			return "Mar";
		case 4:
			return "Apr";
		case 5:
			return "Jun";
		case 6:
			return "Jul";
		case 7:
			return "May";
		case 8:
			return "Agu";
		case 9:
			return "Sep";
		case 10:
			return "Oct";
		case 11:
			return "Nov";
		case 12:
			return "Dec";
		}
	}

public:
	clsDate() {

		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}

	clsDate(string date) {
		vector<string> vDate = clsString::SplitString(date, "/");
		_Day = (short)stoi(vDate.at(0));
		_Month = (short)stoi(vDate.at(1));
		_Year= (short)stoi(vDate.at(2));
	}

	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrderInYear, short year) {

		for (short i = 1; i <= 12; i++)
		{
			if (DayOrderInYear > NumberOfDaysInMonth(i, year))
				DayOrderInYear -= NumberOfDaysInMonth(i, year);
			else {
				_Day = DayOrderInYear;
				_Month = i;
				_Year = year;
				break;
			}
		}
	}

	void setDay(short Day) {
		_Day = Day;
	}

	short getDay() {
		return _Day;
	}

	__declspec(property(get = getDay, put = setDay))short day;

	void setMonth(short Month) {
		_Month = Month;
	}

	short getMonth() {
		return _Month;
	}

	__declspec(property(get = getMonth, put = setMonth))short month;

	void setYear(short Year) {
		_Year = Year;
	}

	short getYear() {
		return _Year;
	}

	__declspec(property(get = getYear, put = setYear))short year;

	static string DateToString(clsDate Date, string delim="/") {
		return(to_string(Date.day) + delim + to_string(Date.month) + delim + to_string(Date.year));

	}
	string DateToString(string delim = "/") {
		return DateToString(*this, delim);
	}

	static bool CheckLeapYear(short year) {
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}
	bool CheckLeapYear() {
		return CheckLeapYear(this->year);
	}

	static short DayOfWeekOrder(short year, short month, short day) {
		short* ptr = new short;
		*ptr = (14 - month) / 12;
		year = year - *ptr;
		month = month + 12 * (*ptr) - 2;
		delete ptr;
		return((day + year + (year / 4) - (year / 100) + (year / 400) + (31 * month / 12)) % 7);

	}
	
	static short DayOrderInYear(clsDate Date) {
		short Days = 0;
		for (short i = 1; i < Date.month; i++)
		{
			Days += NumberOfDaysInMonth(i, Date.year);
		}
		return (Days + Date.day);
	}
	short DayOrderInYear() {
		return DayOrderInYear(*this);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return(Date.day == NumberOfDaysInMonth(Date.month, Date.year));
	}

	static bool IsLastMonthInYear(short Month) {
		return(Month == 12);
	}
	
	static short NumberOfDaysInMonth(short Month, short year) {
		if (Month == 0)
			return 0;
		short days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return(Month == 2) ? ((CheckLeapYear(year)) ? 29 : 28) : days[Month - 1];
	}
	
	static short NumberOfHoursInMonth(short Month, short year) {
		return NumberOfDaysInMonth(Month, year) * 24;
	}
	
	static int NumberOfMinutesInMonth(short Month, short year) {
		return NumberOfHoursInMonth(Month, year) * 60;
	}
	
	static int NumberOfSecondsInMonth(short Month, short year) {
		return NumberOfMinutesInMonth(Month, year) * 60;
	}
	
	static short NumberOfDaysInYear(short Year) {
		return(CheckLeapYear(Year) ? 366 : 365);
	}
	
	static short NumberOfHoursInYear(short Year) {
		return NumberOfDaysInYear(Year) * 24;
	}
	
	static int NumberOfMinutesInYear(short Year) {
		return NumberOfHoursInYear(Year) * 60;
	}
	
	static int NumberOfSecondsInYear(short Year) {
		return NumberOfMinutesInYear(Year) * 60;
	}
	
	static void PrintMonthInfo(short year, short Month) {
		cout << left;
		cout << setw(19) << "Number of Days " << "in [" << Month << "] of year [" << year << "] is " << NumberOfDaysInMonth(Month, year) << "\n";
		cout << setw(19) << "Number of Hours " << "in [" << Month << "] of year [" << year << "] is " << NumberOfHoursInMonth(Month, year) << "\n";
		cout << setw(19) << "Number of Minutes " << "in [" << Month << "] of year [" << year << "] is " << NumberOfMinutesInMonth(Month, year) << "\n";
		cout << setw(19) << "Number of Seconds " << "in [" << Month << "] of year [" << year << "] is " << NumberOfSecondsInMonth(Month, year) << endl;
	}
	
	static clsDate FindDateDependingOnOrder(short DayOrderInYear, short year) {
		clsDate Date;
		for (short i = 1; i <= 12; i++)
		{
			if (DayOrderInYear > NumberOfDaysInMonth(i, year))
				DayOrderInYear -= NumberOfDaysInMonth(i, year);
			else {
				Date.day = DayOrderInYear;
				Date.month = i;
				Date.year = year;
				break;
			}
		}
		return Date;
	}
	
	static clsDate GetSystemDate() {
		clsDate Date;
		time_t t = time(0);
		tm* now = localtime(&t);
		Date.year = now->tm_year + 1900;
		Date.month = now->tm_mon + 1;
		Date.day = now->tm_mday;
		return Date;
	}
	 
	static string GetSystemTime() {
		time_t t = time(0);
		tm* now = localtime(&t);
		short hours = now->tm_hour;
		short minutes = now->tm_min;
		short seconds = now->tm_sec;
		return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
	}

	static void SwapDate(clsDate& Date1, clsDate& Date2) {
		clsDate* ptrTemp = new clsDate;
		*ptrTemp = Date1;
		Date1 = Date2;
		Date2 = *ptrTemp;
		delete ptrTemp;

	}
	void SwapDate(clsDate& Date2) {
		SwapDate(*this, Date2);
	}

	static clsDate NewDateAfterAddingDaysToDate(clsDate Date, int days) {
		int Days = 0;
		Days = DayOrderInYear(Date) + days;
		while (Days > NumberOfDaysInYear(Date.year)) {
			Days -= NumberOfDaysInYear(Date.year);
			Date.year++;
		}
		return(FindDateDependingOnOrder(Days, Date.year));

	}
	clsDate NewDateAfterAddingDaysToDate(int days) {
		return NewDateAfterAddingDaysToDate(*this, days);
	}

	static clsDate IncreadDateByOneDay(clsDate& Date) {
		if (IsLastDayInMonth(Date)) {
			if (Date.month == 12) {
				Date.day = 1;
				Date.month = 1;
				Date.year++;

			}
			else {
				Date.day = 1;
				Date.month++;
			}
		}
		else {
			Date.day++;

		}
		return Date;

	}
	void IncreadDateByOneDay() {
		IncreadDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, int XDays) {
		for (int i = 0; i < XDays; i++)
		{
			IncreadDateByOneDay(Date);

		}
		return Date;
	}
	void IncreaseDateByXDays(int XDays) {
		IncreaseDateByXDays(*this, XDays);
	}
	
	static clsDate IncreaseDateByOneWeek(clsDate& Date) {
		for (int i = 0; i < 7; i++)
		{
			IncreadDateByOneDay(Date);

		}
		return Date;
	}
	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}
	
	static clsDate IncreaseDateByXWeeks(clsDate& Date, int XWeeks) {
		for (int i = 0; i < XWeeks; i++)
		{
			IncreaseDateByOneWeek(Date);

		}
		return Date;
	}
	void IncreaseDateByXWeeks(int XWeeks) {
		IncreaseDateByXWeeks(*this, XWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (IsLastMonthInYear(Date.month)) {
			Date.year++;
			Date.month = 1;
		}
		else
			Date.month++;
		if (Date.day > NumberOfDaysInMonth(Date.month, Date.year)) {
			Date.day = NumberOfDaysInMonth(Date.month, Date.year);

		}
		return Date;
	}
	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, int XMonths) {
		for (int i = 0; i < XMonths; i++)
		{
			IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(int XMonths) {
		IncreaseDateByXMonths(*this, XMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {
		Date.year++;
		return Date;
	}
	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, int XYears) {
		Date.year += XYears;
		return Date;
	}
	void IncreaseDateByXYears(int XYears) {
		IncreaseDateByXYears(*this, XYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {
		Date.year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, int XDecades) {
		Date.year += XDecades * 10;
		return Date;
	}
	void IncreaseDateByXDecades(int XDecades) {
		IncreaseDateByXDecades(*this, XDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {
		Date.year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		Date.year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date) {
		if (Date.day == 1) {
			if (Date.month == 1) {
				Date.day = 31;
				Date.month = 12;
				Date.year--;
				return Date;
			}
			Date.day = NumberOfDaysInMonth(Date.month - 1, Date.year);
			Date.month--;
			return Date;


		}
		Date.day--;
		return Date;
	}
	void DecreaseDateByOneDay() {
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, int XDays) {
		for (int i = 0; i < XDays; i++)
		{
			DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(int XDays) {
		DecreaseDateByXDays(*this, XDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {
		for (int i = 0; i < 7; i++)
		{
			DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, int XWeeks) {
		for (int i = 0; i < XWeeks; i++)
		{
			DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(int XWeeks) {
		DecreaseDateByXWeeks(*this, XWeeks);
	}
	
	static clsDate DecreaseDateByOneMonth(clsDate& Date) {
		if (Date.month == 1) {
			Date.month = 12;
			Date.year--;

		}
		else
			Date.month--;
		if (Date.day > NumberOfDaysInMonth(Date.month, Date.year)) {
			Date.day = NumberOfDaysInMonth(Date.month, Date.year);
		}

		return Date;
	}
	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, int XMonths) {
		for (int i = 0; i < XMonths; i++)
		{
			DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(int XMonths) {
		DecreaseDateByXMonths(*this, XMonths);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {
		Date.year--;
		return Date;
	}
	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, int XYears) {
		Date.year -= XYears;
		return Date;
	}
	void DecreaseDateByXYears(int XYears) {
		DecreaseDateByXYears(*this, XYears);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {
		Date.year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, int XDecades) {
		Date.year -= XDecades * 10;
		return Date;
	}
	void DecreaseDateByXDecades(int XDecades) {
		DecreaseDateByXDecades(*this, XDecades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {
		Date.year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByXCentury(clsDate& Date, int XCenturies) {
		Date.year -= 100 * XCenturies;
		return Date;
	}
	void DecreaseDateByXCentury(int XCenturies) {
		DecreaseDateByXCentury(*this, XCenturies);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {
		Date.year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsBeforeDate(clsDate Date1, clsDate Date2) {
		return((Date1.year < Date2.year) ? true : (Date1.year != Date2.year) ? false : (Date1.month < Date2.month) ? true : (Date1.month != Date2.month) ? false : Date1.day < Date2.day);
	}
	bool IsBeforeDate(clsDate Date2) {
		return IsBeforeDate(*this, Date2);
	}

	static bool isAfterDate(clsDate Date1, clsDate Date2) {
		return(IsBeforeDate(Date2, Date1) && !AreEqualsDates(Date1, Date2));
	}
	bool isAfterDate(clsDate Date2) {
		return isAfterDate(*this, Date2);
	}

	static bool AreEqualsDates(clsDate Date1, clsDate Date2) {
		return(Date1.year == Date2.year && Date1.month == Date2.month && Date1.day == Date2.day);
	}
	bool AreEqualsDates(clsDate Date2) {
		return AreEqualsDates(*this, Date2);
	}

	static short DifferenceBetweenTwoDates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {

		if (IsBeforeDate(Date1, Date2)) {
			short days = 0;
			while (IsBeforeDate(Date1, Date2)) {
				days++;
				Date1 = IncreadDateByOneDay(Date1);
			}
			return IncludeEndDay ? ++days : days;
		}
		else {
			short days = 0;
			while (IsBeforeDate(Date2, Date1)) {
				days++;
				Date2 = IncreadDateByOneDay(Date2);
			}
			return IncludeEndDay ? ++days * -1 : days * -1;
		}
	}
	short DifferenceBetweenTwoDates(clsDate Date2, bool IncludeEndDay = false) {
		return DifferenceBetweenTwoDates(*this, Date2, IncludeEndDay);
	}

	static short  DayOfWeekOrder(clsDate Date) {
		return DayOfWeekOrder(Date.year, Date.month, Date.day);
	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(*this);
	}
	

	static bool isEndOfWeek(clsDate Date) {
		return (DayOfWeekOrder(Date) == 6);

	}
	bool isEndOfWeek() {
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(clsDate Date) {
		return (DayOfWeekOrder(Date) == 5 || DayOfWeekOrder(Date) == 6);

	}
	bool isWeekEnd() {
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate Date) {
		return(!isWeekEnd(Date));
	}
	bool isBusinessDay() {
		return isBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate Date) {
		return (6 - DayOfWeekOrder(Date));
	}
	short DaysUntilEndOfWeek() {
		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate Date) {
		return (NumberOfDaysInMonth(Date.month, Date.year) - Date.day + 1);
	}
	short DaysUntilEndOfMonth() {
		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate Date) {
		return(NumberOfDaysInYear(Date.year) - DayOrderInYear(Date) + 1);
	}
	short DaysUntilEndOfYear() {
		return DaysUntilEndOfYear(*this);
	}

	static int YourAgeInDays(clsDate BirthdayDate) {

		return DifferenceBetweenTwoDates(GetSystemDate(), BirthdayDate);
	}
	int YourAgeInDays() {
		YourAgeInDays(*this);
	}

	static bool isValidateDate(clsDate Date) {

		return!(Date.day > NumberOfDaysInMonth(Date.month, Date.year) || Date.day < 1 || Date.month < 1 || Date.month>12);

	}
	bool isValidateDate() {
		return isValidateDate(*this);
	}

	static string DateToStringWithFormattingOptions(clsDate Date, string FormatShape) {
		string FormattedDate = "";
		FormattedDate = clsString::ReplaceWordsInStringCaseSensitive(FormatShape, "dd", to_string(Date.day));
		FormattedDate = clsString::ReplaceWordsInStringCaseSensitive(FormattedDate, "mm", to_string(Date.month));
		FormattedDate = clsString::ReplaceWordsInStringCaseSensitive(FormattedDate, "yyyy", to_string(Date.year));
		return FormattedDate;
	}
	string DateToStringWithFormattingOptions(string FormatShape) {
		return DateToStringWithFormattingOptions(*this, FormatShape);
	}

	static enCompareDatesResults CompareDates(clsDate Date1, clsDate Date2) {
		return(AreEqualsDates(Date1, Date2) ? enCompareDatesResults::Equals : isAfterDate(Date1, Date2) ? enCompareDatesResults::After : enCompareDatesResults::Before);
	}
	enCompareDatesResults CompareDates(clsDate Date2) {
		return CompareDates(*this, Date2);
	}

	static void PrintMonthCalender(short year, short month) {
		short* Day = new short;
		short* MonthDays = new short;
		*Day = DayOfWeekOrder(year, month, 1);
		*MonthDays = NumberOfDaysInMonth(month, year);

		cout << "_____________________" << MonthName(month) << "_____________________\n\n";
		cout << left << setw(7) << "Sun" << setw(7) << "Mon" << setw(7) << "Tue";
		cout << setw(7) << "Wed" << setw(7) << "Thu" << setw(7) << "Fri" << "Sat\n";
		cout << right;

		//first day
		cout << setw(((*Day) * 7) + 3) << "1";
		if (*Day == 6) cout << "\n";

		for (int i = 2; i <= *MonthDays; i++)
		{
			if (DayOfWeekOrder(year, month, i) == 0)
				printf("%3d", i);
			else if (DayOfWeekOrder(year, month, i) == 6)
				printf("%7d\n", i);
			else
				printf("%7d", i);
		}
		cout << endl;
		delete Day, MonthDays;
		cout << "______________________________________________";
	}
	void PrintMonthCalender() {
		PrintMonthCalender(this->year, this->month);
	}

	static 	void PrintYearCalender(short year) {
		cout << "______________________________________________\n\n";
		cout << right << setw(25) << "Calender - " << year << "\n\n";
		cout << "______________________________________________\n\n";
		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(year, i);
			cout << "\n" << endl;

		}
	}
	void PrintYearCalender() {
		PrintYearCalender(this->year);
	}

	static short CalclateActualVacationDaysInPeriod(clsDate DateFrom, clsDate DateTo) {
		short ActualVacations = 0;
		while (IsBeforeDate(DateFrom, DateTo))
		{
			if (isBusinessDay(DateFrom))
				ActualVacations++;
			IncreadDateByOneDay(DateFrom);
		}
		return ActualVacations;
	}
	short CalclateActualVacationDaysInPeriod(clsDate DateTo) {
		return CalclateActualVacationDaysInPeriod(*this, DateTo);
	}

	static clsDate VacationEndDate(clsDate DateFrom, short ActualVacations) {
		clsDate DateTo = DateFrom;
		do
		{
			IncreadDateByOneDay(DateTo);

		} while (CalclateActualVacationDaysInPeriod(DateFrom, DateTo) != ActualVacations);
		return DateTo;
	}
	clsDate VacationEndDate(short ActualVacations) {
		return VacationEndDate(*this, ActualVacations);
	}




























};

