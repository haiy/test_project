//测试文件结尾eof
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;
void add_plus_plus(ifstream& in_stream, ofstream& out_stream);

int main()
{
    ifstream fin;
    ofstream fout;

    cout << "Begin editing the files.\n";

    fin.open("cin.dat");
    if (fin.fail())
    {
        cout << "Input file open failed!\n";
        exit(1);
    }

    fout.open("cplusad.dat");
    if (fout.fail())
    {
        cout << "Output file open failed.\n";
        exit(1);
    }

    add_plus_plus(fin, fout);

    fin.close();
    fout.close();

    cout << "End of editing files.\n";
    return 0;
}

void add_plus_plus(ifstream& in_stream, ofstream& out_stream) 
{
    char next;
    while (! in_stream.eof())
    {
        if (next == 'c')
        {
            out_stream << "C++";
        }
        else
        {
            out_stream << next;
        }
        in_stream.get(next);
    }
}
