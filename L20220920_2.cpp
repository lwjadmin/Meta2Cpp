#include <iostream>
#include <conio.h>

using namespace std;

namespace LectureKHU
{
    /// <summary>
    /// ChA <-> ChB�� �ٲ۴�.
    /// </summary>
    void Custom_Swap(char* ChA, char* ChB)
    {
        char Temp = *ChA;
        *ChA = *ChB;
        *ChB = Temp;
    }

    /// <summary>
    /// Source ���ڿ��� Destination���� Copy�Ѵ�.
    /// </summary>
    /// <param name="Source">���� ���ڿ�(������ ���ڿ�)</param>
    /// <param name="Destination">��� ���ڿ�</param>
    /// <param name="SourceSize">���� ���ڿ����� ������ ũ��</param>
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
    /// <para/>Source ���ڿ��� Destination���� Copy�Ѵ�.
    /// <para/>Source ���ڿ��� ���� �о��ش�.
    /// </summary>
    /// <param name="Source">���� ���ڿ�</param>
    /// <param name="Destination">��� ���ڿ�</param>
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
    /// Source ���ڿ��� ���� ���� �����Ѵ�.
    /// </summary>
    /// <param name="Source">���� ���ڿ�</param>
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
    /// char ���ڿ� ���� ����
    /// </summary>
    /// <param name="str">���� NULL����(0)�� ������ ���ڿ�</param>
    /// <returns>���ڿ� ����(NULL���� ����)</returns>
    int Custom_Strlen(char* str)
    {
        int nCount = 0;
        if (str != nullptr)
        {
            while (*str != '\0')
            {
                /*-------------------------------------------------------
                ���ڿ��� ���� NULL('\0', 0)�� ������.
                ���ڿ��� ���� ������ ������ Count�� ������Ų��.
                ��, NULL������ ���� �ʾҴ�.
                -------------------------------------------------------*/
                nCount++;
                str++;
            }
        }
        return nCount;
    }

    /// <summary>
    /// ���ڿ� ���ļ� ���ο� ���ڿ��� ��ȯ�Ѵ�.
    /// </summary>
    /// <param name="szStr1">���ڿ�1</param>
    /// <param name="szStr2">���ڿ�2</param>
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
    /// ���� ���ڿ��� �ҹ��ڸ� �빮�ڷ� �ٲ��ش�.
    /// </summary>
    /// <param name="str">���� ���ڿ�</param>
    void Custom_ToUpperCase(char* str)
    {
        while (*str != '\0')
        {
            //���ڿ��� ������ üũ�Ѵ�.
            if (*str >= 'a' && *str <= 'z')
            {
                //���ڰ� a(97)~z(122)�� ���, A(65)~Z(90)�뿪���� �ٲٱ� ���ؼ� 
                //(a)97 - (A)65 = "32"�� ���ش�.
                *str -= ('a' - 'A');
            }
            str++; //���ڿ� �����͸� �Ǿտ������� ��ĭ�� �ű��.
        }
    }

    /// <summary>
    /// ���� ���ڿ��� �빮�ڸ� �ҹ��ڷ� �ٲ��ش�.
    /// </summary>
    /// <param name="str">���� ���ڿ�</param>
    void  Custom_ToLowerCase(char* str)
    {
        while (*str != '\0')
        {
            //���ڿ��� ������ üũ�Ѵ�.
            if (*str >= 'A' && *str <= 'Z')
            {
                //���ڰ� A(65)~Z(90)�� ���, a(97)~z(122)�뿪���� �ٲٱ� ���ؼ� 
                //(a)97 - (A)65 = "32"�� �����ش�.
                *str += ('a' - 'A');
            }
            str++; //���ڿ� �����͸� �Ǿտ������� ��ĭ�� �ű��.
        }
    }

    /// <summary>
    /// ���� ���ڿ��� �Ųٷ� �ٲ��ش�.
    /// </summary>
    /// <param name="str">���� ���ڿ�</param>
    void Custom_ReverseString(char* str)
    {
        /*---------------------------------------------------------
        �������� NULL���ڴ� �ǵ帮�� �ʰ�, �迭�� ������ Swap���ָ� �Ųٷ� ��µȴ�.

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


