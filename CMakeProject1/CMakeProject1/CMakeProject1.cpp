// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"

using namespace std;
string filePath = "Buffer12-.12.txt";
string secondProgPath;

std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

void ReadBuffer() {
	string str;
	ifstream file;
	file.open(filePath);
	int num=0;
	if (file.is_open()) {
		file >> str;
		file.close();
		remove(filePath.c_str());
		cout << str << endl;
		for (int i = 0; i < str.size(); i++) 
			if (str[i] >= '0' && str[i] <= '9') 
				num += (int)(str[i]-'0');

		string path = secondProgPath + " " + to_string(num);
		if(system(path.c_str()) != 0)
			cout << "Error executing the second program, check if the second program is compiled" << std::endl;

		cout << "Sum of numbers " << num  << std::endl;
	}
	else {
		file.close();
		cout << "File  " + filePath + " no find" << std::endl;
	}
}

int main()
{
	{
		string path = GetExePath();
		for(int i=0;i<5;i++)
			path = path.substr(0, path.find_last_of("\\/"));
		path += "\\CMakeProject2\\out\\build\\x64-Debug\\CMakeProject2\\CMakeProject2.exe";
		secondProgPath = path;
	}

	cout << "Start system" << endl;
	while(true){
		string sortStr = "", str;
		while (sortStr.size() == 0)
		{
			//cout << "Load numbers" << endl;
			//sortStr = "";
			cin >> str;
			if (str.size() > 64)
				cout << "Word length > 64" << endl;
			else {
				map <char, int> mp;
				for (int i = 0; i < str.size(); i++)
					if (str[i] >= '0' && str[i] <= '9') {
					auto search = mp.find(str[i]);
					if (search != mp.end())
						search->second++;
					else
						mp[str[i]]++;
				}
				else {
					mp.clear();
					cout << str[i] << " no number" << endl;
					break;
				}

				if (mp.size() > 0) {
					str = "";
					for (int i = 9; i >= 0; i--) {
						auto search = mp.find('0'+char(i));
						if (search != mp.end()) 
							for (int j = 0; j < search->second; j++)
								str += to_string(i);
					}
				}
				for (int i = 0; i < str.size(); i++)
						if ((i+1) % 2 == 0)
							sortStr += "КВ";
						else
							sortStr.push_back(str[i]);
			}
		}
	//	cout << sortStr << endl;


		ofstream file;
		file.open(filePath, ofstream::out | ofstream::trunc);
		file << sortStr;

		bool openFile = file.is_open();
		file.close();
		if (!openFile)
			cout << "Buffer file saving error" << endl;
		else {
			thread thr(ReadBuffer);
			thr.detach();
		}
		sortStr = "";
	}


	return 0;
}
