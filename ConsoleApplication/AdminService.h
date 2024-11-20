#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <fcntl.h>
#include <io.h>
#include "DBConnection.h"
#include <iomanip>

using namespace std;
#pragma once
class AdminService
{

public:
	DBConnection* db;

	AdminService(DBConnection* mydb) {
		db = mydb;

	}

	bool Taotk(string user, string pass) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spTaoTK(?, ?, ?)}";
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
		SQLCHAR* _pass = (SQLCHAR*)(const_cast<char*>(pass.c_str()));
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
			return 1;
		}
		db->checkSQLResult(retCode, "Failed to bind input parameter 1");

		retCode = SQLBindParameter(
			db->hStmt,                     // Statement handle
			3,                         // Parameter number (1-based index)
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
			2,                         // Parameter number (1-based index)
			SQL_PARAM_INPUT,           // Input parameter
			SQL_C_CHAR,                // C data type
			SQL_VARCHAR,               // SQL data type
			50,                         // Column size (ignor	ed for integers)
			0,                         // Decimal digits (ignored for integers)
			_user,                // Pointer to parameter value
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
		return 1;
		cout << retCode << "Success";
		return true;
	}

	bool ThemSv(string mssv, string ten, string namsinh, int khoa, string manganh) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spThemSV(?, ?, ?, ?, ?)}";
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

		int yyyy = (namsinh.substr(0, 4)[0] - '0')*1000 - (namsinh.substr(0, 4)[1] - '0') * 100 + (namsinh.substr(0, 4)[2] - '0') * 10 + (namsinh.substr(0, 4)[3] - '0');
		int mm = (namsinh.substr(5, 2)[0] - '0') * 10 + (namsinh.substr(5, 2)[1] - '0');
		int dd = (namsinh.substr(8, 2)[0] - '0') * 10 + (namsinh.substr(8, 2)[1] - '0');
		SQLCHAR* _mssv = (SQLCHAR*)(const_cast<char*>(mssv.c_str()));
		SQLCHAR* _ten = (SQLCHAR*)(const_cast<char*>(ten.c_str()));
		SQL_DATE_STRUCT _namsinh = {yyyy, mm, dd};
		cout << yyyy << " " << mm << " " << dd;
		SQLINTEGER _khoa = khoa;
		SQLCHAR* _manganh = (SQLCHAR*)(const_cast<char*>(manganh.c_str()));
		
		retCode = SQLBindParameter(db->hStmt, 1,SQL_PARAM_INPUT,SQL_C_CHAR, SQL_VARCHAR,20,  0, _mssv,0,NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, _ten, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 2");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &_namsinh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 3");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &_khoa, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 4");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, _manganh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 5");
			return false;
		}

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
	
	bool XoaSv(string mssv) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spXoaSV(?)}";
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

		
		SQLCHAR* _mssv = (SQLCHAR*)(const_cast<char*>(mssv.c_str()));

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _mssv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}

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
	
	bool ThemGv(string msgv, string ten, string namsinh, string trinhdo) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spThemGV(?, ?, ?, ?)}";
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

		int yyyy = (namsinh.substr(0, 4)[0] - '0') * 1000 - (namsinh.substr(0, 4)[1] - '0') * 100 + (namsinh.substr(0, 4)[2] - '0') * 10 + (namsinh.substr(0, 4)[3] - '0');
		int mm = (namsinh.substr(5, 2)[0] - '0') * 10 + (namsinh.substr(5, 2)[1] - '0');
		int dd = (namsinh.substr(8, 2)[0] - '0') * 10 + (namsinh.substr(8, 2)[1] - '0');
		SQLCHAR* _msgv = (SQLCHAR*)(const_cast<char*>(msgv.c_str()));
		SQLCHAR* _ten = (SQLCHAR*)(const_cast<char*>(ten.c_str()));
		SQL_DATE_STRUCT _namsinh = { yyyy, mm, dd };
		cout << yyyy << " " << mm << " " << dd;
		SQLCHAR* _trinhdo = (SQLCHAR*)(const_cast<char*>(trinhdo.c_str()));

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _msgv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, _ten, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 2");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &_namsinh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 3");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, _trinhdo, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 4");
			return false;
		}

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
	
	bool XoaGv(string msgv) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spXoaGV(?)}";
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


		SQLCHAR* _mssv = (SQLCHAR*)(const_cast<char*>(msgv.c_str()));

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _mssv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}

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

	void ManganhTable() {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM ChuyenNganh";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tMA NGANH TALBE\n";
		cout << "\t" << string(50, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(10) << left << "" << setw(5) << right << "+" << setw(25) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(10) << left << "MA NGANH" << setw(5) << right << "+" << setw(25) << right << "TEN NGANH" << setw(5) << right << '+' << endl;
		cout << "\t" << string(50, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(10) << left << column1 << setw(5) << right << '+' << setw(25) << right << column2 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(50, '_') << "\n";
	}

	void MamhTable() {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM MonHoc";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 3, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tMA NGANH TALBE\n";
		cout << "\t" << string(65, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(10) << left << "" << setw(5) << right << "+" << setw(40) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(10) << left << "MA MON HOC" << setw(5) << right << "+" << setw(40) << right << "TEN MON HOC" << setw(5) << right << '+' << endl;
		cout << "\t" << string(65, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 3, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(10) << left << column1 << setw(5) << right << '+' << setw(40) << right << column2 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(65, '_') << "\n\n";
	}

	void MaPgTable() {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM PhongHoc";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLINTEGER column2;  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 2, SQL_C_LONG, &column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tPHONG HOC TALBE\n";
		cout << "\t" << string(50, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(10) << left << "" << setw(5) << right << "+" << setw(25) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(10) << left << "MA PHONG" << setw(5) << right << "+" << setw(25) << right << "SIZE" << setw(5) << right << '+' << endl;
		cout << "\t" << string(50, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 2, SQL_C_LONG, &column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(10) << left << column1 << setw(5) << right << '+' << setw(25) << right << column2 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(50, '_') << "\n";
	}
	
	void SvTable() {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM SinhVien";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tSINH VIEN TALBE\n";
		cout << "\t" << string(65, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "" << setw(5) << right << "+" << setw(30) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "MSSV" << setw(5) << right << "+" << setw(30) << right << "TEN SINH VIEN" << setw(5) << right << '+' << endl;
		cout << "\t" << string(65, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(20) << left << column1 << setw(5) << right << '+' << setw(30) << right << column2 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(65, '_') << "\n\n";
	}

	void GvTable() {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM GiangVien";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tGIANG VIEN TALBE\n";
		cout << "\t" << string(65, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "" << setw(5) << right << "+" << setw(30) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "MSGV" << setw(5) << right << "+" << setw(30) << right << "TEN GIANG VIEN" << setw(5) << right << '+' << endl;
		cout << "\t" << string(65, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(20) << left << column1 << setw(5) << right << '+' << setw(30) << right << column2 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(65, '_') << "\n\n";
	}


	void GvMhTable() {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM GV_MH";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tMON HOC - GIANG VIEN TALBE\n";
		cout << "\t" << string(65, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "" << setw(5) << right << "+" << setw(30) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "MSGV" << setw(5) << right << "+" << setw(30) << right << "MA MH" << setw(5) << right << '+' << endl;
		cout << "\t" << string(65, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(20) << left << column1 << setw(5) << right << '+' << setw(30) << right << column2 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(65, '_') << "\n\n";
	}

	void LophocTable(int khoa) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM LopHoc";
		retCode = SQLExecDirect(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to execute query", db->hStmt);

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLCHAR column3[256];  // Wide character buffer
		SQLCHAR column4[256];  // Wide character buffer
		SQLINTEGER column5;  // Wide character buffer
		SQLINTEGER column6;  // Wide character buffer
		SQLCHAR column7[256];  // Wide character buffer
		SQLINTEGER column9;  // Wide character buffer
		SQLLEN indicator1, indicator2;

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), NULL);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), NULL);
		SQLBindCol(db->hStmt, 3, SQL_C_CHAR, column3, sizeof(column3), NULL);
		SQLBindCol(db->hStmt, 4, SQL_C_CHAR, column4, sizeof(column4), NULL);
		SQLBindCol(db->hStmt, 5, SQL_C_LONG, &column5, sizeof(column5), NULL);
		SQLBindCol(db->hStmt, 6, SQL_C_LONG, &column6, sizeof(column6), NULL);
		SQLBindCol(db->hStmt, 7, SQL_C_CHAR, column7, sizeof(column7), NULL);
		SQLBindCol(db->hStmt, 9, SQL_C_LONG, &column9, sizeof(column9), NULL);

		//wcout << "HUỲNH\n";
		cout << "\tLICH LOP HOC TALBE\n";
		cout << "\t" << string(158, '_') << "\n";
		cout << "\t"
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(10) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(10) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << right << '+' << endl;
		cout << "\t" 
			<< setw(2) << left << '+' 
			<< setw(20) << left << "MA LOP HOC"
			<< setw(2) << left << '+'
			<< setw(20) << left << "MA MON HOC"
			<< setw(2) << left << '+'
			<< setw(20) << left << "MA PG HOC"
			<< setw(2) << left << '+'
			<< setw(20) << left << "MAGV"
			<< setw(2) << left << '+'
			<< setw(10) << left << "CA"
			<< setw(2) << left << '+'
			<< setw(20) << left << "THU"
			<< setw(2) << left << '+'
			<< setw(10) << left << "--"
			<< setw(2) << left << '+'
			<< setw(20) << left << "--"
			<< setw(2) << right << '+' << endl;
		cout << "\t" << string(158, '=') << "\n";
		string mapp[] = { "thứ 2", "thứ 3", "thứ 4", "thứ 5", "thứ 6", "thứ 7", "cn" };
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), NULL);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), NULL);
			SQLGetData(db->hStmt, 3, SQL_C_CHAR, column3, sizeof(column3), NULL);
			SQLGetData(db->hStmt, 4, SQL_C_CHAR, column4, sizeof(column4), NULL);
			SQLGetData(db->hStmt, 5, SQL_C_LONG, &column5, sizeof(column5), NULL);
			SQLGetData(db->hStmt, 6, SQL_C_LONG, &column6, sizeof(column6), NULL);
			SQLGetData(db->hStmt, 7, SQL_C_CHAR, column7, sizeof(column7), NULL);
			SQLGetData(db->hStmt, 9, SQL_C_LONG, &column9, sizeof(column9), NULL);
			/*cout << column9
			if (column9 != khoa) continue;*/
			cout << "\t"
				<< setw(2) << left << '+'
				<< setw(20) << left << column1
				<< setw(2) << left << '+'
				<< setw(20) << left << column2
				<< setw(2) << left << '+'
				<< setw(20) << left << column3
				<< setw(2) << left << '+'
				<< setw(20) << left << column4
				<< setw(2) << left << '+'
				<< setw(10) << left << column5
				<< setw(2) << left << '+'
				<< setw(22) << left << mapp[column6]
				<< setw(2) << left << '+'
				<< setw(12) << left << (column9 == 0 ? "mở" : "khóa")
				<< setw(2) << left << '+'
				<< setw(20) << left << column7
				<< setw(2) << right << '+' << endl;

		}
		cout << "\t" << string(158, '_') << "\n\n";
	}

	bool ThemLophoc(string malh, string mamh, string mapg, string magv, string ngaystart, int ca, int ngay) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spThemLopHoc(?, ?, ?, ?, ?, ?, ?)}";
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

		int yyyy = (ngaystart.substr(0, 4)[0] - '0') * 1000 - (ngaystart.substr(0, 4)[1] - '0') * 100 + (ngaystart.substr(0, 4)[2] - '0') * 10 + (ngaystart.substr(0, 4)[3] - '0');
		int mm = (ngaystart.substr(5, 2)[0] - '0') * 10 + (ngaystart.substr(5, 2)[1] - '0');
		int dd = (ngaystart.substr(8, 2)[0] - '0') * 10 + (ngaystart.substr(8, 2)[1] - '0');
		SQLCHAR* _msgv = (SQLCHAR*)(const_cast<char*>(magv.c_str()));
		SQLCHAR* _malh = (SQLCHAR*)(const_cast<char*>(malh.c_str()));
		SQLCHAR* _mamh = (SQLCHAR*)(const_cast<char*>(mamh.c_str()));
		SQLCHAR* _mapg = (SQLCHAR*)(const_cast<char*>(mapg.c_str()));
		SQL_DATE_STRUCT _ngaystart = { yyyy, mm, dd };
		SQLINTEGER _ca = ca;
		SQLINTEGER _ngay = ngay;
		cout << yyyy << " " << mm << " " << dd;

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _malh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, _mamh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 2");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, _mapg, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 3");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, _msgv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 4");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &_ca, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 4");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &_ngay, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 4");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 7, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_DATE, 0, 0, &_ngaystart, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 4");
			return false;
		}

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

	bool KhoaLop(string malh) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spKhoaLop(?)}";
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

		SQLCHAR* _malh = (SQLCHAR*)(const_cast<char*>(malh.c_str()));

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _malh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
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
		SQLWCHAR errorMessage[2560];
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

