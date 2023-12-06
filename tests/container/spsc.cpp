#include <iostream>
#include <thread>
#include <xme/container/spsc_queue.hpp>

struct ConcurrencyTest {
    ConcurrencyTest() { worker = std::thread(&ConcurrencyTest::job, this); }

    ~ConcurrencyTest() {
        running = false;
        worker.join();
        const std::size_t available = queue.read_available();
        for(std::size_t i = 0; i < available; ++i)
            queue.consume([](int&& a) { (void)a; });
    }

    void job() {
        while(running) {
            const auto now = std::chrono::steady_clock::now();
            auto end       = now + std::chrono::microseconds(16666);

            const std::size_t available = queue.read_available();
            for(std::size_t i = 0; i < available; ++i)
                queue.consume([](int&& a) { (void)a; });

            std::this_thread::yield();
            std::this_thread::sleep_until(end);
        }
    }

    std::thread worker;
    xme::SPSCQueue<int, xme::Capacity<512>> queue;
    bool running = true;
};

int test_push() {
    int errors = 0;
    {
        xme::SPSCQueue<int, xme::Capacity<16>> queue;
        bool error         = queue.read_available() != 0 || queue.write_available() != 15;
        std::size_t pushed = 0;
        for(std::size_t i = 0; i < 13; ++i)
            pushed += queue.emplace(i);
        error |= queue.read_available() != pushed || queue.write_available() != (15 - pushed);
        error |= pushed == 0;
        if(error) {
            std::cerr << "xme::SPSCQueue push error\n";
            ++errors;
        }
    }
    return errors;
}

int test_pop() {
    int errors = 0;
    {
        xme::SPSCQueue<int> queue{8};
        bool error = queue.read_available() != 0 || queue.write_available() != 7;
        for(std::size_t i = 0; i < 7; ++i)
            queue.push(i);
        for(std::size_t i = 0; i < 4; ++i)
            queue.pop();
        error = queue.read_available() != 3 || queue.write_available() != 4;

        for(std::size_t i = 0; i < 4; ++i)
            queue.push(i);
        error = queue.read_available() != 7 || queue.write_available() != 0;
        if(error) {
            std::cerr << "xme::SPSCQueue pop error\n";
            ++errors;
        }
    }
    return errors;
}

void test_concurrency() {
    ConcurrencyTest t;
    for(std::size_t i = 0; i < 1000; ++i) {
        while(!t.queue.emplace(i)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

int main() {
    int errors = 0;
    errors += test_push();
    errors += test_pop();
    test_concurrency();
    return errors;
}
