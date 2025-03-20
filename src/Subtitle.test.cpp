#include <gtest/gtest.h>
#include <type_traits>

#include <Subtitle.hpp>

using namespace std::chrono_literals;

bool operator==(const Timecode &lhs, const Timecode &rhs)
{
    return lhs.HOURS == rhs.HOURS &&
           lhs.MINUTES == rhs.MINUTES &&
           lhs.SECONDS == rhs.SECONDS &&
           lhs.MILLISECONDS == rhs.MILLISECONDS;
}

TEST(SubtitleCtor, createInitialized)
{
    Subtitle subtitle(std::size_t{}, Timecode{}, Timecode{}, std::string{});
}

TEST(SubtitleAttributes, accessValues)
{
    Subtitle subtitle(std::size_t{}, Timecode{}, Timecode{}, std::string{});
    std::size_t sequence = subtitle.SEQUENCE;
    Timecode start = subtitle.START;
    Timecode end = subtitle.END;
    std::string text = subtitle.TEXT;
}

TEST(SubtitleAttributes, valuesAreConstant)
{
    Subtitle subtitle(std::size_t{}, Timecode{}, Timecode{}, std::string{});
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.SEQUENCE)>);
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.START)>);
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.END)>);
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.TEXT)>);
}

TEST(SubtitleCtor, matchInitialValues)
{
    std::size_t sequence = 123;
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...";
    Subtitle subtitle(sequence, start, end, text);

    ASSERT_EQ(subtitle.SEQUENCE, sequence);
    ASSERT_EQ(subtitle.START, start);
    ASSERT_EQ(subtitle.END, end);
    ASSERT_EQ(subtitle.TEXT, text);
}
