/*
["DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"]	[3, 7]
["AA", "AB", "AC", "AA", "AC"]	[1, 3]
["AA", "AB", "AA", "AB", "AC", "AA", "AB", "AC"]	[1, 3]
["XYZ", "XYZ", "XYZ"]	[1, 1]
["ZZZ", "YYY", "NNNN", "YYY", "BBB"]	[1, 5]
*/
#include <string>
#include <vector>
#include <set>

/* remove */
#include <iostream>
/* remove */

using namespace std; 

set<string> get_all_gems_type(const vector<string> &gems)
{
    set<string> result;
    for (const auto &gem : gems)
        result.insert(gem);

    return result;
}

vector<int> get_answer(const vector<string> &gems, const set<string> &all_gems_type)
{
    int min_count = all_gems_type.size() + 1;
    // int min_count = gems.size() + 1;
    vector<int> gem_pos(2, 0);
    for (int gems_idx = 0; gems_idx < gems.size(); ++gems_idx) {
        set<string> copied_all_gems_type{all_gems_type};
        int count = 0;
        for (int start_idx = gems_idx; start_idx < gems.size(); ++start_idx, ++count) {
            cout << "gems[" << start_idx << "]: " << gems[start_idx] << endl;
            copied_all_gems_type.erase(gems[start_idx]);
            if (copied_all_gems_type.empty())
                break;
        }
        cout << "copied_all_gems_type.empty(): " << copied_all_gems_type.empty() << ", count: " << count << ", min_count: " << min_count << endl;
        if (copied_all_gems_type.empty() && count < min_count) {
            min_count = count;
            gem_pos[0] = gems_idx + 1;
            gem_pos[1] = gem_pos[0] + count;
        }
    }
    return gem_pos;
}

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    set<string> all_gems_type = get_all_gems_type(gems);
    answer = get_answer(gems, all_gems_type);
    return answer;
}

int main()
{
    //vector<string> gems{"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"};
    vector<string> gems{"AA", "AB", "AC", "AC", "AD", "AC", "AE"};
    //vector<string> gems{"AE", "AA", "AA", "AD", "AD", "AB", "AB", "AB", "AD", "AC", "AC", "AB", "AA", "AA", "AB", "AC", "AC", "AA", "AD", "TTTTTT"};
    //vector<string> gems{"ZZZ", "YYY", "NNNN", "YYY", "BBB"};
    vector<int> result{solution(gems)};
    for (const auto &data : result)
        cout << "data: " << data << endl;
    return 0;
}