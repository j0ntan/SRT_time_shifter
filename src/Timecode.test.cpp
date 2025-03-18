#include <gtest/gtest.h>

#include <Timecode.hpp>

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
