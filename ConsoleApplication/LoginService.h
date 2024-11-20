#include "DBConnection.h"
#include <iostream>

using namespace std;

#pragma once
class LoginService
{
	DBConnection* db;

public:
	LoginService(DBConnection* mydb) {
		db = mydb;
	}

	bool checkpass(string user, string pass, int role) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spLogin(?, ?, ?)}";
		SQLRETURN retCode;
		retCode = SQLPrepare(db->hStmt, procedureCall, SQL_NTS);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to prepare procedure call");
			return false;
		}
		db->checkSQLResult(retCode, "Failed to prepare procedure call", db->hEnv, SQL_HANDLE_STMT);

		//SQLRETURN retCode = SQLExecDirect(db->hStmt, procedureCall, SQL_NTS);
		//if (retCode != SQL_SUCCESS) {
		//	db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to prepare procedure call");
		//	return 1;
		//}
		//db->checkSQLResult(retCode, "Failed to execute query", db->hEnv, SQL_HANDLE_ENV);

		SQLCHAR* _user = (SQLCHAR*)(const_cast<char*>(user.c_str()));
		SQLCHAR* _pass= (SQLCHAR*)(const_cast<char*>(pass.c_str()));
		retCode = SQLBindParameter(
			db->hStmt,                     // Statement handle
			1,                         // Parameter number (1-based index)
			SQL_PARAM_INPUT,           // Input parameter
			SQL_C_CHAR,                // C data type
			SQL_VARCHAR,               // SQL data type
			50,                         // Column size (ignor	ed for integers)
			0,                         // Decimal digits (ignored for integers)
			_user,                // Pointer to parameter value
			0,                         // Buffer length (ignored for integers)
			NULL                       // Indicator variable (NULL means not NULL)
		);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
		db->checkSQLResult(retCode, "Failed to bind input parameter 1");
		
		
		role--;
		SQLINTEGER _role = role;

		retCode = SQLBindParameter(
			db->hStmt,                     // Statement handle
			2,                         // Parameter number (1-based index)
			SQL_PARAM_INPUT,           // Input parameter
			SQL_C_CHAR,                // C data type
			SQL_VARCHAR,               // SQL data type
			255,                         // Column size (ignor	ed for integers)
			0,                         // Decimal digits (ignored for integers)
			_pass,                // Pointer to parameter value
			0,                         // Buffer length (ignored for integers)
			NULL                       // Indicator variable (NULL means not NULL)
		);
		db->checkSQLResult(retCode, "Failed to bind input parameter 2");

		retCode = SQLBindParameter(
			db->hStmt,                     // Statement handle
			3,                         // Parameter number (1-based index)
			SQL_PARAM_INPUT,           // Input parameter
			SQL_C_LONG,                // C data type
			SQL_INTEGER,               // SQL data type
			0,                         // Column size (ignor	ed for integers)
			0,                         // Decimal digits (ignored for integers)
			&_role,                // Pointer to parameter value
			0,                         // Buffer length (ignored for integers)
			NULL                       // Indicator variable (NULL means not NULL)
		);
		db->checkSQLResult(retCode, "Failed to bind input parameter 3");

		SQLFreeStmt(db->hStmt, SQL_CLOSE);
		retCode = SQLExecute(db->hStmt);

		if (retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Procedure execution failed");

			// Attempt to fetch additional error information if available
			SQLWCHAR errorMessage[256];
			SQLLEN indicator;
			retCode = SQLFetch(db->hStmt);
			while (retCode == SQL_SUCCESS) {
				SQLGetData(db->hStmt, 2, SQL_C_WCHAR, errorMessage, sizeof(errorMessage), &indicator);
				std::wcout << L"Error Message: " << errorMessage << std::endl;
				retCode = SQLFetch(db->hStmt);
			}

			// Handle multiple result sets
			while (SQLMoreResults(db->hStmt) == SQL_SUCCESS) {
				retCode = SQLFetch(db->hStmt);
				while (retCode == SQL_SUCCESS) {
					SQLGetData(db->hStmt, 2, SQL_C_WCHAR, errorMessage, sizeof(errorMessage), &indicator);
					std::wcout << L"Additional Error Message: " << errorMessage << std::endl;
					retCode = SQLFetch(db->hStmt);
				}
			}
			return false;
		}

		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to  execute procedure");
			return false;
		}
		db->checkSQLResult(retCode, "Failed to execute procedure");
		SQLWCHAR errorMessage[256];
		SQLLEN indicator;
		retCode = SQLFetch(db->hStmt);
		while (retCode == SQL_SUCCESS) {
			SQLGetData(db->hStmt, 2, SQL_C_WCHAR, errorMessage, sizeof(errorMessage), &indicator);
			std::wcout << L"Error Message: " << errorMessage << std::endl;
			retCode = SQLFetch(db->hStmt);
			return false;
		}

		// Handle multiple result sets
		while (SQLMoreResults(db->hStmt) == SQL_SUCCESS) {
			retCode = SQLFetch(db->hStmt);
			while (retCode == SQL_SUCCESS) {
				SQLGetData(db->hStmt, 2, SQL_C_WCHAR, errorMessage, sizeof(errorMessage), &indicator);
				std::wcout << L"Additional Error Message: " << errorMessage << std::endl;
				retCode = SQLFetch(db->hStmt);
				return false;
			}
		}
		cout << retCode << "Success";
		return true;
	}
};

