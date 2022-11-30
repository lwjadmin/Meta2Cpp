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

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

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

std::string MultiByteToUtf8(std::string multibyte_str)
{
    char* pszIn = new char[multibyte_str.length() + 1];
    strncpy_s(pszIn, multibyte_str.length() + 1, multibyte_str.c_str(), multibyte_str.length());

    std::string resultString;

    int nLenOfUni = 0, nLenOfUTF = 0;
    wchar_t* uni_wchar = NULL;
    char* pszOut = NULL;

    // 1. ANSI(multibyte) Length
    if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
        return 0;

    uni_wchar = new wchar_t[nLenOfUni + 1];
    memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

    // 2. ANSI(multibyte) ---> unicode
    nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

    // 3. utf8 Length
    if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
    {
        delete[] uni_wchar;
        return 0;
    }

    pszOut = new char[nLenOfUTF + 1];
    memset(pszOut, 0, sizeof(char) * (nLenOfUTF + 1));

    // 4. unicode ---> utf8
    nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
    pszOut[nLenOfUTF] = 0;
    resultString = pszOut;

    delete[] uni_wchar;
    delete[] pszOut;

    return resultString;
}

void ShowMenu()
{
    cout << "1. 회원가입" << endl;
    cout << "2. 회원정보 수정" << endl;
    cout << "3. 회원탈퇴" << endl;
    cout << "4. 로그인" << endl;
    cout << "5. 프로그램 종료" << endl;

}

void ClearCin()
{
    cin.clear();
    cin.ignore(LLONG_MAX, '\n');
}

int GetIntNumber()
{
    int value = -1;
    cin >> value;
    if (cin.fail()) { ClearCin(); }
    return value;
}

int main(int argc, char* argv[])
{
    sql::Driver* driver = nullptr;
    sql::Connection* con = nullptr;
    sql::Statement* stmt = nullptr;
    sql::PreparedStatement* pstmt = nullptr;
    sql::ResultSet* rs = nullptr;
    bool bExitCalled = false;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema("guestbook");
    }
    catch (sql::SQLException e)
    {
        cout << "[SYS] SQLConnection Error Occurred. ErrorMsg : " << e.what() << endl;
        exit(-1);
    }

    while (!bExitCalled)
    {
        Sleep(500);
        system("cls");
        pstmt = con->prepareStatement("SELECT * FROM GMUSER");
        rs = pstmt->executeQuery();
        cout << "※ 회원 목록수 : " << rs->rowsCount() << endl;
        cout << "---------------------------------------------------------------" << endl;
        while (rs->next())
        {
            string strID_GMUSER = trim(rs->getString("ID_GMUSER"));
            string strUSER_ID = trim(rs->getString("USER_ID"));
            string strUSERNAME = trim(rs->getString("USERNAME"));
            strUSERNAME = strUSERNAME.empty() ? "미등록" : Utf8ToMultiByte(strUSERNAME);

            cout << strID_GMUSER << ":" << strUSER_ID << ":" << strUSERNAME << endl;
        }
        cout << "---------------------------------------------------------------" << endl;
        ShowMenu();
        cout << "---------------------------------------------------------------" << endl;
        cout << "명령어 입력 : ";
        switch (GetIntNumber())
        {
            case 1:
            {
                ClearCin();
                string strID = "";
                string strPWD = "";
                string strYN = "";
                cout << "신규계정 아이디 : ";
                getline(cin, strID);
                strID = trim(strID);
                cout << "신규계정 비밀번호 : ";
                getline(cin, strPWD);
                strPWD = trim(strPWD);
                cout << "가입하기(Y/N) : ";
                getline(cin, strYN);

                try
                {
                    if (strYN == "Y" || strYN == "y")
                    {
                        pstmt = con->prepareStatement("SELECT 1 FROM GMUSER WHERE `USER_ID` = ?");
                        pstmt->setString(1, strID);
                        rs = pstmt->executeQuery();
                        bool isExists = rs->rowsCount() > 0 ? true : false;
                        if (isExists)
                        {
                            cout << "이미 가입되어 있습니다." << endl;
                        }
                        else
                        {
                            pstmt = con->prepareStatement("INSERT INTO GMUSER(`USER_ID`,`USER_PWD`) VALUES(?,sha(?))");
                            pstmt->setString(1, strID);
                            pstmt->setString(2, strPWD);
                            pstmt->execute();
                            cout << "가입이 완료되었습니다." << endl;
                        }
                    }
                }
                catch (sql::SQLException e)
                {
                    cout << "[SYS] SQLQuery Error Occurred. ErrorMsg : " << e.what() << endl;
                }
                break;
            }
            case 2:
            {
                ClearCin();
                string strID = "";
                string strPWD = "";
                string strNAME = "";
                cout << "수정할 아이디 : ";
                getline(cin, strID);
                strID = trim(strID);

                try
                {
                    if (strID.empty())
                    {
                        cout << "아이디를 입력하세요!! " << endl;
                        break;
                    }
                    else
                    {
                        pstmt = con->prepareStatement("SELECT 1 FROM GMUSER WHERE `USER_ID` = ?");
                        pstmt->setString(1, strID);
                        rs = pstmt->executeQuery();
                        bool isExists = rs->rowsCount() > 0 ? true : false;
                        if (isExists)
                        {
                            cout << "변경 비밀번호 입력 : ";
                            getline(cin, strPWD);
                            strPWD = trim(strPWD);
                            cout << "변경 성명 입력 : ";
                            getline(cin, strNAME);
                            strNAME = trim(strNAME);

                            pstmt = con->prepareStatement("UPDATE GMUSER SET `USER_PWD`=sha(?), `USERNAME`=?  WHERE `USER_ID` = ?");
                            pstmt->setString(1, strPWD);
                            pstmt->setString(2, MultiByteToUtf8(strNAME));
                            pstmt->setString(3, strID);
                            pstmt->execute();
                            cout << "아이디 [" << strID << "]의 수정이 완료되었습니다." << endl;
                        }
                        else
                        {
                            cout << "아이디가 존재하지 않습니다!" << endl;
                        }
                    }
                }
                catch (sql::SQLException e)
                {
                    cout << "[SYS] SQLQuery Error Occurred. ErrorMsg : " << e.what() << endl;
                    Sleep(100000);
                }
                break;
            }
            case 3:
            {
                ClearCin();
                string strID = "";
                cout << "삭제할 아이디 : ";
                getline(cin, strID);
                strID = trim(strID);

                if (strID.empty())
                {
                    cout << "아이디를 입력하세요!! " << endl;
                    break;
                }
                try
                {
                    pstmt = con->prepareStatement("SELECT 1 FROM GMUSER WHERE `USER_ID` = ?");
                    pstmt->setString(1, strID);
                    rs = pstmt->executeQuery();
                    bool isExists = rs->rowsCount() > 0 ? true : false;
                    if (isExists)
                    {
                        pstmt = con->prepareStatement("DELETE FROM GMUSER WHERE `USER_ID` = ?");
                        pstmt->setString(1, strID);
                        pstmt->execute();
                        cout << "아이디 : [" << strID << "] 를 탈퇴처리하였습니다." << endl;
                    }
                    else
                    {
                        cout << "아이디가 존재하지 않습니다!" << endl;
                    }
                }
                catch (sql::SQLException e)
                {
                    cout << "[SYS] SQLQuery Error Occurred. ErrorMsg : " << e.what() << endl;
                }

                break;
            }
            case 4:
            {
                ClearCin();
                string strID = "";
                string strPWD = "";
                cout << "접속 아이디 : ";
                getline(cin, strID);
                strID = trim(strID);
                cout << "접속 비밀번호 : ";
                getline(cin, strPWD);
                strPWD = trim(strPWD);

                if (strID.empty() || strPWD.empty())
                {
                    cout << "아이디, 비밀번호를 입력하세요!! " << endl;
                    break;
                }
                try
                {
                    pstmt = con->prepareStatement("SELECT COUNT(1) AS `CNT` FROM GMUSER WHERE `USER_ID`=? AND `USER_PWD`=sha(?)");
                    pstmt->setString(1, strID);
                    pstmt->setString(2, strPWD);
                    rs = pstmt->executeQuery();

                    bool isExists = false;
                    while (rs->next())
                    {
                        isExists = rs->getInt("CNT") > 0 ? true : false;
                        break;
                    }
                    if (isExists)
                    {
                        cout << "로그인이 되었습니다." << endl;
                    }
                    else
                    {
                        cout << "로그인이 실패하였습니다." << endl;
                    }
                }
                catch (sql::SQLException e)
                {
                    cout << "[SYS] SQLQuery Error Occurred. ErrorMsg : " << e.what() << endl;
                }
                break;
            }
            case 5:
            {
                cout << "프로그램을 종료합니다." << endl;
                bExitCalled = true;
                break;
            }
            default:
            {
                cout << "유효하지 않은 입력입니다." << endl;
                break;
            }
        }//eoswitch
    }//eowhile

    delete rs;
    delete pstmt;
    delete con;
    return 0;
}