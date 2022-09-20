#include <iostream>
#include <conio.h>

using namespace std;

namespace LectureKHU
{
    /// <summary>
    /// ChA <-> ChB를 바꾼다.
    /// </summary>
    void Custom_Swap(char* ChA, char* ChB)
    {
        char Temp = *ChA;
        *ChA = *ChB;
        *ChB = Temp;
    }

    /// <summary>
    /// Source 문자열을 Destination으로 Copy한다.
    /// </summary>
    /// <param name="Source">원본 문자열(복사할 문자열)</param>
    /// <param name="Destination">대상 문자열</param>
    /// <param name="SourceSize">원본 문자열에서 복사할 크기</param>
    char* Custom_StringCopy1(char* Source, char* Destination, int SourceSize)
    {
        for (int i = 0; i < SourceSize; i++)
        {
            Destination[i] = Source[i];
        }
        Destination[SourceSize] = '\0';

        return Destination;
    }

    /// <summary>
    /// <para/>Source 문자열을 Destination으로 Copy한다.
    /// <para/>Source 문자열의 끝을 읽어준다.
    /// </summary>
    /// <param name="Source">원본 문자열</param>
    /// <param name="Destination">대상 문자열</param>
    char* Custom_StringCopy2(char* Source, char* Destination)
    {
        char* SrcTemp = Source;
        int count = 0;
        while (*SrcTemp != '\0')
        {
            Destination[count] = *SrcTemp;
            SrcTemp++;
            count++;
        }
        Destination[count] = '\0';

        return Destination;
    }

    /// <summary>
    /// Source 문자열을 새로 만들어서 리턴한다.
    /// </summary>
    /// <param name="Source">원본 문자열</param>
    char* Custom_StringCopy3(char* Source)
    {
        char* str = nullptr;
        char* Srccopy = Source;
        int size = 0;
        if (Srccopy != nullptr)
        {
            while (*Srccopy != '\0')
            {
                Srccopy++;
                size++;
            }
            str = new char[size + 1];
            for (int i = 0; i < size; i++)
            {
                str[i] = Source[i];
            }
            str[size] = '\0';
        }
        return str;
    }


    /// <summary>
    /// char 문자열 길이 측정
    /// </summary>
    /// <param name="str">끝이 NULL문자(0)로 끝나는 문자열</param>
    /// <returns>문자열 길이(NULL문자 제외)</returns>
    int Custom_Strlen(char* str)
    {
        int nCount = 0;
        if (str != nullptr)
        {
            while (*str != '\0')
            {
                /*-------------------------------------------------------
                문자열의 끝은 NULL('\0', 0)로 끝난다.
                문자열의 끝에 도달할 때까지 Count를 증가시킨다.
                단, NULL까지는 세지 않았다.
                -------------------------------------------------------*/
                nCount++;
                str++;
            }
        }
        return nCount;
    }

    /// <summary>
    /// 문자열 합쳐서 새로운 문자열을 반환한다.
    /// </summary>
    /// <param name="szStr1">문자열1</param>
    /// <param name="szStr2">문자열2</param>
    /// <returns></returns>
    char* Custom_Strcat(char* szStr1, char* szStr2)
    {
        char* szStrout = nullptr;
        if (szStr1 != nullptr && szStr2 != nullptr)
        {
            int sz1 = Custom_Strlen(szStr1);
            int sz2 = Custom_Strlen(szStr2);

            if (sz1 > 0 && sz2 > 0)
            {
                szStrout = new char[sz1 + sz2 + 1];
                for (int i = 0; i < sz1; i++)
                {
                    szStrout[i] = szStr1[i];
                }
                for (int j = 0; j < sz2; j++)
                {
                    szStrout[j + sz1] = szStr2[j];
                }
                szStrout[sz1 + sz2] = '\0';
            }
        }
        return szStrout;
    }

    /// <summary>
    /// 원본 문자열의 소문자를 대문자로 바꿔준다.
    /// </summary>
    /// <param name="str">원본 문자열</param>
    void Custom_ToUpperCase(char* str)
    {
        while (*str != '\0')
        {
            //문자열의 끝까지 체크한다.
            if (*str >= 'a' && *str <= 'z')
            {
                //문자가 a(97)~z(122)일 경우, A(65)~Z(90)대역으로 바꾸기 위해서 
                //(a)97 - (A)65 = "32"를 빼준다.
                *str -= ('a' - 'A');
            }
            str++; //문자열 포인터를 맨앞에서부터 한칸씩 옮긴다.
        }
    }

    /// <summary>
    /// 원본 문자열의 대문자를 소문자로 바꿔준다.
    /// </summary>
    /// <param name="str">원본 문자열</param>
    void  Custom_ToLowerCase(char* str)
    {
        while (*str != '\0')
        {
            //문자열의 끝까지 체크한다.
            if (*str >= 'A' && *str <= 'Z')
            {
                //문자가 A(65)~Z(90)일 경우, a(97)~z(122)대역으로 바꾸기 위해서 
                //(a)97 - (A)65 = "32"를 더해준다.
                *str += ('a' - 'A');
            }
            str++; //문자열 포인터를 맨앞에서부터 한칸씩 옮긴다.
        }
    }

    /// <summary>
    /// 원본 문자열을 거꾸로 바꿔준다.
    /// </summary>
    /// <param name="str">원본 문자열</param>
    void Custom_ReverseString(char* str)
    {
        /*---------------------------------------------------------
        마지막의 NULL문자는 건드리지 않고, 배열의 절반을 Swap해주면 거꾸로 출력된다.

        EX1) [0] [1] [2] [3] [4] [5]
              H   E   L   L   O '\0'
              O               H      (0,4 SWAP)
                  L       E          (1,3 SWAP), Done

        EX2) [0] [1] [2] [3] [4]
              H   E   L   L '\0'
              L           H      (0,3 SWAP)
                  L   E          (1,2 SWAP), Done
        ---------------------------------------------------------*/
        int len = Custom_Strlen(str);
        for (int i = 0; i < len / 2; i++)
        {
            Custom_Swap(str + i, str + len - 1 - i);
        }
    }

    int L20220920_2_main()
    {
        char Word1[] = "HelloWorld";
        char Word2[] = "NiceToMeetYou";

        cout << "[1] Word1 : " << Word1 << endl;
        cout << "[2] Word2 : " << Word2 << endl;

        Custom_ReverseString(Word1);
        cout << "[3] Reverse Word1 : " << Word1 << endl;

        Custom_ReverseString(Word1);
        cout << "[4] ReReverse Word1 : " << Word1 << endl;

        char* Word3 = Custom_Strcat(Word1, Word2);
        cout << "[5] Combined Word3 : " << Word3 << endl;
        cout << "[5] Combined Word3 Length : " << Custom_Strlen(Word3) << endl;

        Custom_ToUpperCase(Word3);
        cout << "[6] Combined Word3 Uppercase : " << Word3 << endl;

        Custom_ToLowerCase(Word3);
        cout << "[7] Combined Word3 Lowercase : " << Word3 << endl;

        char Word4[50] = { 0, };
        cout << "[8] StringCopy_SourceCopy : " << Custom_StringCopy2(Word3, Word4) << endl;

        char* Word5 = Custom_StringCopy3(Word4);
        cout << "[9] StringCopy_CreateNewone : " << Word5 << endl;
        return 0;
    }
}


