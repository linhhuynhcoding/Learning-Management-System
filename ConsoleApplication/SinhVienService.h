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
class SinhVienService
{
public:
	DBConnection* db;
	SinhVienService(DBConnection* mydb) {
		db = mydb;
	}

	bool DKL(string malh, string mssv) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spDangkyLop(?, ?)}";
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
		SQLCHAR* _malh = (SQLCHAR*)(const_cast<char*>(malh.c_str()));

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _mssv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, _malh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 2");
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
	bool HuyLop(string malh, string mssv) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spHuyLop(?, ?)}";
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
		SQLCHAR* _malh = (SQLCHAR*)(const_cast<char*>(malh.c_str()));

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _mssv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return false;
		}
		retCode = SQLBindParameter(db->hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, _malh, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 2");
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

	void DSLSVTable(string mssv) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLRETURN retCode;

		SQLWCHAR query[] = L"SELECT * FROM DSLOP WHERE MSSV=?";
		retCode = SQLPrepare(db->hStmt, query, SQL_NTS);
		db->checkSQLResult(retCode, "Failed to prepare query", db->hStmt);

		SQLCHAR* _mssv = (SQLCHAR*)(const_cast<char*>(mssv.c_str()));
		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLLEN indicator1, indicator2;

		retCode = SQLBindParameter(db->hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, _mssv, 0, NULL);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to bind input parameter 1");
			return;
		}
		retCode = SQLExecute(db->hStmt);
		if (retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to execute SELECT query");
			return;
		}

		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
		//wcout << "HUỲNH\n";
		cout << "\tDANH SACH LOP - SINH VIEN TALBE\n";
		cout << "\t" << string(65, '_') << "\n";
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "" << setw(5) << right << "+" << setw(30) << right << "" << setw(5) << right << '+' << endl;
		cout << "\t" << setw(5) << left << '+' << setw(20) << left << "MSSV" << setw(5) << right << "+" << setw(30) << right << "MA LH" << setw(5) << right << '+' << endl;
		cout << "\t" << string(65, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), &indicator2);
			cout << "\t" << setw(5) << left << '+' << setw(20) << left << column2 << setw(5) << right << '+' << setw(30) << right << column1 << setw(5) << right << '+' << endl;
		}
		cout << "\t" << string(65, '_') << "\n\n";
	}

	void KQHT(string mssv) {
		SQLFreeStmt(db->hStmt, SQL_CLOSE);

		SQLWCHAR procedureCall[] = L"{CALL spKetquahoctap(?)}";
		SQLRETURN retCode;
		retCode = SQLPrepare(db->hStmt, procedureCall, SQL_NTS);
		if (retCode != SQL_SUCCESS) {
			db->logODBCError(db->hStmt, SQL_HANDLE_STMT, "Failed to prepare procedure call");
			return ;
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
			return ;
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
			return ;
		}

		SQLCHAR column1[256];
		SQLCHAR column2[256];  // Wide character buffer
		SQLCHAR column4[256];  // Wide character buffer
		SQLFLOAT column5;  // Wide character buffer
		SQLFLOAT column6;  // Wide character buffer
		SQLFLOAT column7;  // Wide character buffer
		SQLINTEGER column8;  // Wide character buffer
		SQLLEN indicator1, indicator2;
		SQLBindCol(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), NULL);
		SQLBindCol(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), NULL);
		//wcout << "HUỲNH\n";
		cout << "\tKET QUA HOC TAP\n";
		cout << "\t" << string(104, '_') << "\n";
		cout << "\t"
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(20) << left << ""
			<< setw(2) << left << '+'
			<< setw(10) << left << ""
			<< setw(2) << left << '+'
			<< setw(10) << left << ""
			<< setw(2) << left << '+'
			<< setw(10) << left << ""
			<< setw(2) << right << '+' << endl;
		cout << "\t"
			<< setw(2) << left << '+'
			<< setw(20) << left << "MAMH"
			<< setw(2) << left << '+'
			<< setw(20) << left << "MALH"
			<< setw(2) << left << '+'
			<< setw(20) << left << "GKY"
			<< setw(2) << left << '+'
			<< setw(10) << left << "CKY"
			<< setw(2) << left << '+'
			<< setw(10) << left << "TONG"
			<< setw(2) << left << '+'
			<< setw(10) << left << "TRANGTHAI"
			<< setw(2) << right << '+' << endl;
		cout << "\t" << string(104, '=') << "\n";
		while (SQLFetch(db->hStmt) == SQL_SUCCESS) {

			SQLGetData(db->hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), NULL);
			SQLGetData(db->hStmt, 2, SQL_C_CHAR, column2, sizeof(column2), NULL);
			SQLGetData(db->hStmt, 5, SQL_C_DOUBLE, &column5, sizeof(column5), NULL);
			SQLGetData(db->hStmt, 6, SQL_C_DOUBLE, &column6, sizeof(column6), NULL);
			SQLGetData(db->hStmt, 7, SQL_C_DOUBLE, &column7, sizeof(column7), NULL);
			SQLGetData(db->hStmt, 8, SQL_C_LONG, &column8, sizeof(column8), NULL);

			cout<< "\t" << setprecision(2) << fixed
				<< setw(2) << left << '+'
				<< setw(20) << left << column1
				<< setw(2) << left << '+'
				<< setw(20) << left << column2
				<< setw(2) << left << '+'
				<< setw(20) << left << column5
				<< setw(2) << left << '+'
				<< setw(10) << left << column6
				<< setw(2) << left << '+'
				<< setw(10) << left << column7
				<< setw(2) << left << '+'
				<< setw(12) << left << (column8 == 0 ? "rớt" : "đậu")
				<< setw(2) << right << '+' << endl;
		}
		cout << "\t" << string(104, '_') << "\n\n";

		cout << retCode << "Success";
		return ;
	}
};

