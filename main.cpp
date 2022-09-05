#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "main2.h"
#include "MyFunctions.h"

#define string_empty ""


/*-------------------------------------------------------
1. using namespace 최대한 사용금지
-------------------------------------------------------*/

namespace TestFunctions {
	void PrintHex_LittleEndian(int number) {
		std::cout << std::showbase << std::hex << number << std::endl;
	}

	void PrintUppercase(std::string str) {
		std::cout << std::uppercase << str << std::endl;
	}

	void PrintNumbers_setfill(int number) {
		std::cout << std::setfill('*') << std::setw(5) << number << std::endl;
	}

	void GetStringReverse_charArray() {
		const int line_size = 100;
		char line[line_size] = { 0, };
		//memset(line, 0, sizeof(char) * line_size);
		
		std::cin.getline(line, line_size);
		//helloworld
		//p = h, q = d

		if (!std::cin.eof() && !std::cin.fail()) {
			char* p = line;
			char* q = line + (strlen(line) - 1);
			while (p < q) {
				//양 포인터의 주소값을 비교하여, 앞에서 움직이는 p의 포인터주소값이 q의 포인터주소값보다 크면 멈춘다.
				char temp = *p;
				*p = *q;
				*q = temp;

				p++;
				q--;
			}
		}
		std::cout << line << std::endl;
	}

	void GetStringReverse_stdString() {
		std::string strin;
		//'\n'을 만날때까지 String을 반환한다.
		std::getline(std::cin, strin); 

		size_t sz = strin.size();
		std::cout << "string size : " << sz << std::endl;
		//helloworld

		for (size_t i = 0; i < sz / 2; i++) {
			char tmp = strin[i];
			strin[i] = strin[sz - (i + 1)];
			strin[sz - (i + 1)] = tmp;
		}
		std::cout << strin << std::endl;
	}

	bool TryGetIntNumbers(int& numbers, bool tryAgainIfBad = false) {
		bool isS = false;
		do 
		{
			std::cin >> numbers;
			if (std::cin.eof()) {
				std::cin.clear();
				break;
			}
			isS = !std::cin.fail();
			if (isS)
			{
				break;
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(LLONG_MAX, '\n');
				if (tryAgainIfBad) 
				{
					continue;
				}
			}
		} while (true);
		return isS;
	}

	void WorkOffice() {
		std::cout << "Work In Office " << std::endl;
		std::cout << "Work In Office2 " << std::endl;
		std::cout << "Work In Office3 " << std::endl;
		std::cout << "Work In Office4 " << std::endl;
		std::cout << "Work In Office5 " << std::endl;
		std::cout << "Work In Office6 " << std::endl;
	}
	void WorkHome() {
		std::cout << "Work In Home" << std::endl;
		std::cout << "Work In Home1" << std::endl;
		std::cout << "Work In Home2" << std::endl;
		std::cout << "Work In Home3" << std::endl;
		std::cout << "Work In Home4" << std::endl;
		std::cout << "Work In Home5" << std::endl;
	}

	void Run1_TryGetIntNumbers() {
		do
		{
			int numbers = TryGetIntNumbers(numbers, true) ? numbers : -1;
			if (numbers != -1) {
				std::cout << "Result value is : " << numbers << std::endl;
			}
			else {
				break;
			}
		} while (true);
	}

	void Run2_GetStringReverse() {

		GetStringReverse_stdString();
	}
}

namespace FileIO {
	void FileOpen_CStyle(const char* fileName) {
		FILE* fp = NULL;
		fp = fopen(fileName, "r");
		char character;
		if (fp != NULL) {
			printf("FileOpen Success!!\n");
			do {
				character = getc(fp);
				printf("%c", character);
			} while (character != EOF);
			printf("\n");
			fclose(fp);
		}
	}

	void FileOpen_CppStyle(const char* fileName) {
		std::ifstream ifs;
		ifs.open(fileName);
		std::string line;

		if (ifs.is_open()) {
			std::cout << "FileOpen Success!!" << std::endl;

#pragma region Version1
			/*---------------------------------------
			//char character;
			while (true) {
				//ifs.get(character);
				std::getline(ifs, line);
				if (ifs.fail()) {
					break;
				}
				//std::cout << character;
				std::cout << line << std::endl;
			}
			//std::cout << std::endl;
			---------------------------------------*/
#pragma endregion
#pragma region Version2
			while (!ifs.eof()) {
				std::getline(ifs, line);
				std::cout << line << std::endl;
			}
#pragma endregion
			ifs.close();
		}
		
	}

	void FileWrite_CStyle(const char* fileName) {
		FILE* fp = fopen(fileName, "w");
		if (fp != NULL) {
			char line[512] = { 0, };
			if (fgets(line, 512, fp) != NULL) {
				fprintf(fp, "%s\n", line);
			}
			fclose(fp); fp = NULL;
		}
	}

	void FileWrite_CppStyle(const char* fileName) {
		std::ofstream ofs;
		ofs.open(fileName);
		std::string line = string_empty;
		if (ofs.is_open()) {
			std::getline(std::cin, line);
			if (!std::cin.fail()) {
				ofs << line << std::endl;
			}
			ofs.close();
		}
	}
}

int main(int argc, char* argv[])
{
	std::string FileName = "hello.txt";
	FileIO::FileWrite_CppStyle(FileName.c_str());
	FileIO::FileOpen_CppStyle(FileName.c_str());
	return 0;
}