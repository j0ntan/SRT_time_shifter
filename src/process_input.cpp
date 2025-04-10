#include <process_input.hpp>

#include <charconv>

using namespace std::chrono_literals;

Timecode to_timecode(const std::string_view &str_v)
{
    const std::size_t TWO_DIGIT_LEN = 2, THREE_DIGIT_LEN = 3;

    // offset of time components from start of timecode
    const std::size_t HOURS_OFFSET = 0, MINUTES_OFFSET = 3,
                      SECONDS_OFFSET = 6, MILLISECONDS_OFFSET = 9;

    // start & end pointers for time components
    const char *const HOURS_START_PTR = str_v.begin() + HOURS_OFFSET;
    const char *const HOURS_END_PTR = HOURS_START_PTR + TWO_DIGIT_LEN;
    const char *const MINUTES_START_PTR = str_v.begin() + MINUTES_OFFSET;
    const char *const MINUTES_END_PTR = MINUTES_START_PTR + TWO_DIGIT_LEN;
    const char *const SECONDS_START_PTR = str_v.begin() + SECONDS_OFFSET;
    const char *const SECONDS_END_PTR = SECONDS_START_PTR + TWO_DIGIT_LEN;
    const char *const MILLISECONDS_START_PTR = str_v.begin() +
                                               MILLISECONDS_OFFSET;
    const char *const MILLISECONDS_END_PTR = MILLISECONDS_START_PTR +
                                             THREE_DIGIT_LEN;

    // read time component values from chars in timecode string
    std::size_t hours_val, minutes_val, seconds_val, milliseconds_val;
    std::from_chars(HOURS_START_PTR, HOURS_END_PTR, hours_val);
    std::from_chars(MINUTES_START_PTR, MINUTES_END_PTR, minutes_val);
    std::from_chars(SECONDS_START_PTR, SECONDS_END_PTR, seconds_val);
    std::from_chars(MILLISECONDS_START_PTR, MILLISECONDS_END_PTR,
                    milliseconds_val);

    return Timecode(std::chrono::hours{hours_val},
                    std::chrono::minutes{minutes_val},
                    std::chrono::seconds{seconds_val},
                    std::chrono::milliseconds{milliseconds_val});
}
