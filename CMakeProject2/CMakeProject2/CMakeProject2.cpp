// CMakeProject2.cpp: определяет точку входа для приложения.
//

#include "CMakeProject2.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc > 1) {
		string str = argv[1];
		int num = stoi(str);
		if(str.size() >2 && (num %32 ==0))
			cout << "Program second finish successfully" << endl;
		else
			cout << "Program second finish error" << endl;
	}

	return 0;
}

