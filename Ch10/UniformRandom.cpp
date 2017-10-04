#include <chrono>
#include <random>
#include <functional>
#include <iostream>
using namespace std;

int currentTimeSeconds()
{
    auto now = chrono::high_resolution_clock::now().time_since_epoch();
    return (chrono::duration_cast<chrono::seconds>(now)).count();
}

class UniformRandom
{
    public:
        explicit UniformRandom(int seed = currentTimeSeconds()) : generator { seed } {}

        int nextInt()
        {
            static uniform_int_distribution<unsigned int> distribution;
            return distribution(generator);
        }

        int nextInt(int high)
        {
            return nextInt(0, high - 1);
        }

        int nextInt(int low, int high)
        {
            uniform_int_distribution<int> distribution(low, high);
            return distribution(generator);
        }

        double nextDouble()
        {
            static uniform_real_distribution<double> distribution(0, 1);
            return distribution(generator);
        }
    private:
        mt19937 generator;
};

int main()
{
    UniformRandom ur {};
    for (int i = 0; i < 10; ++i)
        cout << ur.nextInt() << '\n';

    return 0;
}
