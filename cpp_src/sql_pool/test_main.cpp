#include "test_main.h"
#include "mysql_pool.h"

using namespace std;
using namespace haiy::sqlpool;


void q1(MySQLPool * mpl, string &query)
{
    MysqlLine sqlHandler(mpl);
    if (!sqlHandler.Query(query.c_str()))
    {
        cout << "Query failed\n";
        exit(-1);
    }
    if (!sqlHandler.AllocateQueryResult() )
    {
        cout << "alloc failed\n";
        exit(-1);
    }
    HAIY_ROW itemId = sqlHandler.GetQueryResult();
    cout << "Here..." ;
    while (NULL != itemId)
    {
        //cout << "Get itemId.\n";
        cout << itemId[0] << endl;
        itemId = sqlHandler.GetQueryResult();
    }
    sqlHandler.FreeQueryResult();
}

void insert(MySQLPool *mpl, string &query)
{
    MysqlLine sqlHandler(mpl);
}

int main(int argc, char ** argv)
{
    //bool DBG = 1;
    string host("localhost");
    string user("");
    string passwd("");
    string db_used("");
    MySQLPool mpl;
    mpl.Initialize(2, host, user, passwd, db_used);
    //MySQLPool mpl = MySQLPool();
    //ThreadFunction = &test_connect;
    //threads_init(2, &mpl);

    string qry1("select title from women_wear.itemlist limit 1000");
    string qry2("select count(*) from women_wear.itemlist ");
    boost::thread t1(q1, &mpl, qry1);
    boost::thread t2(q1, &mpl, qry2);
    t1.join();
    t2.join();

    return 0;
}
