#include "cplusplus.h"
using namespace std; // 只影响本文件，源文件里图方便可以写，但尽量写在 .cpp 最顶部，不要放进头文件

int main()
{
    // std::cout << "Hello World!-GuoPeng\n";
    // double i = 100/3;//33,隐式类型转换
    // int i = 100 / 3.0;
    // cout<<"i="<<i<<endl;
    // int i = static_cast<int>(100 / 3.0);//static_cast<int>强制类型转换 截断小数位置的作用
    // cout << i << endl;

    bool isGoodJob = true;
    cout << isGoodJob << endl;

    int myAge = 18;
    cout << myAge << endl;

    double pi = 3.14159;
    cout << pi << endl;

    long long i = 123456789123456789;
    cout << i << endl;

    char c = 'c';
    cout << c << endl;

    return 0;
}
