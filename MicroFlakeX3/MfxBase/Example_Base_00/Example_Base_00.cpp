#include <iostream>
#include "MfxBase.h"
using namespace MicroFlakeX;
using namespace std;

/*********************************************************
*	UTF-8 - win - x86
*
*   版本：1.01       作者：yishengjun8
*
*   这个示例展示了如何使用MfxBase及其组件
*********************************************************/

class point
{
public:
    int a = 10;
    point(const point& rhs)
    {
        cout << "point copy " << endl;
    }

    point(int a)
    {
        this->a = a;
        cout << "point Creat" << endl;
    }

    void say()
    {
        cout << "point say hello" << endl;
    }
};



void func(MfxParam mpParam)
{
    cout << GetParam(mpParam, point, 0).a << endl;

    mpParam.push_back(500);
}


int main()
{
    cout << endl;
    MfxParam mpParam;

    point tem(10);

    mpParam.push_back(tem);

    func(mpParam);

    cout << GetParam(mpParam, int, 1) << endl;


    return 0;
}
