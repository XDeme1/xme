#include "../common.hpp"
#include <xme/container/spsc_queue.hpp>
#include <chrono>
#include <thread>

struct TestQueue {
    TestQueue() { worker = std::thread(&TestQueue::job, this); }

    ~TestQueue() {
        running = false;
        worker.join();
    }

    void job() {
        auto start = std::chrono::steady_clock::now();
        int frames = 0;
        while (running) {
            ++frames;
            const auto now = std::chrono::steady_clock::now();
            auto diff = now - start;
            auto end = now + std::chrono::microseconds(16666);
            if (diff >= std::chrono::seconds(1)) {
                start = now;
                std::cerr << '\n' << "FPS: " << frames << '\n';
                frames = 0;
            }

            const std::size_t available = queue.readAvailable();
            for (std::size_t i = 0; i < available; ++i)
                queue.consume([](int&& a) { std::cerr << a << ' '; });
            
            std::this_thread::yield();
            std::this_thread::sleep_until(end);
        }
    }

    std::thread worker;
    xme::SPSCQueue<int, 512, xme::StaticAllocation> queue;
    bool running = true;
};

int main() {
    xme::SPSCQueue<int, 8, xme::StaticAllocation> static_queue;
    xme::SPSCQueue<int, 8, xme::DynamicAllocation<std::allocator<int>>> dynamic_queue;
    return 0;
}