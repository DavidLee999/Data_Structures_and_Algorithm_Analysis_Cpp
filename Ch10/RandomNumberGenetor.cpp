#include <iostream>

class Random
{
    public:
        explicit Random(int initialValue = 1)
        {
            if (initialValue < 0)
                initialValue += M;

            state = initialValue;
            if (state == 0)
                state = 1;
        }

        int randomInt()
        {
            int tmpState = A * (state % Q) - R * (state / Q);

            if (tmpState >= 0)
                state = tmpState;
            else
                state = tmpState + M;

            return state;
        }

        int random0_1()
        { return static_cast<double>(randomInt()) / M; }
    private:
        static const int A = 48271;
        static const int M = 2147483647;
        static const int Q = M / A;
        static const int R = M % A;

        int state;
};


int main()
{
    Random randomNum {};
    for (int i = 0; i < 10; ++i)
        std::cout << randomNum.randomInt() << '\n';

    return 0;
}
