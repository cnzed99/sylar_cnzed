#pragma once

namespace sylar
{
    /**
     * @brief 对象无法拷贝,赋值
     */
    class Noncopyable
    {
    public:
        Noncopyable() = default;
        ~Noncopyable() = default;

        //拷贝构造函数(禁用)
        Noncopyable(const Noncopyable&) = delete;
        // 赋值函数(禁用)
        Noncopyable& operator=(const Noncopyable&) = delete;
    };
}