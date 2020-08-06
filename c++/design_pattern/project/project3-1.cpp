/*
 1. 클래스 어답터로 만들어 보세요
*/

#include <iostream>
#include <list>

using namespace std;

template<typename DataType, typename Container = list<DataType>>
class Queue
{
    Container c;
public:
    void Push(const DataType &d)
    {
        c.push_back(d);
    }

    DataType Pop()
    {
        DataType d = c.front();
        c.pop_front();
        return d;
    }
};

int main()
{
    Queue<int> q;
    q.Push(10);
    q.Push(20);
    cout << q.Pop() << endl; // 10
    cout << q.Pop() << endl; // 20
}