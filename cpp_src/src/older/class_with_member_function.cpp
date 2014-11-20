#include <iostream>
using namespace std;

class DayOfYear
{
public:
    void output();
    int month;
    int day;
};

int main()
{
    DayOfYear today, birthday;

    cout << "Enter today's date:\n";
    cout << "Enter month as a value:\n";
    cin >> today.month;
    cout << "Enter the day of the month:\n";
    cin >> today.day;

    cout << "Enter your birthday:\n";
    cout << "Enter month as a value:\n";
    cin >> birthday.month;
    cout << "Enter the day of the month:\n";
    cin >> birthday.day;

    cout << "Today's date is :\n";
    today.output();

    cout << "Your birthday is :\n"; 
    birthday.output();

    if (today.month == birthday.month
        && today.day == birthday.day)
    {
        cout << "Happy birthday !\n" ;
    }
    else
    {
        cout << "Happy unbirthday !\n";
    }

    return 0;


}

void DayOfYear::output() 
{
    cout << "Month = " << month
        << ", day = " << day << endl;
}
