#include <iostream>
#include <cstdlib>

void fill_array(int a[], const int ARRAY_SIZE);

int main()
{
using namespace std;
    const int ARRAY_SIZE = 5;
    int array[ARRAY_SIZE];
    
    fill_array(array,ARRAY_SIZE);

    int array_index = 0;
    for (array_index = 0; array_index < ARRAY_SIZE; array_index++)
    {
        cout << "Value of array_index" << array_index << endl;
        cout <<  array[array_index] << endl;
    }

    return 0;
}
void fill_array(int a[], const int ARRAY_SIZE)
{
    int array_index = 0;
    for (array_index = 0; array_index < ARRAY_SIZE; array_index++)
    {
        a[array_index] = random()%100;
    }
}

