#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <future>

void TestFuture()
{
    //通过async来获取异步操作结果
    std::future<int>  result = std::async([](){ 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return 8; 
    });

    std::cout << "the future status : " << result.valid() << std::endl;
    std::cout << "the future result : " << result.get() << std::endl;
    try
    {
        result.wait();  //或者 result.get() ,会异常
    //因此std::future只能用于单线程中调用 ，多线程调用使用std::share_future();
    }
    catch (...)
    {
        std::cout << "get error....\n ";
    }

}


int main()
{
    TestFuture();
    return 0;
}