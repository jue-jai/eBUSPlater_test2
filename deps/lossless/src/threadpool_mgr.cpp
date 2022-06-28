#include "threadpool_mgr.hpp"

#include "ThreadPool.h"

namespace jaids::lossless {
    ThreadPoolMgr& ThreadPoolMgr::GetInstance(const uint16_t thread_num) {
        static ThreadPoolMgr instance(thread_num);
        return instance;
    }
    ThreadPool& jaids::lossless::ThreadPoolMgr::GetPool() {
        return *pool_;
    }
    ThreadPoolMgr::ThreadPoolMgr(const uint16_t thread_num) { pool_ = new ThreadPool(thread_num); }
}  // namespace jaids::lossless