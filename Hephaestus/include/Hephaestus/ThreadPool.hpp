#pragma once
#include <Hephaestus/Includes.h>

// cpp 从 17 开始弃用 result_of，改用 invoke_result
#if __cplusplus >= 201703L
#define RESULT_OF_T(F, ...) std::invoke_result_t<F, __VA_ARGS__>
#else
#define RESULT_OF_T(F, ...) typename std::result_of<F(__VA_ARGS__)>::type
#endif

class ThreadPool {
public:
  explicit ThreadPool(size_t const &capacity);

  ThreadPool(ThreadPool const &) = delete;

  ~ThreadPool();

  template <typename F, typename... Args>
  auto enqueue(F &&f, Args &&...args) -> std::future<RESULT_OF_T(F, Args...)>;

  size_t getCapacity() { return capacity; }

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::condition_variable condition;
  std::mutex queueMutex;
  bool stop;
  size_t capacity;
};

template <typename F, typename... Args>
auto ThreadPool::enqueue(F &&f, Args &&...args)
    -> std::future<RESULT_OF_T(F, Args...)> {
  //
  using ret_type = RESULT_OF_T(F, Args...);
  auto task = std::make_shared<std::packaged_task<ret_type()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  std::future<ret_type> ret = task->get_future();
  {
    std::lock_guard lock{queueMutex};
    if (stop) {
      throw std::runtime_error("错误：人物入队时销毁了线程池");
    }

    tasks.emplace([task]() { (*task)(); });
  }
  condition.notify_one();
  return ret;
}

inline ThreadPool::ThreadPool(size_t const &capacity)
    : stop(false), capacity(capacity) {
  for (size_t i = 0; i < capacity; ++i) {
    workers.emplace_back([this]() {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock lock{queueMutex};
          // 收到结束信号或还有任务就接触阻塞
          condition.wait(lock, [this]() { return stop || !tasks.empty(); });

          // 只要受到结束信号且队列中没有任务了就返回，否则就执行任务
          if (stop && tasks.empty()) {
            return;
          }
          task = tasks.front();
          tasks.pop();
        }
        task();
      }
    });
  }
}

inline ThreadPool::~ThreadPool() {
  {
    std::lock_guard lock{queueMutex};
    stop = true;
  }
  condition.notify_all();
  for (auto &worker : workers) {
    worker.join();
  }
}
