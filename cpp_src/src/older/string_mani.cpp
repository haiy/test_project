#include <iostream>
#include <string>

int main()
{
    using namespace std;

    string first_name = "haiy", last_name = "fu";
    cout << "Your first name is :" << first_name 
         << endl
         << "Your last name is : " << last_name
         << endl;
    cout << "Your name spelled as : \n";
    int i = 0;
    for (i = 0; i < last_name.length(); i++)
    {
        cout << last_name[i] << " ";
        last_name[i] = '-';
    }
    cout << endl;

    for ( i = 0; i < last_name.length(); i++)
    {
        cout << last_name[i] << " ";
    }
    cout << endl;

    return 0;
}
