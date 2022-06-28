#pragma once

#include "ThreadPool.h"

#include <cstdint>

namespace jaids {
    namespace lossless {
        class ThreadPoolMgr {
        public:
            ThreadPoolMgr(const ThreadPoolMgr&) = delete;
            ThreadPoolMgr& operator=(const ThreadPoolMgr&) = delete;
            ThreadPoolMgr(ThreadPoolMgr&&) = delete;
            ThreadPoolMgr& operator=(ThreadPoolMgr&&) = delete;

            static ThreadPoolMgr& GetInstance(const uint16_t thread_num);
            ThreadPool& GetPool();
            ~ThreadPoolMgr() = default;

        private:
            ThreadPoolMgr() = delete;
            ThreadPoolMgr(const uint16_t);
            ThreadPool* pool_;
        };
    }  // namespace lossless
}  // namespace jaids
