#include <iostream>
#include "product.h"

namespace Ifactory
{
class PhoneFactory
{
public:
    enum PHONE_FACTORIES
    {
        SAMSUNG,
        HTC,
        NOKIA,
    };

    virtual ISmart * GetSmart() = 0;
    virtual IDumb  * GetDumb() = 0;
    static PhoneFactory * CreateFactory(PHONE_FACTORIES factory);
};

class SamsungFactory : public PhoneFactory
{
public:
    ISmart * GetSmart()
    {
        return new Galaxy();
    }
    IDumb * GetDumb()
    {
        return new Primo();
    }
};

class HTCFactory : public PhoneFactory
{
public:
    ISmart * GetSmart()
    {
        return new Titan();
    }
    IDumb * GetDumb()
    {
        return new Genie();
    }
};

class NokiaFactory : public PhoneFactory
{
public:
    ISmart * GetSmart()
    {
        return new Lumia();
    }
    IDumb * GetDumb()
    {
        return new Asha();
    }
};
}//namepsace factory
