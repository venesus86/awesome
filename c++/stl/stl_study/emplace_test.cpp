#include <iostream>
#include <vector>

using namespace std;

class Point
{
public:
    int x, y;
public:
    Point(int a, int b) : x(a), y(b) { cout << "Point()" << endl; }
    ~Point() { cout << "~Point()" << endl; }
    Point(const Point& p) : x(p.x), y(p.y) { cout << "Point(const Point&)" << endl; }
};

int main()
{
    vector<Point> v;

    // Point p(10, 20);
    // v.push_back(p);
    v.emplace_back(10, 20);

    for (const auto &p : v)
        cout << "p.x: " << p.x << ", p.y: " << p.y << endl;

    cout << "------------------" << endl;
}