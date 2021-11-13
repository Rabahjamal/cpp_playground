#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <atomic>
#include <optional>
#include "templates.h"

using namespace std;

void normal_fun()
{
    cout << "I'm normal" << endl;
}

int koko(double x)
{
    return static_cast<int>(x);
}

int main()
{
    int a = absfun(-3);
    cout << a << endl;

    normal_fun();

    STM<int> s;
    cout << is_void_var<void> << endl;
    cout << is_same_v<myvec<float>, std::vector<float>> << endl;

    cout << "----------------------------------------------------------" << endl;

    f(2, 3);
    f(2.3, 4);

    g(2, 5);

    foo(std::array<int,8>{}, std::array<double,4>{}, 0.0);
    // foo(std::array<int,9>{}, std::array<double,4>{}, 0.0); error

    // foo2(  [](double x) { return int(x); } );   error
    foo2(  +[](double x) { return int(x); } );

    int (*fptr)(double);
    fptr = &koko;

    foo2(koko);
    add<int>();

    cout << "----------------------------------------------------------" << endl;

    int x = 27;
    const int cx = x;
    const int& rx = x;
    f(x);
    f(cx);
    f(rx);

    f2(x);  // T = int&
    f2(cx); // T = const int&
    f2(rx); // T = const int&
    const string& str = "ls";
    f2(str);
    f2(27); // T = int
    f2(move(x)); // T = int
    f2(move(cx)); // T = const int
    f2(move(rx)); // T = const int

    cout << "----------------------------------------------------------" << endl;

    int sum = adder(2, 4, 6, 10, 2);
    cout << sum << endl;

    cout << "----------------------------------------------------------" << endl;

    Vec<1, int> v1D(10);

    Vec<2, int> v2D(10, 50);

    Vec<3, double> v3D(4, 6, 2, 3.14);

    cout << v3D.size() << endl;

    std::vector <int> m (10, 0);

    cout << m.size() << endl;

    stringstream stream;
    write<int>(stream, 16);


}
