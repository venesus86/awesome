#include <vector>
#include <list>
#include <iterator>
#include <iostream>
#include <type_traits>
#include <algorithm>

using namespace std;
# if 1
template <typename T>
typename enable_if<is_same<typename T::iterator_category, random_access_iterator_tag>::value>::type
eadvance(T& p, int n)
{
    cout << "random_access_iterator_tag" << endl;
    p = p + n;
}

template <typename T>
typename enable_if<! is_same<typename T::iterator_category, random_access_iterator_tag>::value>::type
eadvance(T& p, int n)
{
    cout << "not random_access_iterator_tag" << endl;
    while(n--)
        ++p;
}
#else

template <typename T>
void eadvance(T& p, int n)
{
    if constexpr (is_same<typename T::iterator_category, random_access_iterator_tag>::value) {
        cout << "random_access_iterator_tag" << endl;
        p = p + n;
    } else {
        cout << "not random_access_iterator_tag" << endl;
        while (n--) ++p;
    }
}
#endif
int main()
{
    vector<int> v{1,2,3,4,5};
    list<int> l{10,20,30,40,50};

    vector<int>::iterator v_it = begin(v);
    list<int>::iterator l_it = begin(l);    

    eadvance(v_it, 3);
    cout << "*v_it: " << *v_it << endl;
    cout << "--------------------------------" << endl;
    eadvance(l_it, 3);
    cout << "*l_it: " << *l_it << endl;

    return 0;
}