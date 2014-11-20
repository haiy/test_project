#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>

int main()
{
    using namespace std;
    ifstream fin;
    ofstream fout;
    char fnm_in[16];

    const string words = "Test words!";
    cout << "Input the file name:\n";
    cin >> fnm_in;
    fout.open(fnm_in,ios::app);

    if( fout.fail() )
    {
        cout << "file open error!\n";
        exit(0);
    }
    cout << "This is the words will be shown up,";
    cout << words << endl;

    fout << words ;
    fout << '\n' ;
    fout.close();
}
