#include<fstream>
#include<iostream>
#include<cstdlib>

int main()
{
    using namespace std;
    ifstream in_stream;
    ofstream out_stream;
    in_stream.open("trest.txt");
    if( in_stream.fail() )
    {
        cout << "File open failed!" << endl;
        exit(1);
    }
    out_stream.open("res_test.txt");

    int first = 0;
    int second = 0;
    int third = 0;

    in_stream >> first >> second >> third;
    out_stream << "The first number is: " << third << endl;

    in_stream.close();
    out_stream.close();

    return 0;
}

