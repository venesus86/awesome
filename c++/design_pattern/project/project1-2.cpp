/*
 변하는 것에 해당 하는 “이전 결과를 바탕으로 사용자가 생각한 숫자를 예측하는 부분”을
교체 가능한 설계로 변경해 보세요. 즉, BaseBallGame 클래스가 변하지 않고도 알고리즘을 교체 할 수
있도록 변하는 것을 다른 클래스로 분리한 후, 인터페이스 기반으로 교체 가능한 설계(strategy)로 만들어
보세요.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <tuple>

using namespace std;

struct IPredictionNumber
{
    typedef tuple<int, int, int> INPUT;
    typedef tuple<int, int> RESULT;
    virtual void findNumber(int *n1, int *n2, int *n3, const vector<pair<INPUT, RESULT>> &v) = 0;
    virtual ~IPredictionNumber() {}
};

class BaseBallGame
{
    typedef tuple<int, int, int> INPUT;
    typedef tuple<int, int> RESULT;
    vector<pair<INPUT, RESULT>> v;
    IPredictionNumber *pn = 0;

public:
    BaseBallGame() { srand((unsigned)time(0)); }
    void setPredictionNumber(IPredictionNumber *p) { pn = p; }
    void run()
    {
        while (1)
        {
            int x = 0, y = 0, z = 0;
            if ( pn ) {
                pn->findNumber(&x, &y, &z, v);
            } else {
                do {
                    x = rand() % 9 + 1;
                    y = rand() % 9 + 1;
                    z = rand() % 9 + 1;
                } while (x == y || y == z || x == z);
            }
            cout << "당신이 생각한 숫자는 " << x
                 << ", " << y << ", " << z << " 입니까 ?" << endl;
            int strike = 0, ball = 0;
            cout << "strike 갯수 : ";
            cin >> strike;
            if (strike == 3)
            {
                cout << "성공 !" << endl;
                break;
            }
            cout << "ball 갯수 : ";
            cin >> ball;
            //--------------------------------------
            // 입력된 결과(strike, ball)을 기록해 두었다가
            // 다음수를 예측할때 사용합니다.
            v.push_back(make_pair(INPUT(x, y, z), RESULT(strike, ball)));
            dump();
        }
    }
    // 필요하신 분을 위해 참고용으로 만든 함수입니다.
    void dump()
    {
        printf("-------------------------------\n");
        printf("입력값 s b\n");
        for (auto &p : v) // p는 pair<INPUT, RESULT> 입니다.
        {
            printf(" %d %d %d : %d %d\n",
                   get<0>(p.first), get<1>(p.first), get<2>(p.first),
                   get<0>(p.second), get<1>(p.second));
        }
        printf("-------------------------------\n");
    }
};

class PredictionNumber : public IPredictionNumber
{
public:
    virtual void findNumber(int *n1, int *n2, int *n3, const vector<pair<INPUT, RESULT>> &v) override
    {
        // 현재까지 입력된 결과 'v'를 이용하여 findNumber 구현
        cout << "this is PredictionNumber class" << endl;
        do {
            *n1 = rand() % 9 + 1;
            *n2 = rand() % 9 + 1;
            *n3 = rand() % 9 + 1;
        } while (*n1 == *n2 || *n2 == *n3 || *n1 == *n3);
    }
};

int main(void)
{
    BaseBallGame bbg;
    PredictionNumber pn;
    bbg.setPredictionNumber(&pn);
    bbg.run();
}