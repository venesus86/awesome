#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstring>

using namespace std;

vector<string> tockenize_getline(const string &str, const char delim)
{
    stringstream ss{str};
    string partial_string;
    vector<string> result;
    while (getline(ss, partial_string, delim)) {
        result.push_back(partial_string);
    }
    return result;
}

vector<string> tockenize_strtok(const string &str, const char* delim)
{
    char *str_buff = new char[str.size() + 1];
    strcpy(str_buff, str.c_str());
    char *tok = strtok(str_buff, delim);
    vector<string> result;
    while (tok != nullptr) {
        result.push_back(tok);
        tok = strtok(nullptr, delim);
    }
    return result;
}

int main()
{
    string str{"this is test /test/string"};
    // clock_t start{clock()};
    // for (int count{}; count < 1000000; ++count)
    //     //tockenize_getline(str, ' ');
    //     tockenize_strtok(str, " /");
    // clock_t end{clock()};

    // cout << "time: " << end - start << " ms" << endl;
    //vector<string> parsed_string{tockenize_strtok(str, " /")};
    vector<string> parsed_string{tockenize_getline(str, ' ')};
     for (const auto &data : parsed_string)
         cout << data << endl;

    return 0;
}