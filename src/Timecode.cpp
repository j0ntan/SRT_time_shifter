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
