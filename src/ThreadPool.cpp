//
// Created by shriller44 on 8/31/22.
//

#include <ThreadPool.h>


ThreadPool::ThreadPool(std::size_t numThreads) {
  start(numThreads);
}

ThreadPool::~ThreadPool() {
  stop();
}

void ThreadPool::start(std::size_t numThreads) {
  for (auto i =  0U ; i < numThreads; ++i) {
    threads_.emplace_back([=]{
      while (true) {
        Task task;
        {
          std::unique_lock<std::mutex> lock{ eventMutex_ };

          /* lock has been acquired
           *
           * condition variable predicate must return true to proceed otherwise the lock is released.
           * */
          eventVar_.wait(lock, [=] {return stopping_ || !tasks_.empty(); });

          /* break out of the function only if the threads is stopping and there are no tasks.*/
          if (stopping_ && tasks_.empty()) {
            break;
          }
          task = std::move(tasks_.front());
          tasks_.pop();
        }
        task();
      }
    });
  }
}

void ThreadPool::stop() noexcept {
  {
    std::unique_lock <std::mutex> lock{ eventMutex_ };
    stopping_ = true;
  }

  /* thread has stopped therefore notify the waiting threads to
   *
   * further test their condition variable predicate.
   * */
  eventVar_.notify_all();

  for (auto& thread : threads_) {
    thread.join();
  }
}
