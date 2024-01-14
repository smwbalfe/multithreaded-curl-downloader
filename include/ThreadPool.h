//
// Created by shriller44 on 8/31/22.
//


#ifndef DOWNLOADTEST_THREADPOOL_H
#define DOWNLOADTEST_THREADPOOL_H

#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <future>

class ThreadPool{
 public:
  using Task = std::function<void()>;

  explicit ThreadPool(std::size_t numThreads);

  ~ThreadPool();

  template<class T>
  auto enqueue(T task) -> std::future<decltype(task())> {
    auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));
    {
      std::unique_lock<std::mutex> lock{ eventMutex_ };
      tasks_.emplace([=] {
        (*wrapper)();
      });
    }

    /* task has been added therefore notify a thread in the thread pool to
     *
     * check the wait condition again to proceed with task execution.
     * */

    eventVar_.notify_one();
    return wrapper->get_future();

  }

 private:

  std::vector<std::thread> threads_;
  std::condition_variable eventVar_;
  std::mutex eventMutex_;
  bool stopping_{ false };
  std::queue<Task> tasks_;
  void start(std::size_t numThreads);
  void stop() noexcept;
};


#endif  // DOWNLOADTEST_THREADPOOL_H
