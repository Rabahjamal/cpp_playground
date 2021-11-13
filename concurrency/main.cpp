#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <atomic>
#include <optional>
#include <mutex>

using namespace std;

void thread_safe_std_thread()
{
    int res = 0;
    std::thread threadB([&]() {
        cout << "hello from threadB" << endl;
        res++;
        res++;
    });

    threadB.join();
    res++;
    cout << "hello from threadA" << endl;
    cout << "result = " << res << endl;
}

void data_race_with_std_thread()
{
    int res2 = 0;
    std::thread threadB([&]() {
        cout << "hello from threadB" << endl;
        res2++;
        res2++;
    });
    res2++;
    cout << "hello from threadA" << endl;

    threadB.join();
    cout << "result = " << res2 << endl;
}

void use_atomic_1()
{
    int deadline = 10;
    atomic<int> counter = 0;
    std::thread threadB = std::thread([&](){
        for(int i = 0; i < deadline; i++)
            cout << "B: " << ++counter << endl;;
    });
    for(int i = 0; i < deadline; i++)
        cout << "A: " << ++counter << endl;
    threadB.join();

    cout << "Final result of counter = " << counter << endl;
}

void busy_wait()
{
    std::atomic<bool> ready = false;
    std::thread threadB = std::thread([&](){
        while (!ready) { }
        cout << "Hello from B\n";
    });
    cout << "Hello from A\n";
    ready = true;

    threadB.join();
    cout << "Hello again from A\n";
}

struct Token
{
    size_t id;
    string key;
};

class TokenPool {
    std::mutex mtx_;
    std::vector<Token> tokens_;
public:
    void add_token(const Token& t)
    {
        tokens_.push_back(t);
    }
    Token getToken() {
        std::lock_guard lk(mtx_);
        //this_thread::sleep_for(chrono::nanoseconds(5));
        if (tokens_.empty())
            tokens_.push_back(Token{1, "f34nlof3"});
        Token t = std::move(tokens_.back());
        tokens_.pop_back();
        return t;
    }

    size_t numTokensAvailable() {
        std::lock_guard lk(mtx_);
        return tokens_.size();
    }
};

void access_token_pool()
{
    TokenPool t;
    t.add_token(Token{1, "mf3p423"});
    t.add_token(Token{2, "lso2hqw"});
    t.add_token(Token{3, "pwg14ls"});
    t.add_token(Token{4, "hafm03l"});
    t.add_token(Token{5, "v3p4wtl"});

    std::thread threadB = std::thread([&](){
        cout << t.numTokensAvailable() << endl;
        cout << "ThreadB" << endl;
    });

    cout << "ThreadA" << endl;
    t.getToken();
    threadB.join();
}

struct Employee {
    Employee(std::string id) : id(id) {}
    std::string id;
    std::vector<std::string> lunch_partners;
    std::mutex m;
    std::string output() const
    {
        std::string ret = "Employee " + id + " has lunch partners: ";
        for( const auto& partner : lunch_partners )
            ret += partner + " ";
        return ret;
    }
};

void send_mail(Employee &, Employee &)
{
    // simulate a time-consuming messaging operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void assign_lunch_partner(Employee &e1, Employee &e2)
{
    static std::mutex io_mutex;
    {
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
    }

    {
        // use std::scoped_lock to acquire two locks without worrying about
        // other calls to assign_lunch_partner deadlocking us
        // and it also provides a convenient RAII-style mechanism

        std::scoped_lock lock(e1.m, e2.m);

        // Equivalent code 1 (using std::lock and std::lock_guard)
         //std::lock(e1.m, e2.m);
         //std::lock_guard<std::mutex> lk1(e1.m);
         //std::lock_guard<std::mutex> lk2(e2.m);

        // Equivalent code 2 (if unique_locks are needed, e.g. for condition variables)
        // std::unique_lock<std::mutex> lk1(e1.m, std::defer_lock);
        // std::unique_lock<std::mutex> lk2(e2.m, std::defer_lock);
        // std::lock(lk1, lk2);
        {
            std::lock_guard<std::mutex> lk(io_mutex);
            std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;
        }
        e1.lunch_partners.push_back(e2.id);
        e2.lunch_partners.push_back(e1.id);
    }

    send_mail(e1, e2);
    send_mail(e2, e1);
}

void employees_example()
{
    Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");

    // assign in parallel threads because mailing users about lunch assignments
    // takes a long time
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));

    for (auto &thread : threads) thread.join();
    std::cout << alice.output() << '\n'  << bob.output() << '\n'
              << christina.output() << '\n' << dave.output() << '\n';
}

void foo(int num)
{
    cout << this_thread::get_id() << ": " << num << endl;

    if(num == 3)
    {
        cout << "num = 3, so this thread will sleep" << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }

    if(num > 10)
    {
        throw std::runtime_error("num is greater than 10");
    }

}

void print_msg(const string& msg)
{
    cout << msg << endl;
}

void test_lambda_fun(std::thread& thread, const string& msg, string& out)
{
    cout << "address of msg in test_lambda_fun: " << &msg << endl;
    cout << "address of  out in test_lambda_fun: " << &out << endl;
    thread = std::thread([&]{
        cout << "start executing inside lambda function" << endl;
        print_msg(msg);
        out = "result of lambda function";
        cout << "address of msg in lambda: " << &msg << endl;
        cout << "address of out in lambda: " << &out << endl;
    });
}

int main()
{
   //thread_safe_std_thread();

    cout << "---------------------------------------------------" << endl;

   //data_race_with_std_thread();

    cout << "---------------------------------------------------" << endl;
    //use_atomic_1();

    //busy_wait();


    //access_token_pool();

    //employees_example();

    /*vector<thread> v;
    try {
        v.push_back(thread(foo, 12));
        v.push_back(thread(foo, 3));
//        thread t1(foo, 12);
//        thread t2(foo, 3);
    }  catch (...) {
        for(auto& i : v)
        {
            i.join();
        }
    }

    for(auto& i : v)
    {
        i.join();
    }*/

    ///////// test lambda
    std::thread thread;
    string msg = "this is the message to lambda function";
    string out;
    test_lambda_fun(thread, msg+"message to lambda function", out);
    cout << "main fun" << endl;

    thread.join();

    cout << "address of msg in main: " << &msg << endl;
    cout << "address of out in main: " << &out << endl;
    cout << out << endl;
}
