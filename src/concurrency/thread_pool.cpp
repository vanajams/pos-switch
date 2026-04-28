#include "concurrency/thread_pool.h"
#include<mutex>

ThreadPool::ThreadPool(size_t threadCount) : stop(false) {
    for (size_t i = 0; i < threadCount; ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(queueMutex);

                    condition.wait(lock, [this]() {
                        return stop.load() || !tasks.empty();
                    });

                    if (stop.load() && tasks.empty())
                        return;

                    task = std::move(tasks.front());
                    tasks.pop();
                }

                try {
                    task();
                } catch (...) {
                    // Prevent thread crash
                }
            }
        });
    }
}

template<typename F, typename... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result<F, Args...>::type>
{
    using ReturnType = typename std::invoke_result<F, Args...>::type;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<ReturnType> result = task->get_future();

    {
        std::lock_guard<std::mutex> lock(queueMutex);

        if (stop.load()) {
            throw std::runtime_error("ThreadPool is stopped");
        }

        tasks.emplace([task]() {
            (*task)();
        });
    }

    condition.notify_one();
    return result;
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::shutdown() {
    stop.store(true);
    condition.notify_all();

    for (auto& worker : workers) {
        if (worker.joinable())
            worker.join();
    }
}