#include "mysql_pool.h"

using namespace std;

/*implemention of mysql pool*/
bool haiy::sqlpool::MySQLPool::Initialize(int MAX_mPoolSize, string& host,string& user, string& passwd, string& db_used) 
{
    try
    {
        mysql_library_init(0, NULL, NULL);
        for (int i=0; i<MAX_mPoolSize; i++) 
        {
            MySQLConnect(host, user, passwd, db_used);
            //cout << "The ," << i << "con!" << mSQLPool.size() << endl;
        }
        return true;
    }
    catch(...)
    {
        std::cout << "MySQL pool created failed.\n" ;
        return false;
    }
}

haiy::sqlpool::MySQLPool::MySQLPool()
{
    string host = string("localhost");
    string user = string("root");
    string passwd = string("1104");
    string db_used = string("");
    mysql_library_init(0, NULL, NULL);
    int MAX_mPoolSize = 3;
    try
    {
        mysql_library_init(0, NULL, NULL);
        for (int i=0; i<MAX_mPoolSize; i++) 
        {
            MySQLConnect(host, user, passwd, db_used);
            //cout << "The ," << i << "con!" << mSQLPool.size() << endl;
        }

    }
    catch(...)
    {
        std::cout << "MySQL pool created failed.\n" ;
    }
}

haiy::sqlpool::MySQLPool::~MySQLPool() 
{
    while (!mSQLPool.empty())
    {
        MYSQL * tmp =  mSQLPool.front();
        mSQLPool.pop();
        mysql_close(tmp);
    }
    mysql_library_end();
}

int haiy::sqlpool::MySQLPool::MySQLConnect(
        string& host, 
        string& user,
        string& passwd,
        string& db) 
{
    MYSQL * sql = mysql_init(NULL);
    mysql_options(sql, MYSQL_SET_CHARSET_NAME, "utf8");
    sql->reconnect = 1;
    if ( mysql_real_connect( sql, host.c_str(), 
                user.c_str(), passwd.c_str(), 
                db.c_str(), 0, NULL, 0) != NULL)
    {
        mSQLPool.push(sql);
        return 0;
    }
    mysql_close(sql);
    return 1;
}

MYSQL * haiy::sqlpool::MySQLPool::Get() 
{
    boost::mutex::scoped_lock lock(mPoolMutex);
    int retry = 5;
    while ( retry > 0)
    {
        MYSQL * sql = NULL;
        if (!mSQLPool.empty())
        {
            sql = mSQLPool.front();
            mSQLPool.pop();
        }
        if ( NULL != sql )
        {
            return sql;
        }
        --retry;
        usleep(100);
    }
    return NULL;
}

int haiy::sqlpool::MySQLPool::Back(MYSQL * used) {
    boost::mutex::scoped_lock lock(mPoolMutex);
    if (NULL != used )
    {
        mSQLPool.push(used);
        return 0;
    }
    return  -1;
}

/*mysql pool finished*/

//////////////////////////////////////////////////////
/*mysql connection interface with the pool*/
haiy::sqlpool::MysqlLine::MysqlLine(MySQLPool * SQLPool)
{
    mPool = SQLPool;
    mMysql = mPool->Get();
}

haiy::sqlpool::MysqlLine::~MysqlLine()
{
    mPool->Back(mMysql);
}

bool haiy::sqlpool::MysqlLine::Initialize()
{
    if (NULL == mMysql)
    {
        return false;
    }
    return ( NULL != (mSTMT = mysql_stmt_init(mMysql)) );
}

bool haiy::sqlpool::MysqlLine::Query(const std::string& query)
{
    if (!Initialize())
    {
        cout << "SQLLINE Initialize failed.\n";
        return false;
    }
    if (mysql_stmt_prepare(mSTMT, query.c_str(), query.size() ))
    {
        cout << "SQLLINE Prepare failed\n";
        cout << mysql_stmt_error(mSTMT) << endl;
        return false;
    }
    if (mysql_stmt_execute(mSTMT)) 
    {
        cout << "SQLLINE Execute failed\n";
        cout << mysql_stmt_error(mSTMT) << endl;
        return false;
    }
    return true;
}

bool haiy::sqlpool::MysqlLine::AllocateQueryResult()
{
    mColumnCount = mysql_stmt_field_count(mSTMT); 
    MYSQL_RES * meta = mysql_stmt_result_metadata(mSTMT);
    if ( mColumnCount <=0 || !meta)
    {
        cout << "SQLINE Get columnCount and meta info failed \n";
        return false;
    }
    mBind = new MYSQL_BIND [mColumnCount];
    memset(mBind, 0, sizeof(MYSQL_BIND)*mColumnCount);
    unsigned long  real_length = 0;
    for (int i=0; i<mColumnCount; i++)
    {
        mBind[i].buffer_type = MYSQL_TYPE_STRING;
        mBind[i].buffer = new char [BUFFSIZE];
        mBind[i].buffer_length = BUFFSIZE;
        mBind[i].is_null = 0;
        mBind[i].length = &real_length;
    }
    if (mysql_stmt_bind_result(mSTMT, mBind)) {
        return false;
    }
    return (0 == mysql_stmt_store_result(mSTMT));
}

char ** haiy::sqlpool::MysqlLine::GetQueryResult()
{
    if (NULL != mSTMT)
    {
        if ( 0 == mysql_stmt_fetch(mSTMT))
        {
            result = new char * [mColumnCount];
            for (int i=0; i<mColumnCount; i++)
            {
                result[i] = (char *) mBind[i].buffer;
                //cout << "real length " << *(mBind[i].length) << endl;
            }
            return result;
        }
        return NULL;
    }
    return NULL;
}

void haiy::sqlpool::MysqlLine::FreeQueryResult()
{
    for (int i=0; i<mColumnCount; i++)
    {
        delete (char * ) mBind[i].buffer;
    }
    delete [] mBind;
    delete [] result;
    mysql_stmt_free_result(mSTMT);
    mysql_stmt_close(mSTMT);
}

void haiy::sqlpool::MysqlLine::Close()
{
}
