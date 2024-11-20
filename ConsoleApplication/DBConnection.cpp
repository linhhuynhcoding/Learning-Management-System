#include "DBConnection.h"

DBConnection::DBConnection()
{

    SQLRETURN retCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    checkSQLResult(retCode, "Failed to allocate environment handle");

    retCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    checkSQLResult(retCode, "Failed to set ODBC version");

    retCode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    checkSQLResult(retCode, "Failed to allocate database connection handle");

    SQLWCHAR connectionString[] = L"Dsn=Linh2";
    retCode = SQLDriverConnect(hDbc, NULL, connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    checkSQLResult(retCode, "Failed to connect to SQL Server");

    std::cout << "Connected to SQL Server successfully!" << std::endl;

    retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    checkSQLResult(retCode, "Failed to allocate statement handle");

    SQLWCHAR query[] = L"SELECT * FROM SinhVien";
    retCode = SQLExecDirect(hStmt, query, SQL_NTS);
    checkSQLResult(retCode, "Failed to execute query", hStmt);

    //SQLCHAR column1[256];
    //SQLWCHAR column2[4096];  // Wide character buffer
    //SQLLEN indicator1, indicator2;

    //SQLBindCol(hStmt, 1, SQL_C_CHAR, column1, sizeof(column1), &indicator1);
    //SQLBindCol(hStmt, 2, SQL_C_WCHAR, column2, sizeof(column2), &indicator2);
    //wcout << "HUỲNH\n";
    //while (SQLFetch(hStmt) == SQL_SUCCESS) {
    //    if (indicator2 == SQL_NULL_DATA) {
    //        std::wcout << L"Column 2 is NULL" << std::endl;
    //    }
    //    else {
    //        //for (int i = 1; i < 100; i++) wcout << column2[i];
    //        std::wcout << L"Column 2 (NVARCHAR): " << column2 << std::endl;
    //    }

    //    if (indicator1 == SQL_NULL_DATA) {
    //        std::cout << "Column 1 is NULL" << std::endl;
    //    }
    //    else {
    //        std::cout << "Column 1: " << column1 << std::endl;
    //    }
    //}
}

DBConnection::~DBConnection()
{
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

void DBConnection::checkSQLResult(SQLRETURN retCode, const std::string& message, SQLHANDLE handle, SQLSMALLINT handleType)
{
    if (retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO) {
        if (handle) {
            SQLWCHAR sqlState[6], errorMsg[SQL_MAX_MESSAGE_LENGTH];
            SQLINTEGER nativeError;
            SQLSMALLINT textLength;
            SQLSMALLINT record = 1;

            //SQLGetDiagRec(handleType, handle, 1, sqlState, &nativeError, errorMsg, sizeof(errorMsg), &textLength);
            while ((retCode = SQLGetDiagRec(handleType, handle, record, sqlState, &nativeError, errorMsg, sizeof(errorMsg), &textLength)) == SQL_SUCCESS) {
                cerr << "Context: " << errorMsg << endl;
                cerr << "SQLSTATE: " << sqlState << endl;
                cerr << "Native Error Code: " << nativeError << endl;
                cerr << "Error Message: " << errorMsg << endl;
                record++;
            }
            cout << retCode;
            //std::cerr << "Error: " << message << " - ";
            //cout << *errorMsg << " (SQLState: " << *sqlState << ")" << std::endl;
            //cout << nativeError << " (SQLState: " << textLength << ")" << std::endl;
        }
        else {
            std::cerr << "Error: " << message << std::endl;
        }
        exit(EXIT_FAILURE);
    }
}

void DBConnection::logODBCError(SQLHANDLE handle, SQLSMALLINT handleType, const string& contextMessage)
{
    SQLWCHAR sqlState[6];
    SQLWCHAR errorMessage[SQL_MAX_MESSAGE_LENGTH];
    SQLINTEGER nativeError;
    SQLSMALLINT textLength;
    SQLRETURN retCode;

    SQLSMALLINT record = 1;
    while ((retCode = SQLGetDiagRec(handleType, handle, record, sqlState, &nativeError, errorMessage, sizeof(errorMessage), &textLength)) == SQL_SUCCESS) {
        cerr << "Context: " << contextMessage << endl;
        wcout << "SQLSTATE: " << sqlState << endl;
        wcout << "Native Error Code: " << nativeError << endl;
        wcout << "Error Message: " << errorMessage << endl;
        record++;
    }
}
