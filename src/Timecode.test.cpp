#include <gtest/gtest.h>

#include <Timecode.hpp>

using namespace std::chrono_literals;

TEST(TimecodeCtor, createDefault)
{
    Timecode timecode;
}

TEST(TimecodeAttributes, accessTimeComponents)
{
    Timecode timecode;
    std::chrono::hours hr = timecode.HOURS;
    std::chrono::minutes min = timecode.MINUTES;
    std::chrono::seconds sec = timecode.SECONDS;
    std::chrono::milliseconds ms = timecode.MILLISECONDS;
}

TEST(TimecodeAttributes, componentsAreConst)
{
    ASSERT_TRUE(std::is_const_v<decltype(Timecode{}.HOURS)>);
    ASSERT_TRUE(std::is_const_v<decltype(Timecode{}.MINUTES)>);
    ASSERT_TRUE(std::is_const_v<decltype(Timecode{}.SECONDS)>);
    ASSERT_TRUE(std::is_const_v<decltype(Timecode{}.MILLISECONDS)>);
}

TEST(TimecodeCtor, zeroDefaultValues)
{
    Timecode timecode;

    ASSERT_EQ(timecode.HOURS.count(), 0);
    ASSERT_EQ(timecode.MINUTES.count(), 0);
    ASSERT_EQ(timecode.SECONDS.count(), 0);
    ASSERT_EQ(timecode.MILLISECONDS.count(), 0);
}

TEST(TimecodeCtor, takeInitialValues)
{
    std::chrono::hours h{1};
    std::chrono::minutes m{2};
    std::chrono::seconds s{3};
    std::chrono::milliseconds ms{4};
    Timecode timecode{h, m, s, ms};
    Timecode using_literals{1h, 2min, 3s, 4ms};
}

TEST(TimecodeCtor, matchInitialValues)
{
    Timecode timecode{1h, 2min, 3s, 4ms};

    ASSERT_EQ(timecode.HOURS, 1h);
    ASSERT_EQ(timecode.MINUTES, 2min);
    ASSERT_EQ(timecode.SECONDS, 3s);
    ASSERT_EQ(timecode.MILLISECONDS, 4ms);
}

TEST(TimecodeValidRanges, accessValidRangeStaticValues)
{
    std::chrono::hours h_max = Timecode::HOURS_MAX;
    std::chrono::hours h_min = Timecode::HOURS_MIN;
    std::chrono::minutes m_max = Timecode::MINUTES_MAX;
    std::chrono::minutes m_min = Timecode::MINUTES_MIN;
    std::chrono::seconds s_max = Timecode::SECONDS_MAX;
    std::chrono::seconds s_min = Timecode::SECONDS_MIN;
    std::chrono::milliseconds ms_max = Timecode::MILLISECONDS_MAX;
    std::chrono::milliseconds ms_min = Timecode::MILLISECONDS_MIN;
}

TEST(TimecodeCtor, throwExceptionOnInvalidArguments)
{
    ASSERT_THROW((Timecode{100h, 0min, 0s, 0ms}), std::invalid_argument);
    ASSERT_THROW((Timecode{0h, 60min, 0s, 0ms}), std::invalid_argument);
    ASSERT_THROW((Timecode{0h, 0min, 60s, 0ms}), std::invalid_argument);
    ASSERT_THROW((Timecode{0h, 0min, 0s, 1000ms}), std::invalid_argument);

    ASSERT_THROW((Timecode{-1h, 0min, 0s, 0ms}), std::invalid_argument);
    ASSERT_THROW((Timecode{0h, -1min, 0s, 0ms}), std::invalid_argument);
    ASSERT_THROW((Timecode{0h, 0min, -1s, 0ms}), std::invalid_argument);
    ASSERT_THROW((Timecode{0h, 0min, 0s, -1ms}), std::invalid_argument);
}

TEST(TimecodeStr, convertToString)
{
    Timecode timecode;

    std::string str = timecode.str();
}

TEST(TimecodeStr, matchStringFormat)
{

    Timecode timecode(1h, 2min, 3s, 4ms);
    std::string expected = "01:02:03,004";

    ASSERT_EQ(timecode.str(), expected);
}

TEST(shiftTimecode, getNewTimecodeResult)
{
    Timecode result = shift(Timecode(), 1h, 2min, 3s, 4ms);
}

TEST(shiftTimecode, increaseTimeComponents)
{
    Timecode result = shift(Timecode(), 1h, 2min, 3s, 4ms);

    ASSERT_EQ(result.HOURS, 1h);
    ASSERT_EQ(result.MINUTES, 2min);
    ASSERT_EQ(result.SECONDS, 3s);
    ASSERT_EQ(result.MILLISECONDS, 4ms);
}

TEST(shiftTimecode, decreaseTimeComponents)
{
    Timecode result = shift(Timecode(1h, 2min, 3s, 4ms), -1h, -2min, -3s, -4ms);

    ASSERT_EQ(result.HOURS, 0h);
    ASSERT_EQ(result.MINUTES, 0min);
    ASSERT_EQ(result.SECONDS, 0s);
    ASSERT_EQ(result.MILLISECONDS, 0ms);
}

TEST(shiftTimecode, increaseTimeWithOverflow)
{
    Timecode result = shift(Timecode(1h, 59min, 59s, 999ms), 0h, 1min, 1s, 1ms);

    ASSERT_EQ(result.HOURS, 2h);
    ASSERT_EQ(result.MINUTES, 1min);
    ASSERT_EQ(result.SECONDS, 1s);
    ASSERT_EQ(result.MILLISECONDS, 0ms);
}

TEST(shiftTimecode, decreaseTimeWithBorrow)
{
    Timecode result = shift(Timecode(1h, 0min, 0s, 0ms), 0h, -1min, -1s, -1ms);

    ASSERT_EQ(result.HOURS, 0h);
    ASSERT_EQ(result.MINUTES, 58min);
    ASSERT_EQ(result.SECONDS, 58s);
    ASSERT_EQ(result.MILLISECONDS, 999ms);
}
