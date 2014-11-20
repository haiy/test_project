/* Description: 这个程序是测试流作为函数参数的，参考6.2.3，p226
 * Author: haiy
 * Date:Fri Nov 29 09:03:28 CST 2013
 */
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>

using namespace std;

void make_neat( ifstream& messy_file, ofstream& neat_file,
        int number_after_decimalpoint, int field_width);

int main()
{
    ifstream fin;
    ofstream fout;

    fin.open("rawdata.dat");
    if( fin.fail() )
    {
        cout << "File open error" << endl;
        exit(1);
    }

    fout.open("neat.dat");
    if( fout.fail() )
    {
        cout << "Out file open error!" << endl;
        exit(1);
    }

    make_neat( fin, fout, 5, 12 );

    fin.close();
    fout.close();

    return 0;
}


void make_neat( ifstream& messy_file, ofstream& neat_file,
        int number_after_decimalpoint, int field_width)
{
    neat_file.setf( ios::fixed );
    neat_file.setf( ios::showpoint );
    neat_file.setf( ios::showpos );
    neat_file.precision( number_after_decimalpoint );
    cout.setf( ios::fixed );
    cout.setf( ios::showpoint );
    cout.setf( ios::showpos );
    cout.precision( number_after_decimalpoint );

    double next;
    while( messy_file >> next )
    {
        cout << setw( field_width ) << next << endl;
        neat_file << setw( field_width ) << next << endl;

    }
}

