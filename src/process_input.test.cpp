#include <gtest/gtest.h>

#include <process_input.hpp>

using namespace std::chrono_literals;

TEST(to_timecode, callFunction)
{
    std::string_view timecode_str("12:34:56:789");
    Timecode t = to_timecode(timecode_str);
}

TEST(to_timecode, matchHoursValue)
{
    ASSERT_EQ(to_timecode("12:34:56:789").HOURS, 12h);
    ASSERT_EQ(to_timecode("13:24:35,467").HOURS, 13h);
}

TEST(to_timecode, matchMinutesValue)
{
    ASSERT_EQ(to_timecode("12:34:56:789").MINUTES, 34min);
    ASSERT_EQ(to_timecode("13:24:35,467").MINUTES, 24min);
}

TEST(to_timecode, matchSecondsValue)
{
    ASSERT_EQ(to_timecode("12:34:56:789").SECONDS, 56s);
    ASSERT_EQ(to_timecode("13:24:35,467").SECONDS, 35s);
}

TEST(to_timecode, matchMillisecondsValue)
{
    ASSERT_EQ(to_timecode("12:34:56:789").MILLISECONDS, 789ms);
    ASSERT_EQ(to_timecode("13:24:35,467").MILLISECONDS, 467ms);
}
