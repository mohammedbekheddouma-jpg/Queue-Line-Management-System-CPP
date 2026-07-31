//ProgrammingAdvices.com
//Mohammed Abu-Hadhoud

#pragma once

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class clsDate
{
private:

    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

public:

    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(string sDate)
    {
        // سيتم إكمال التحويل من النص لاحقاً
        _Day = 1;
        _Month = 1;
        _Year = 1900;
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DateOrderInYear, short Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);

        _Day = Date1.GetDay();
        _Month = Date1.GetMonth();
        _Year = Date1.GetYear();
    }

    //==========================
    // Setters & Getters
    //==========================

    void SetDay(short Day)
    {
        _Day = Day;
    }

    short GetDay() const
    {
        return _Day;
    }

    void SetMonth(short Month)
    {
        _Month = Month;
    }

    short GetMonth() const
    {
        return _Month;
    }

    void SetYear(short Year)
    {
        _Year = Year;
    }

    short GetYear() const
    {
        return _Year;
    }

    void Print()
    {
        cout << DateToString() << endl;
    }

    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        return clsDate(
            now->tm_mday,
            now->tm_mon + 1,
            now->tm_year + 1900
        );
    }

    static string GetSystemDateTimeString()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        return to_string(now->tm_mday) + "/" +
               to_string(now->tm_mon + 1) + "/" +
               to_string(now->tm_year + 1900) + " - " +
               to_string(now->tm_hour) + ":" +
               to_string(now->tm_min) + ":" +
               to_string(now->tm_sec);
    }
	    static bool IsValidDate(clsDate Date)
    {
        if (Date.GetDay() < 1 || Date.GetDay() > 31)
            return false;

        if (Date.GetMonth() < 1 || Date.GetMonth() > 12)
            return false;

        if (Date.GetMonth() == 2)
        {
            if (isLeapYear(Date.GetYear()))
            {
                if (Date.GetDay() > 29)
                    return false;
            }
            else
            {
                if (Date.GetDay() > 28)
                    return false;
            }
        }

        short DaysInMonth =
            NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear());

        if (Date.GetDay() > DaysInMonth)
            return false;

        return true;
    }

    bool IsValid()
    {
        return IsValidDate(*this);
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.GetDay()) + "/" +
               to_string(Date.GetMonth()) + "/" +
               to_string(Date.GetYear());
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    static bool isLeapYear(short Year)
    {
        return ((Year % 4 == 0 && Year % 100 != 0) ||
                (Year % 400 == 0));
    }

    bool isLeapYear()
    {
        return isLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return isLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;

        short Days[12] =
        {
            31,28,31,30,31,30,
            31,31,30,31,30,31
        };

        if (Month == 2)
            return isLeapYear(Year) ? 29 : 28;

        return Days[Month - 1];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }
	    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;

        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;

        // 0 = Sunday, 1 = Monday, ...
        return (Day + y + (y / 4) - (y / 100) +
                (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] =
        {
            "Sun", "Mon", "Tue",
            "Wed", "Thu", "Fri", "Sat"
        };

        return arrDayNames[DayOfWeekOrder];
    }

    static string DayShortName(short Day, short Month, short Year)
    {
        return DayShortName(DayOfWeekOrder(Day, Month, Year));
    }

    string DayShortName()
    {
        return DayShortName(_Day, _Month, _Year);
    }

    static string MonthShortName(short MonthNumber)
    {
        string Months[12] =
        {
            "Jan","Feb","Mar","Apr",
            "May","Jun","Jul","Aug",
            "Sep","Oct","Nov","Dec"
        };

        return Months[MonthNumber - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }
	    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        // Index of the first day (0 = Sun)
        int Current = DayOfWeekOrder(1, Month, Year);

        printf("\n  _______________%s_______________\n\n",
               MonthShortName(Month).c_str());

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }

        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(int Year)
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");

        for (int i = 1; i <= 12; i++)
            PrintMonthCalendar(i, Year);
    }

    void PrintYearCalendar()
    {
        PrintYearCalendar(_Year);
    }

    static short DaysFromTheBeginingOfTheYear(short Day,
                                              short Month,
                                              short Year)
    {
        short TotalDays = 0;

        for (int i = 1; i < Month; i++)
            TotalDays += NumberOfDaysInAMonth(i, Year);

        TotalDays += Day;

        return TotalDays;
    }

    short DaysFromTheBeginingOfTheYear()
    {
        return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    }
	    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;

        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        Date.SetYear(Year);
        Date.SetMonth(1);

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear());

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.SetMonth(Date.GetMonth() + 1);
            }
            else
            {
                Date.SetDay(RemainingDays);
                break;
            }
        }

        return Date;
    }

    void AddDays(short Days)
    {
        short RemainingDays =
            Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);

        short MonthDays = 0;

        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.GetYear() < Date2.GetYear()) ? true :
               ((Date1.GetYear() == Date2.GetYear()) ?
               ((Date1.GetMonth() < Date2.GetMonth()) ? true :
               ((Date1.GetMonth() == Date2.GetMonth()) ?
               (Date1.GetDay() < Date2.GetDay()) : false))
               : false);
    }

    bool IsDateBeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.GetYear() == Date2.GetYear()) &&
               (Date1.GetMonth() == Date2.GetMonth()) &&
               (Date1.GetDay() == Date2.GetDay());
    }

    bool IsDateEqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date.GetDay() ==
                NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear()));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }
	    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date.GetMonth()))
            {
                Date.SetDay(1);
                Date.SetMonth(1);
                Date.SetYear(Date.GetYear() + 1);
            }
            else
            {
                Date.SetDay(1);
                Date.SetMonth(Date.GetMonth() + 1);
            }
        }
        else
        {
            Date.SetDay(Date.GetDay() + 1);
        }

        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2,
        bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        if (IncludeEndDay)
            Days++;

        return Days * SwapFlagValue;
    }

    int GetDifferenceInDays(clsDate Date2,
        bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(
            DateOfBirth,
            clsDate::GetSystemDate(),
            true);
    }

    static clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        for (int i = 0; i < 7; i++)
            Date = AddOneDay(Date);

        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 0; i < Weeks; i++)
            Date = IncreaseDateByOneWeek(Date);

        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }
	    static clsDate IncreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.GetMonth() == 12)
        {
            Date.SetMonth(1);
            Date.SetYear(Date.GetYear() + 1);
        }
        else
        {
            Date.SetMonth(Date.GetMonth() + 1);
        }

        // إذا أصبح اليوم أكبر من عدد أيام الشهر الجديد
        short NumberOfDaysInCurrentMonth =
            NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear());

        if (Date.GetDay() > NumberOfDaysInCurrentMonth)
        {
            Date.SetDay(NumberOfDaysInCurrentMonth);
        }

        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    clsDate IncreaseDateByXDays(short Days, clsDate& Date)
    {
        for (short i = 0; i < Days; i++)
        {
            Date = AddOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByXDays(short Days)
    {
        IncreaseDateByXDays(Days, *this);
    }

    clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 0; i < Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }

        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() + 1);
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    clsDate IncreaseDateByXYears(short Years, clsDate& Date)
    {
        Date.SetYear(Date.GetYear() + Years);
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() + 10);
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
    {
        Date.SetYear(Date.GetYear() + Decades * 10);
        return Date;
    }

    void IncreaseDateByXDecades(short Decades)
    {
        IncreaseDateByXDecades(Decades, *this);
    }

    clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() + 100);
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    clsDate IncreaseDateByOneMillennium(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() + 1000);
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }
	    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date.GetDay() == 1)
        {
            if (Date.GetMonth() == 1)
            {
                Date.SetMonth(12);
                Date.SetDay(31);
                Date.SetYear(Date.GetYear() - 1);
            }
            else
            {
                Date.SetMonth(Date.GetMonth() - 1);
                Date.SetDay(
                    NumberOfDaysInAMonth(
                        Date.GetMonth(),
                        Date.GetYear()));
            }
        }
        else
        {
            Date.SetDay(Date.GetDay() - 1);
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate& Date)
    {
        for (int i = 0; i < 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 0; i < Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }

        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.GetMonth() == 1)
        {
            Date.SetMonth(12);
            Date.SetYear(Date.GetYear() - 1);
        }
        else
        {
            Date.SetMonth(Date.GetMonth() - 1);
        }

        short NumberOfDaysInCurrentMonth =
            NumberOfDaysInAMonth(
                Date.GetMonth(),
                Date.GetYear());

        if (Date.GetDay() > NumberOfDaysInCurrentMonth)
        {
            Date.SetDay(NumberOfDaysInCurrentMonth);
        }

        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
    {
        for (short i = 0; i < Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 0; i < Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }

        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }
	    static clsDate DecreaseDateByOneYear(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() - 1);
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
    {
        Date.SetYear(Date.GetYear() - Years);
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() - 10);
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
    {
        Date.SetYear(Date.GetYear() - (Decades * 10));
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() - 100);
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date.SetYear(Date.GetYear() - 1000);
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }
	    static short IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(
            Date.GetDay(),
            Date.GetMonth(),
            Date.GetYear()) == 6;
    }

    short IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        // Weekend = Friday & Saturday
        short DayIndex = DayOfWeekOrder(
            Date.GetDay(),
            Date.GetMonth(),
            Date.GetYear());

        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(
            Date.GetDay(),
            Date.GetMonth(),
            Date.GetYear());
    }

    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date1)
    {
        clsDate EndOfMonthDate;

        EndOfMonthDate.SetDay(
            NumberOfDaysInAMonth(
                Date1.GetMonth(),
                Date1.GetYear()));

        EndOfMonthDate.SetMonth(Date1.GetMonth());
        EndOfMonthDate.SetYear(Date1.GetYear());

        return GetDifferenceInDays(Date1, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date1)
    {
        clsDate EndOfYearDate;

        EndOfYearDate.SetDay(31);
        EndOfYearDate.SetMonth(12);
        EndOfYearDate.SetYear(Date1.GetYear());

        return GetDifferenceInDays(Date1, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }
	    // Calculate business days between two dates
    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short Days = 0;

        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;

            DateFrom = AddOneDay(DateFrom);
        }

        return Days;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        return CalculateBusinessDays(DateFrom, DateTo);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;

        for (short i = 1; i <= VacationDays; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = AddOneDay(DateFrom);
        }

        while (WeekEndCounter--)
        {
            DateFrom = AddOneDay(DateFrom);
        }

        return DateFrom;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) &&
                !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare
    {
        Before = -1,
        Equal = 0,
        After = 1
    };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return Equal;

        return After;
    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }

};