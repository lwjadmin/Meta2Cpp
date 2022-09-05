#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace FileIO {

	struct TRecord {
		std::string StudentID;
		std::string StudentName;
		std::string Score;
	};

	TRecord ReadRecord(std::istream& ifs, bool bPrompt) {
		TRecord record;
		if (bPrompt) {
			std::cout << "StudentID : ";
		}
		ifs >> record.StudentID;
		if (bPrompt) {
			std::cout << "StudentName : ";
		}
		ifs >> record.StudentName;
		if (bPrompt) {
			std::cout << "Score : ";
		}
		ifs >> record.Score;
		ifs.clear();
		ifs.ignore(LLONG_MAX, '\n');
		return record;
	}
	void WriteFileRecord(std::fstream& ofs, const TRecord& record) {
		ofs.seekp(0, std::ios_base::end);
		ofs << record.StudentID << "," << record.StudentName << "," << record.Score << "\n";
		ofs.flush();
	}
	void DisplayRecord(std::fstream& fs) {
		fs.seekg(0);
		std::string line;
		while (true) {
			std::getline(fs, line);
			if (fs.eof()) {
				fs.clear();
				break;
			}
			std::cout << line << std::endl;
		}
	}
	void ManageRecordExample(const char* fileName) {
		std::fstream fs;
		fs.open(fileName, std::ios_base::in | std::ios_base::out);
		if (!fs.is_open()) {
			std::cout << "file : " << fileName << "Open Failed.." << std::endl;
			return;
		}

		bool bExitCalled = false;
		std::string command = "";
		char cmdinitial;
		while (!bExitCalled) {
			//system("cls");
			std::cout << "Append[A], Display[D], Exit[E] : ";
			std::getline(std::cin, command);
			cmdinitial = command.size() > 0 ? command[0] :'?';
			switch (cmdinitial)
			{
				case 'A':
				case 'a':
				{
					TRecord record = ReadRecord(std::cin, true);
					WriteFileRecord(fs, record);
					break;
				}
				case 'D':
				case 'd':
				{
					DisplayRecord(fs);
					break;
				}
				case 'E':
				case 'e': 
				{
					bExitCalled = true;
					fs.close();
					break;
				}
			}//eoswitch


		}//eowhile
	}//eofunc
}