#include <cstdio> 
#include <iostream>
using namespace std;

int switch_magic(void) {
    static int i ;
    static int  state = 0;
    printf ( "Now state: %d, i:%d\n", state, i );
    switch (state)
    {
        case 0 :
            for (i=0; i<10; i++)
            {
                state = 1;
                return i;
                case 1:
                    cout << "Here " << "state " << state 
                        << ",i :" << i << endl;
            }
    }
    return -1;
}

int main()
{
    cout << switch_magic() << endl;
    cout << "=============" << endl;
    cout << switch_magic() << endl;
    cout << "=============" << endl;
    cout << switch_magic() << endl;
    cout << "=============" << endl;
    cout << switch_magic() << endl;
    cout << "=============" << endl;
    cout << switch_magic() << endl;
    cout << "=============" << endl;
    cout << switch_magic() << endl;
    cout << "=============" << endl;
    cout << switch_magic() << endl;
    return 0;
}
