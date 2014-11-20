#include <iostream>
#include <string>

void new_line();

int main()
{
using namespace std;
    string first_name, last_name, record_name;
    string motto = "Your records are our records!";

    cout << "Enter your first name and last name :\n";
    cin >> first_name >> last_name;
    new_line();

    record_name = last_name + "," + first_name;
    cout << "Your name in our records is :\n";
    cout << record_name << endl;

    cout << "Our motto is :" << motto << endl;

    cout << "Please suggest a better motto (one line)\n";
    getline(cin,motto);
    cout << "Our new motto will be :" << motto << endl;

    return 0;
}

void new_line()
{
using namespace std;
    char symbol;
    do
    {
        cin.get(symbol);
    }while( symbol != '\n' );
}
