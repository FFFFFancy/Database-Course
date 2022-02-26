#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include <stdio.h>
#include <odbcinst.h>
#include <iostream>
using namespace std;

SQLHENV henv;//�������
SQLHDBC hdbc;//���Ӿ��
SQLHSTMT hstmt;//�����
SQLRETURN retcode;//����ֵ

int main()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//���뻷�����
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//�������ݿ����Ӿ��

	retcode = SQLSetConnectAttr(hdbc, SQL_ATTR_AUTOCOMMIT, (void*)SQL_AUTOCOMMIT_OFF, SQL_IS_POINTER);
	if (!(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO))printf("�����������Գ���\n");

	retcode = SQLConnect(hdbc, (SQLCHAR*)"Library", SQL_NTS, (SQLCHAR*)"sa", SQL_NTS, (SQLCHAR*)"xxxxxxxx", SQL_NTS);
	if (!(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO))
	{
		printf("�������ݿ�ʧ��!\n");
		return -1;
	}
	else
	{
		printf("connect SQL success!");
	}

	printf("\nTABLE_book:\n");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use JY";//ʹ��JY���ݿ�
	SQLCHAR sql2[] = "select * from book";//��ѯbook���������
	retcode = SQLExecDirect(hstmt, sql1, SQL_NTS);//SQLExecDirect���˺�������ִ��SQL��䣬ִ��sql1��䣬��"use JY"
	retcode = SQLExecDirect(hstmt, sql2, SQL_NTS);//ִ��sql2���
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50], str6[50], str7[50];
		INT64 len_str1, len_str2, len_str3, len_str4, len_str5, len_str6, len_str7;
		while (SQLFetch(hstmt) != SQL_NO_DATA)
		{
			SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //��ȡ��һ������
			SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //��ȡ�ڶ�������
			SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
			SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);
			SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 50, &len_str5);
			SQLGetData(hstmt, 6, SQL_C_CHAR, str6, 50, &len_str6);
			SQLGetData(hstmt, 7, SQL_C_CHAR, str7, 50, &len_str7);	//book��7��

			printf("\n%s\t%s\t%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5, str6, str7);
		}
	}

	printf("\nTABLE_reader:\n");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql3[] = "select * from reader";//��ѯreader���������
	retcode = SQLExecDirect(hstmt, sql1, SQL_NTS);//ִ��sql1���
	retcode = SQLExecDirect(hstmt, sql3, SQL_NTS);//ִ��sql3���
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR str1[50], str2[50], str3[50], str4[50];
		INT64 len_str1, len_str2, len_str3, len_str4;
		while (SQLFetch(hstmt) != SQL_NO_DATA)
		{
			SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //��ȡ��һ������
			SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //��ȡ�ڶ�������
			SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
			SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);

			printf("\n%s\t%s\t%s\t%s\n", str1, str2, str3, str4);
		}
	}

	printf("\nTABLE_record:\n");
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql4[] = "select * from record";//��ѯrecord���������
	retcode = SQLExecDirect(hstmt, sql1, SQL_NTS);//ִ��sql1���
	retcode = SQLExecDirect(hstmt, sql4, SQL_NTS);//ִ��sql4���
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50], str6[50], str7[50];
		INT64 len_str1, len_str2, len_str3, len_str4, len_str5, len_str6, len_str7;
		while (SQLFetch(hstmt) != SQL_NO_DATA)
		{
			SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //��ȡ��һ������
			SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //��ȡ�ڶ�������
			SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
			SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);
			SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 50, &len_str5);
			//printf("len=%d", len_str5);

			printf("\n%s\t%s\t%s\t%s\t%s\n", str1, str2, str3, str4, str5);
			//if (len_str5<0)printf("NULL\n");
		}
	}	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);//�ͷ����Ӿ��
	SQLFreeHandle(SQL_HANDLE_ENV, henv);//�ͷŻ������

	printf("processes finish\n");


}