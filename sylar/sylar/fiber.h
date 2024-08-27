#pragma once
//协程调度器封装

#include <memory>
#include <functional>
#include <ucontext.h>

namespace sylar
{
    class Scheduler;

    /**
     * @brief 协程类
     */
    class Fiber : public std::enable_shared_from_this<Fiber> 
    {
        friend class Scheduler;
        public:
        typedef std::shared_ptr<Fiber> ptr;

        //协程状态
        enum State
        {
            INIT,   //初始化状态
            HOLD,   //暂停状态
            EXEC,   //执行中状态
            TERM,   //结束状态
            READY,  //可执行状态
            EXCEPT  //异常状态
        };

        private:
        //每个线程第一个协程的构造，无参构造
        Fiber();

        public:
        Fiber(std::function<void()> cb, size_t stacksize = 0, bool use_caller = false);

        ~Fiber();

        
    };
}