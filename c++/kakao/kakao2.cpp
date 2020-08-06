#include <string>
#include <vector>
#include <list>
#include <cstring>

/* remove */
#include <iostream>
/* remove */

using namespace std;

/* 
long long max_num = 0;
case 1 : - > *
string[] str = {"50", "6" "3" "2"}
int[] num {50,6 3 2}
string[6] oper = {  "*" "-" "+" }
-> 50 3 2
if (abs(result) > max_num)
max_num = abs(result);
case 2 : * > -
num[oper_idx] = num[oper_idx] - num[oper_idx+1];
erase num[oper_idx+1];
string[] str = {"50", "*", "6" "-", "3" "*" "2"}
{"50", "*", "3" "*" "2"}
{"150" "*" "2"}
{"300"}

"100-200*300-500+20"	60420
"50*6-3*2"	300
*/

vector<string> tockenize(const string &str, const char* delim)
{
    char *str_buff = new char[str.size() + 1];
    strcpy(str_buff, str.c_str());
    char *tok = strtok(str_buff, delim);
    int pos = strlen(tok);
    vector<string> result;
    result.push_back(str.substr(pos++, 1));
    result.push_back(tok);
    while ((tok = strtok(nullptr, delim)) != nullptr) {
        result.push_back(tok);
        pos += strlen(tok);
        result[0] += str.substr(pos++, 1);
    }
    return result;
}

long long calc(char oper, long long num1, long long num2)
{
    if (oper == '*')
        return num1 * num2;
    else if (oper == '-')
        return num1 - num2;
    else
        return num1 + num2;
}

long long solution(string expression) {
    long long answer = 0;
    vector<string> data_list = tockenize(expression, "*+-");
    vector<long long> number_list;
    string priority_array[] = {"*+-", "*-+", "+*-", "+-*", "-*+", "-+*"};
    //string priority_array[] = {"-*+"};
    for (auto iter = data_list.begin() + 1; iter != data_list.end(); ++iter)
        number_list.push_back(stoll(*iter));

    long long max_value = 0;
    for (int pri_array_idx = 0; pri_array_idx < 6; ++pri_array_idx) {
        vector<long long> number_list_copy = number_list;
        string priority = priority_array[pri_array_idx];
        string oper_list = data_list[0];
        for (int pri_idx = 0; pri_idx < 3; ++pri_idx) {
            int num_idx = 0;
            while ((num_idx = oper_list.find(priority[pri_idx])) != string::npos) {
                number_list_copy[num_idx] = calc(oper_list[num_idx], number_list_copy[num_idx], number_list_copy[num_idx + 1]);
                oper_list.erase(num_idx, 1);
                number_list_copy.erase(number_list_copy.begin() + num_idx + 1);
            }
        }
        if (abs(number_list_copy[0]) > answer)
            answer = abs(number_list_copy[0]);
    }
    return answer;
}

int main()
{
    string expression{"100-200*300-500+20"};
    //string expression{"50*6-3*2"};
    long long result{solution(expression)};
    cout << "result: " << result << endl;
    return 0;
}