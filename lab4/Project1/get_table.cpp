#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include <stdio.h>
#include <odbcinst.h>
#include <iostream>
using namespace std;

SQLHENV henv;//环境句柄
SQLHDBC hdbc;//连接句柄
SQLHSTMT hstmt;//语句句柄
SQLRETURN retcode;//返回值

int main()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境句柄
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接句柄

	retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_AUTOCOMMIT, (void*)SQL_AUTOCOMMIT_OFF, SQL_IS_POINTER);
	if (!(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO))printf("设置连接属性出错\n");

	retcode = SQLConnect(hdbc, (SQLCHAR*)"Library", SQL_NTS, (SQLCHAR*)"sa", SQL_NTS, (SQLCHAR*)"xxxxxxxx", SQL_NTS);
	if (!(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO))
	{
		printf("连接数据库失败!\n");
		return -1;
	}
	else
	{
		printf("connect SQL success!");
	}

	printf("\nTABLE_book:\n");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use JY";//使用JY数据库
	SQLCHAR sql2[] = "select * from book";//查询book表的所有列
	retcode = SQLExecDirect(hstmt, sql1, SQL_NTS);//SQLExecDirect，此函数用于执行SQL语句，执行sql1语句，即"use JY"
	retcode = SQLExecDirect(hstmt, sql2, SQL_NTS);//执行sql2语句
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50], str6[50], str7[50];
		INT64 len_str1, len_str2, len_str3, len_str4, len_str5, len_str6, len_str7;
		while (SQLFetch(hstmt) != SQL_NO_DATA)
		{
			SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
			SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //获取第二列数据
			SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
			SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);
			SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 50, &len_str5);
			SQLGetData(hstmt, 6, SQL_C_CHAR, str6, 50, &len_str6);
			SQLGetData(hstmt, 7, SQL_C_CHAR, str7, 50, &len_str7);	//book表共7列

			printf("\n%s\t%s\t%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5, str6, str7);
		}
	}

	printf("\nTABLE_reader:\n");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql3[] = "select * from reader";//查询reader表的所有列
	retcode = SQLExecDirect(hstmt, sql1, SQL_NTS);//执行sql1语句
	retcode = SQLExecDirect(hstmt, sql3, SQL_NTS);//执行sql3语句
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR str1[50], str2[50], str3[50], str4[50];
		INT64 len_str1, len_str2, len_str3, len_str4;
		while (SQLFetch(hstmt) != SQL_NO_DATA)
		{
			SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
			SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //获取第二列数据
			SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
			SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);

			printf("\n%s\t%s\t%s\t%s\n", str1, str2, str3, str4);
		}
	}

	printf("\nTABLE_record:\n");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql4[] = "select * from record";//查询record表的所有列
	retcode = SQLExecDirect(hstmt, sql1, SQL_NTS);//执行sql1语句
	retcode = SQLExecDirect(hstmt, sql4, SQL_NTS);//执行sql4语句
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50], str6[50], str7[50];
		INT64 len_str1, len_str2, len_str3, len_str4, len_str5, len_str6, len_str7;
		while (SQLFetch(hstmt) != SQL_NO_DATA)
		{
			SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
			SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //获取第二列数据
			SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
			SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);
			SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 50, &len_str5);
			//printf("len=%d", len_str5);

			printf("\n%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5);
			//if (len_str5<0)printf("NULL\n");
		}
	}	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);//释放连接句柄
	SQLFreeHandle(SQL_HANDLE_ENV, henv);//释放环境句柄

	printf("processes finish\n");


}