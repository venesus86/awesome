#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <set>
#include <vector>
#include <thread>

using namespace std;
using namespace std::placeholders;

const bool NEW_THREAD = true;

struct NotificationInfo
{
    using HANDLER = function<void(void*)>;

	int priority;
	HANDLER handler;
	bool use_thread;

public:
	NotificationInfo(HANDLER h = nullptr, int p = -1, bool t = false) : handler(h), priority(p), use_thread(t) {}
	NotificationInfo(const NotificationInfo &n) : handler(n.handler), priority(n.priority), use_thread(n.use_thread) {}
};

struct PriorityGreater
{
	bool operator()(const NotificationInfo &n1, const NotificationInfo &n2)
	{
		return n1.priority > n2.priority;
	}
};

class NotificationCenter
{
    map<string, set<NotificationInfo, PriorityGreater>> notify_map;
public:
    void Register(string key, NotificationInfo::HANDLER h, int priority, bool use_thread = false)
    {
        notify_map[key].insert(NotificationInfo(h, priority, use_thread));
	}

    void Notify(string key, void* param)
    {
        auto noti_info_it = notify_map.find(key);
        if (noti_info_it == notify_map.end())
            return;

        for(auto noti_info : noti_info_it->second) {
            if (noti_info.use_thread) {
                thread t(noti_info.handler, param);
                t.detach();
            } else {
                noti_info.handler(param);
            }
        }
    }
};

void foo(void* p, string name)
{
    cout << name << " : " << this_thread::get_id() << endl;
    this_thread::sleep_for(3s);
    cout << name << " end" << endl;
}

int main()
{
    NotificationCenter nc;
    nc.Register("TEST_EVENT", bind(&foo, _1, "one"s), 1);
    nc.Register("TEST_EVENT", bind(&foo, _1, "two"s), 2, NEW_THREAD);
    nc.Register("TEST_EVENT", bind(&foo, _1, "three"s), 3);

    nc.Notify("TEST_EVENT", (void*)0);
    getchar();

    return 0;
}