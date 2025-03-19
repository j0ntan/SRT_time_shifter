#include <Timecode.hpp>

#include <stdexcept>
#include <sstream>
#include <iomanip>

Timecode::Timecode(std::chrono::hours h, std::chrono::minutes m,
                   std::chrono::seconds s, std::chrono::milliseconds ms)
    : HOURS{h}, MINUTES{m}, SECONDS{s}, MILLISECONDS{ms}
{
    const bool VALID_HOURS = h >= HOURS_MIN && h <= HOURS_MAX;
    const bool VALID_MINUTES = m >= MINUTES_MIN && m <= MINUTES_MAX;
    const bool VALID_SECONDS = s >= SECONDS_MIN && s <= SECONDS_MAX;
    const bool VALID_MILLISECONDS =
        ms >= MILLISECONDS_MIN && ms <= MILLISECONDS_MAX;
    if (!VALID_HOURS || !VALID_MINUTES || !VALID_SECONDS || !VALID_MILLISECONDS)
    {
        throw std::invalid_argument("Invalid time value");
    }
}

std::string Timecode::str() const
{
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << HOURS.count() << ":"
        << std::setw(2) << MINUTES.count() << ":"
        << std::setw(2) << SECONDS.count() << ","
        << std::setw(3) << MILLISECONDS.count();

    return oss.str();
}

Timecode shift(const Timecode &timecode, std::chrono::hours h,
               std::chrono::minutes m, std::chrono::seconds s,
               std::chrono::milliseconds ms)
{
    using namespace std::chrono;

    milliseconds result_ms = timecode.MILLISECONDS + ms;

    seconds result_s = timecode.SECONDS + s + duration_cast<seconds>(result_ms);
    result_ms %= milliseconds{1000};

    minutes result_m = timecode.MINUTES + m + duration_cast<minutes>(result_s);
    result_s %= seconds{60};

    hours result_h = timecode.HOURS + h + duration_cast<hours>(result_m);
    result_m %= minutes{60};

    // borrow if necessary
    if (result_ms < 0ms)
    {
        result_ms += 1000ms;
        --result_s;
    }
    if (result_s < 0s)
    {
        result_s += 60s;
        --result_m;
    }
    if (result_m < 0min)
    {
        result_m += 60min;
        --result_h;
    }

    return Timecode(result_h, result_m, result_s, result_ms);
}
