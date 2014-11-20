#include <iostream>
#include <cstdlib>
using namespace std;

class DayOfYear
{
public:
    void output();
    void input();

    void set(int new_month, int new_day);
    int get_month();
    int get_day();

private:
    void check_date();
    int month;
    int day;
};

int main()
{
    DayOfYear today, batch_birthday;
    cout << "Enter today's date :\n";
    today.input();
    cout << "Today's date is :\n";
    today.output();

    batch_birthday.set(3, 21);
    cout << "J.S. Batch's birthday is :\n";
    batch_birthday.output();

    if ( today.get_month() == batch_birthday.get_month()
        && today.get_day() == batch_birthday.get_day() )
    {
        cout << "Happy Birthday John !\n";
    }
    else
    {
        cout << "Happy unBirthday John !\n";
    }

    return 0;
}

void DayOfYear::output()
{
    cout << "The date is :" << month 
        << "," << day
        << endl;
}

void DayOfYear::input()
{
    cout << "Enter the month as a value :\n";
    cin >> month;

    cout << "Enter the day as a value :\n";
    cin >> day;

    check_date();
}

void DayOfYear::set(int month, int day)
{
    month = month;
    day = day;
    check_date();
}

void DayOfYear::check_date()
{
    if ( (month < 1) || (month > 12) 
        || ( day < 1) || (day > 31) )
    {
        cout << "Illgal date.Aborting program.\n";
        exit(1);
    }
}

int DayOfYear::get_month()
{
    return month;
}

int DayOfYear::get_day()
{
    return day;
}
