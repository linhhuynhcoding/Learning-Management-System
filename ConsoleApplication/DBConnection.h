#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <fcntl.h>
#include <io.h>

using namespace std;

#pragma once
class DBConnection
{
public:
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;

	DBConnection();
	~DBConnection();

	void checkSQLResult(SQLRETURN retCode, const std::string& message, SQLHANDLE handle = nullptr, SQLSMALLINT handleType = SQL_HANDLE_STMT);
	void logODBCError(SQLHANDLE handle, SQLSMALLINT handleType, const string& contextMessage);
};

