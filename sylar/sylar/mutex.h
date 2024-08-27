#pragma once

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <atomic>
#include <list>

#include "noncopyable.h"
#include "fiber.h"

namespace sylar
{
    /**
     * @brief 信号量
     */
    class Semaphore : Noncopyable
    {

    };
}