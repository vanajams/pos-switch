#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <type_traits>

class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount);
    ~ThreadPool();

    // Submit task with return value support
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) 
        -> std::future<typename std::invoke_result<F, Args...>::type>;

    void shutdown();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

template<typename F, typename... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result<F, Args...>::type>
{
    using ReturnType =
        typename std::invoke_result<F, Args...>::type;

    auto task =
        std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(
                std::forward<F>(f),
                std::forward<Args>(args)...)
        );

    std::future<ReturnType> result =
        task->get_future();

    {
        std::lock_guard<std::mutex> lock(queueMutex);

        if (stop.load()) {
            throw std::runtime_error(
                "ThreadPool stopped");
        }

        tasks.emplace([task]() {
            (*task)();
        });
    }

    condition.notify_one();

    return result;
}