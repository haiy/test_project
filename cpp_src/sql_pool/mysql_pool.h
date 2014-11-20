#include <boost/thread/mutex.hpp>
#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unistd.h>


#ifndef MYSQL_POOL
#define MYSQL_POOL

typedef char ** HAIY_ROW;

namespace haiy
{
namespace sqlpool
{

class MySQLPool
{

public:
    bool Initialize(int MAX_SIZE, std::string& host, std::string& user, std::string& passwd, std::string& db_used);
    MySQLPool();
    ~MySQLPool();

    //sql pool methods
    MYSQL * Get();
    int Back(MYSQL *w);

private :
    std::queue <MYSQL *> mSQLPool;

    int MySQLConnect(std::string& host, std::string& user, std::string& passwd, std::string& db);
    boost::mutex mPoolMutex;

};

class MysqlLine
{
public:
    MysqlLine(MySQLPool * mpl);
    ~MysqlLine();
    bool Initialize();
    bool Query(const std::string& query);
    char ** GetQueryResult();
    bool AllocateQueryResult();
    void FreeQueryResult();
    void Close();

    int mColumnCount;

private:
    bool Connect();
    MySQLPool * mPool;
    MYSQL *mMysql;
    MYSQL_STMT * mSTMT;
    MYSQL_RES* mResult;
    HAIY_ROW result;

    MYSQL_BIND * mBind;

    //control the single column buffer size
    static const int BUFFSIZE = 1024;
};

}//namespace haiy
}//sqlpool
#endif
