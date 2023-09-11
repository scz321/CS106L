#ifndef kwc


#define kwc 



#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
using namespace std;

/* Function: OpenUserFile(ifstream& fileStream);
* Usage: OpenUserFile(myStream);
* -------------------------------------------------
* Prompts the user for a filename until a valid filename
* is entered, then sets fileStream to read from that file.
*/
void OpenUserFile(ifstream& fileStream);
/* Function: GetFileContents(ifstream& file);
* Usage: string contents = GetFileContents(ifstream& file);
* -------------------------------------------------
* Returns a string containing the contents of the file passed
* in as a parameter.
*/
string GetFileContents(ifstream& file);
/* Function: GenerateKeywordReport(string text);
* Usage: map<string, size_t> keywords = GenerateKeywordReport(contents);
* -------------------------------------------------
* Returns a map from keywords to the frequency at which those keywords
* appear in the input text string. Keywords not contained in the text will
* not appear in the map.
*/
map<string, size_t> GenerateKeywordReport(string contents);

set<string> targetKeys;

void loadKeys() {
	ifstream input("keyWords.txt");
	string key;
	while (input >> key) {//input ���fail״̬�������Ƕ����ļ����ո�ͻ���ֻ�ᵼ���ж�
		targetKeys.insert(key);
	}
	return;
}

void keyWordsCount() {
	loadKeys();
	/*for (set<string>::iterator itr = targetKeys.begin(); itr != targetKeys.end(); ++itr) {
		cout << *itr << endl;
	}*/

	/* Prompt the user for a valid file and open it as a stream. */
	ifstream input;
	OpenUserFile(input);
	/* Generate the report based on the contents of the file. */

	map<string, size_t> report = GenerateKeywordReport(GetFileContents(input));

	/* Print a summary. */
	for (map<string, size_t>::iterator itr = report.begin();
		itr != report.end(); ++itr)
		cout << "Keyword " << itr->first << " occurred "
		<< itr->second << " times." << endl;
}



void OpenUserFile(ifstream& fileStream) {

	//���Ȱ�Ŀ���ļ����������ݶ�ȡ��fileStream��
	cout << "������ͬ��Ŀ¼�µ��ļ����ƣ�����׺��";
	string fName;

	cin >> fName;
	fileStream.open(fName);

	if (!fileStream.is_open())
		cerr << "open error!" << endl;
	return;




}

string GetFileContents(ifstream& file) {
	string temp_line;
	string ret;
	while (!getline(file, temp_line).fail()) {
		ret = ret + temp_line + '\n';
	}
	//�Ѳ���ͨ��------cout << "ת�����string��" << ret << endl;
	return ret;

}


map<string, size_t> GenerateKeywordReport(string contents) {

	//���ȣ���string�е����б��ĳɿո�
	for (int i = 0; i < contents.length(); i++) {
		if (ispunct(static_cast<unsigned char>(contents[i]))) {
			contents[i] = ' ';
		}
	}
	map<string, size_t> ret;
	stringstream ioStream;

	ioStream << contents;
	string temp_word;

	while (ioStream >> temp_word) {
		if (targetKeys.count(temp_word)) {
			ret[temp_word]++;
		}
	}

	return ret;



}

#endif // !kwc