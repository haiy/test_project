#include <iostream>
class ISmart
{
public:
    virtual std::string Name() = 0;
};

class Galaxy : public ISmart
{
public:
    std::string Name()
    {
        return "Galaxy";
    }
};

class Titan : public ISmart
{
public:
    std::string Name()
    {
        return "Galaxy";
    }
};

class Lumia : public ISmart
{
public:
    std::string Name()
    {
        return "Lumia";
    }
};


/*=========================*/
class IDumb
{
public:
    virtual std::string Name() = 0;
};

class Asha : public IDumb
{
public:
    std::string Name()
    {
        return "Asha";
    }
};

class Primo : public IDumb
{
public :
    std::string Name()
    {
        return "Guru";
    }
};

class Genie : public IDumb
{
public :
    std::string Name()
    {
        return "Genie";
    }
};

