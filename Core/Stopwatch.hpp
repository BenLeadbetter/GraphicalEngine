#ifndef GUARD_STOPWATCH_HPP
#define GUARD_STOPWATCH_HPP

#include <chrono>

class Stopwatch
{
    using Clock = std::chrono::high_resolution_clock;

    public:
        Stopwatch() : 
            start_point(Clock::now()),
            restart_point(Clock::now())
        {}

        template <typename Rep = typename Clock::duration::rep, typename Units = typename Clock::duration>
        Rep elapsed_time() const
        {
            auto counted_time = std::chrono::duration_cast<Units>(Clock::now() - restart_point).count();
            return static_cast<Rep>(counted_time);
        }

        void restart()
        {
            restart_point = Clock::now();
        }
    
    private:

        Clock::time_point start_point;
        Clock::time_point restart_point;
};

#endif