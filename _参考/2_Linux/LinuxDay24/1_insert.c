#include <func.h>
#include <mysql/mysql.h>
#include <stdlib.h>

int main()
{
    //初始化MYSQL连接
    MYSQL conn;
    MYSQL* pconn = mysql_init(&conn);

    //与MySQL服务器建立连接
    pconn = mysql_real_connect(&conn, "localhost", "root", "1234", "58th", 0, NULL, 0);
    if(pconn == NULL) {
        printf("%s\n", mysql_error(&conn));
        return EXIT_FAILURE;
    }

    //设置客户端的编码规则，防止出现乱码的情况
    mysql_query(pconn, "set names utf8");

    //进行查询操作
    //const char * query = "INSERT INTO torder VALUES(5, '平底锅', 7)";
    const char * query = "INSERT INTO torder VALUES(7, '平底锅', 7)";
    int ret = mysql_query(pconn, query);
    if(ret !=0) {
        printf("(%d, %s)\n", mysql_errno(pconn), mysql_error(pconn));
        return EXIT_FAILURE;
    } else {
        printf("QUERY OK, %ld row afftected.\n", 
               mysql_affected_rows(pconn));
    }

    mysql_close(pconn);
    return 0;
}

