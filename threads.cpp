#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>

class Kangaroo {
public:
    Kangaroo(std::string name, int speed) : name(name), speed(speed) {}

    void hop() {
        std::cout << name << " is hopping around." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 * (0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0))) / speed)));
    }

    void operator()() {
        std::cout << name << " has entered the field." << std::endl;
        while (true) {
            hop();
        }
    }

private:
    std::string name;
    int speed;
};

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    std::vector<std::string> kangaroo_names = {"Kangy", "Jumpy", "Hopper", "Rex"};
    std::vector<std::thread> kangaroo_threads;

    for (const auto &name : kangaroo_names) {
        int speed = rand() % 5 + 1;
        kangaroo_threads.emplace_back(Kangaroo(name, speed));
    }

    std::cout << "Let's watch the kangaroos hopping around:" << std::endl;

    for (auto &thread : kangaroo_threads) {
        thread.detach(); // Let threads run independently
    }

    // Let the kangaroos hop for some time
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Signal to stop the kangaroos
    std::cout << "Time's up! Let's call the kangaroos back." << std::endl;

    // No need to join the threads since we detached them earlier

    std::cout << "All kangaroos have finished hopping." << std::endl;

    return 0;
}
