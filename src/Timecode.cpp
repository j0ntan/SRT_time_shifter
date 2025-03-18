#include <Timecode.hpp>

#include <stdexcept>

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
