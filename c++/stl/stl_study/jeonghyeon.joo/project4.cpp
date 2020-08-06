/*
   과제 4. 전처리기 만들기
   “preprocessor” 라는 실행파일을 만드세요.
   input.txt 파일이 아래와 같을 때
   preprocessor input.txt result.txt
   처럼 실행 하면 다음과 같은 result.txt 가 생성되어야 합니다.
   unordered_map 을 사용해 주세요.
   과제 제출시 실행파일이 아닌 preprocessor 의 소스를 제출하시면 됩니다.
 */

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "invalid argument" << endl;
		cout << "uasge: preprocessor [input file] [output file]" << endl;
		return 1;
	}

	ifstream ifs(argv[1]);
	ofstream ofs(argv[2]);
	unordered_map<string, string> preprocessor_map;
	string contents;
	while (getline(ifs, contents)) {
		if (contents.empty()) {
			continue;
		} else if (contents.find("define") != string::npos) {
			istringstream iss(contents);
			string as_is_str;
			iss >> as_is_str; // define
			iss >> as_is_str; // as-is string
			string to_be_str;
			iss >> to_be_str; // to-be string
			preprocessor_map.insert(make_pair(as_is_str, to_be_str));
		} else {
			for (auto pre_it = begin(preprocessor_map); pre_it != end(preprocessor_map); ++pre_it) {
				size_t str_idx;
				while ((str_idx = contents.find(pre_it->first)) != string::npos)
					contents.replace(str_idx, pre_it->first.size(), pre_it->second);
			}
			ofs << contents << endl;
		}
	}

	return 0;
}