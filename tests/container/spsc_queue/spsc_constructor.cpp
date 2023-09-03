#include "../common.hpp"
#include <thread>

struct TestQueue {
    TestQueue() {
        worker = std::jthread(&TestQueue::job, this);
    }

    ~TestQueue() {
        running = false;
        worker.join();

        const std::size_t avaialble = queue.readAvailable();
        for(std::size_t i = 0; i < avaialble; ++i)
            queue.consume([](int&& a){ std::cerr << a << ' '; });
    }

    constexpr void job() {
        while (running) {
            const std::size_t available = queue.readAvailable();
            if (available == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            for (std::size_t i = 0; i < available; ++i)
                queue.consume([](int&& a) { std::cerr << a << ' '; });

            std::this_thread::yield();
        }
    }
    
    std::jthread worker;
    xme::SPSCQueue<int, 512, xme::StaticAllocation> queue;
    bool running = true;
};

int main() {
    int errors = 0;
    TestQueue t;
    for (std::size_t i = 0; i < 1e3; ++i) {
        bool emplaced = t.queue.emplace(i);
        while (!emplaced) {
            emplaced = t.queue.emplace(i);
        }
    }

    return errors;
}