// ("kim", 10), ("lee", 15), ("park", 5), ("jung", 20), ("choi", 12) 를 v에 넣어주세요.
// 이름순으로 정렬해서 출력해 보세요
// 나이순으로 정렬해서 출력해 보세요.

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct People
{
    string name;
    int age;
    People(string n, int a) : name(n), age(a) {}
    void Dump() const { cout << name << "(" << age << ")" << endl; }
};

int main()
{
    vector<shared_ptr<People>> v;
    v.emplace_back(make_shared<People>("kim", 10));
    v.emplace_back(make_shared<People>("lee", 15));
    v.emplace_back(make_shared<People>("park", 5));
    v.emplace_back(make_shared<People>("jung", 20));
    v.emplace_back(make_shared<People>("choi", 12));

    cout << "line up by age (ascending)" << endl;
    sort(begin(v), end(v), [](const shared_ptr<People> &sp1, const shared_ptr<People> &sp2)
                            { return sp1->age < sp2->age; });
    for (const auto &sp : v)
        cout << sp->name << ", " << sp->age << endl;

    cout << "---------------------------" << endl;
    cout << "line up by name (ascending)" << endl;
    sort(begin(v), end(v), [](const shared_ptr<People> &sp1, const shared_ptr<People> &sp2)
                            { return sp1->name < sp2->name; });
    for (const auto &sp : v)
        cout << sp->name << ", " << sp->age << endl;

    return 0;
}