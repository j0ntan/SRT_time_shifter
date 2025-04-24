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

TEST(ShiftAmount, createDefault)
{
    ShiftAmount sa;
}

TEST(ShiftAmount, accessMembers)
{
    ShiftAmount sa;
    std::chrono::hours hours = sa.hours;
    std::chrono::minutes minutes = sa.minutes;
    std::chrono::seconds seconds = sa.seconds;
    std::chrono::milliseconds milliseconds = sa.milliseconds;
}

TEST(shift_timecode_range_str, callFunction)
{
    std::string_view timecode_range_str("12:34:56,789 --> 13:24:35,467");
    ShiftAmount sa{};
    std::string shifted = shift_timecode_range_str(timecode_range_str, sa);
}

TEST(shift_timecode_range_str, shiftStartTimeByGivenAmount)
{
    std::string shifted = shift_timecode_range_str(
        "12:34:56,789 --> 13:24:35,467", ShiftAmount{1h, 2min, 3s, 4ms});

    std::string start_time = shifted.substr(0, 12), expected("13:36:59,793");
    ASSERT_GE(shifted.size(), 12);
    ASSERT_EQ(start_time, expected);
}

TEST(shift_time_range_str, matchArrowSeparator)
{
    std::string shifted = shift_timecode_range_str(
        "12:34:56,789 --> 13:24:35,467", ShiftAmount{1h, 2min, 3s, 4ms});

    ASSERT_GE(shifted.size(), 17);
    ASSERT_EQ(shifted.substr(12, 5), " --> ");
}

TEST(shift_timecode_range_str, shiftEndTimeByGivenAmount)
{
    std::string shifted =
        shift_timecode_range_str("12:34:56,789 --> 13:24:35,467",
                                 ShiftAmount{1h, 2min, 3s, 4ms});

    std::string end_time = shifted.substr(17, 12), expected("14:26:38,471");
    ASSERT_EQ(shifted.size(), 29);
    ASSERT_EQ(end_time, expected);
}

TEST(processInput, callFunction)
{
    ShiftAmount sa;
    std::istringstream iss;
    std::ostringstream oss;
    process_input(sa, iss, oss);
}

TEST(processInput, reachesEndOfInputStream)
{
    ShiftAmount sa{};
    std::istringstream iss("1\n"
                           "01:02:03,004 --> 05:06:07,008\n"
                           "Once upon a time...\n\n");
    std::ostringstream oss;
    process_input(sa, iss, oss);

    ASSERT_TRUE(iss.eof());
}

TEST(processInput, OutputMatchesInputForZeroShift)
{
    ShiftAmount sa{0h, 0min, 0s, 0ms};
    std::string input_str("1\n"
                          "01:02:03,004 --> 05:06:07,008\n"
                          "Once upon a time...\n\n");
    std::istringstream iss(input_str);
    std::ostringstream oss;
    process_input(sa, iss, oss);

    ASSERT_EQ(oss.str(), input_str);
}

TEST(processInput, shiftTimesByGivenAmount)
{
    ShiftAmount sa{1h, 2min, 3s, 4ms};
    std::string input("1\n"
                      "01:02:03,004 --> 05:06:07,008\n"
                      "Once upon a time...\n\n"
                      "2\n"
                      "06:07:08,009 --> 10:11:12,013\n"
                      "In a land far away...\n\n"),
        expected("1\n"
                 "02:04:06,008 --> 06:08:10,012\n"
                 "Once upon a time...\n\n"
                 "2\n"
                 "07:09:11,013 --> 11:13:15,017\n"
                 "In a land far away...\n\n");
    std::istringstream iss(input);
    std::ostringstream oss;
    process_input(sa, iss, oss);

    ASSERT_EQ(oss.str(), expected);
}

TEST(processInput, useGeneralIOstreams)
{
    class MyInStream : public std::istream
    {
    };
    class MyOutStream : public std::ostream
    {
    };

    ShiftAmount sa{1h, 2min, 3s, 4ms};
    MyInStream my_in;
    MyOutStream my_out;
    process_input(sa, my_in, my_out);
}
