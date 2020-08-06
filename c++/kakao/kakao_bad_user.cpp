/*
user_id                                         banned_id                               result
["frodo", "fradi", "crodo", "abc123", "frodoc"]	["fr*d*", "abc1**"]                     2
["frodo", "fradi", "crodo", "abc123", "frodoc"]	["*rodo", "*rodo", "******"]            2
["frodo", "fradi", "crodo", "abc123", "frodoc"]	["fr*d*", "*rodo", "******", "******"]	3
*/

#include <string>
#include <vector>
#include <set>
/* TODO: remove */
#include <iostream>
/****************/

using namespace std;

bool check_pattern(string check_str, string pattern)
{
    if (check_str.size() != pattern.size())
        return false;
    
    for (auto pattern_it{pattern.begin()}, check_str_it{check_str.begin()}; pattern_it != pattern.end(); ++pattern_it, ++check_str_it) {
        if (*pattern_it != *check_str_it && *pattern_it != '*')
            return false;
    }
    return true;
}

vector<vector<string>> get_banned_list(const vector<string> &user_id, const vector<string> &banned_id)
{
    vector<vector<string>> user_list_per_pattern;
    for (const auto &pattern : banned_id) {
        vector<string> user_list;
        for (const auto &user : user_id) {
            if (check_pattern(user, pattern))
                user_list.push_back(user);
        }
        user_list_per_pattern.push_back(user_list);
    }
    return user_list_per_pattern;
}

size_t get_count(vector<vector<string>>::size_type depth, const set<string> &previous_result, const vector<vector<string>> &user_list_per_pattern)
{
    static set<set<string>> banned_user_list{};
    if (depth == user_list_per_pattern.size()) {
        if (previous_result.size() == user_list_per_pattern.size())
            banned_user_list.insert(previous_result);
        return 0;
    }

    for (auto userlist_it{user_list_per_pattern[depth].begin()}; userlist_it != user_list_per_pattern[depth].end(); ++userlist_it) {
        set<string> current_result{previous_result};
        current_result.insert(*userlist_it);
        get_count(depth + 1, current_result, user_list_per_pattern);
    }
    return banned_user_list.size();
}

int solution(vector<string> user_id, vector<string> banned_id)
{
    int answer = 0;
    answer = get_count(0, set<string>{}, get_banned_list(user_id, banned_id));
    return answer;
}

int main()
{
    vector<string> user_id{"frodo", "fradi", "crodo", "abc123", "frodoc"};
    vector<string> banned_id{"fr*d*", "abc1**"};
    //vector<string> banned_id{"*rodo", "*rodo", "******"};
    //vector<string> banned_id{"fr*d*", "*rodo", "******", "******"};
    cout << "answer: " << solution(user_id, banned_id) << endl;

    return 0;
}