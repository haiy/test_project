#include "factory.h"

using namespace Ifactory;
using namespace std;

int main(int argc, char ** argv)
{
    PhoneFactory * f1 = PhoneFactory::CreateFactory(PhoneFactory::HTC);
    cout << "Dumb phone from Samung : " << f1->GetDumb()->Name() << endl;

    PhoneFactory * f2 = PhoneFactory::CreateFactory(PhoneFactory::NOKIA);
    cout << "Dumb phone from Samung : " << f2->GetDumb()->Name() << endl;

    PhoneFactory * f3 = PhoneFactory::CreateFactory(PhoneFactory::SAMSUNG);
    cout << "Dumb phone from Samung : " << f3->GetDumb()->Name() << endl;
}
