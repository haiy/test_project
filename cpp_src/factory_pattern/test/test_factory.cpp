#include <iostream>
using namespace std;
class people
{
public:
    virtual std::string MyColor() = 0;
};

class asia : public people
{
public:
    string MyColor()
    {
        return "Yellow skin";
    }
};

class america : public people
{
public:
    string MyColor()
    {
        return "White skin";
    }
};

class factory
{
public:
    people * createAisa()
    {
        return new asia();
    }

    people * createAmerica()
    {
        return new america();
    }
};

int main()
{
    factory f;
    cout << f.createAisa()->MyColor() << endl;
    cout << f.createAmerica()->MyColor() << endl;
    return 0;
}
