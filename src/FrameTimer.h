#ifndef FRAMETIMER_H_1126610
#define FRAMETIMER_H_1126610

#include <chrono>

class FrameTimer
{
public:

    float deltaTime = 0;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    void Mark(){start = std::chrono::steady_clock::now();}
    void SetDuration(){

    end = std::chrono::steady_clock::now();

    std::chrono::duration<float> runtime = end - start;

    deltaTime = runtime.count();

    }
};

#endif // FRAMETIMER_H_1126610
