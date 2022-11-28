#include <stdlib.h>
#include <iostream>
#include <Windows.h>
//
#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/prepared_statement.h"
//
#pragma comment(lib,"mysqlcppconn.lib")
//
using namespace std;
//
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "Passw0rd";
//

std::string Utf8ToMultiByte(std::string utf8_str)
{
	std::string resultString; char* pszIn = new char[utf8_str.length() + 1];
	strncpy_s(pszIn, utf8_str.length() + 1, utf8_str.c_str(), utf8_str.length());
	int nLenOfUni = 0, nLenOfANSI = 0; wchar_t* uni_wchar = NULL;
	char* pszOut = NULL;
	// 1. utf8 Length
	if ((nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
		return nullptr;
	uni_wchar = new wchar_t[nLenOfUni + 1];
	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));
	// 2. utf8 --> unicode
	nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);
	// 3. ANSI(multibyte) Length
	if ((nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
	{
		delete[] uni_wchar; return 0;
	}
	pszOut = new char[nLenOfANSI + 1];
	memset(pszOut, 0x00, sizeof(char) * (nLenOfANSI + 1));
	// 4. unicode --> ANSI(multibyte)
	nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, pszOut, nLenOfANSI, NULL, NULL);
	pszOut[nLenOfANSI] = 0;
	resultString = pszOut;
	delete[] uni_wchar;
	delete[] pszOut;
	return resultString;
}

int main()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("guestbook");

	stmt = con->createStatement();
	sql::ResultSet* rs = stmt->executeQuery("SELECT * FROM sheet1 limit 0, 5");
	while(rs->next())
	{
		cout << rs->getInt("IDX") << ":" 
			<< Utf8ToMultiByte(rs->getString("NAME")) << ":"
			<< Utf8ToMultiByte(rs->getString("CONTENT")) << ":"
			<< rs->getInt("COUNT") 
			<< endl;
	}
	stmt->close();
	stmt = con->createStatement();
	pstmt = con->prepareStatement("insert into sheet1(NAME,CONTENT,COUNT) values(?,?,?)");
	pstmt->setString(1, "AA");
	pstmt->setString(2, "BB");
	pstmt->setInt(3, 123);
	pstmt->execute();
	stmt->close();
	stmt = con->createStatement();
	sql::ResultSet* rs2 = stmt->executeQuery("SELECT * FROM sheet1 order by idx asc");
	while (rs2->next())
	{
		cout << rs2->getInt("IDX") << ":"
			<< Utf8ToMultiByte(rs2->getString("NAME")) << ":"
			<< Utf8ToMultiByte(rs2->getString("CONTENT")) << ":"
			<< rs2->getInt("COUNT")
			<< endl;
	}
	stmt->close();

	//USE Guestbook;
	//con->setSchema("guestbook");
	//
	//stmt = con->createStatement();
	//stmt->execute("DROP TABLE IF EXISTS inventory");
	//cout << "Finished dropping table (if existed)" << endl;
	//stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
	//cout << "Finished creating table" << endl;
	//delete stmt;
	//
	//pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
	//pstmt->setString(1, "banana");
	//pstmt->setInt(2, 150);
	//pstmt->execute();
	//cout << "One row inserted." << endl;
	//
	//pstmt->setString(1, "orange");
	//pstmt->setInt(2, 154);
	//pstmt->execute();
	//cout << "One row inserted." << endl;
	//
	//pstmt->setString(1, "apple");
	//pstmt->setInt(2, 100);
	//pstmt->execute();
	//cout << "One row inserted." << endl;

	delete con;
	system("pause");
	return 0;
}