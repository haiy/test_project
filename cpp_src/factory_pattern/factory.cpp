#include "factory.h"

using namespace Ifactory;
using namespace std;

PhoneFactory* PhoneFactory::CreateFactory(PHONE_FACTORIES factory)
{
    if (factory == SAMSUNG)
    {
        return new SamsungFactory();
    }
    else if (factory == HTC)
    {
        return new HTCFactory();
    }
    else if (factory == NOKIA)
    {
        return new NokiaFactory();
    }
    return NULL;
}
