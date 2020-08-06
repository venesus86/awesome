#include <iostream>

using namespace std;

template <typename InputIter, typename OutputIter, typename UnaryFunc>
OutputIter xcopy_if(InputIter in_first, InputIter in_last, OutputIter out_first, UnaryFunc func)
{
    for (; in_first != in_last; ++in_first) {
        if (func(*in_first)) {
            *out_first = *in_first;
            ++out_first;
        }
    }
    return out_first;
}

int main()
{
    int x[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int y[10] = { 0 };
    xcopy_if(x, x + 10, y, [](int a) { return a % 2 == 0; });
    for (auto n : y)
        cout << n << endl;
    
    return 0;
}
// 출력 결과 : 2, 4, 6, 8, 10, 0,0,0,0,0