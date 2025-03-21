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
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    Subtitle subtitle(1, start, end, text);
}

TEST(SubtitleAttributes, accessValues)
{
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    Subtitle subtitle(1, start, end, text);

    std::size_t sequence = subtitle.SEQUENCE;
    Timecode start_val = subtitle.START;
    Timecode end_val = subtitle.END;
    std::string text_val = subtitle.TEXT;
}

TEST(SubtitleAttributes, valuesAreConstant)
{
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    Subtitle subtitle(1, start, end, text);

    ASSERT_TRUE(std::is_const_v<decltype(subtitle.SEQUENCE)>);
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.START)>);
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.END)>);
    ASSERT_TRUE(std::is_const_v<decltype(subtitle.TEXT)>);
}

TEST(SubtitleCtor, matchInitialValues)
{
    std::size_t sequence = 123;
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    Subtitle subtitle(sequence, start, end, text);

    ASSERT_EQ(subtitle.SEQUENCE, sequence);
    ASSERT_EQ(subtitle.START, start);
    ASSERT_EQ(subtitle.END, end);
    ASSERT_EQ(subtitle.TEXT, text);
}

TEST(SubtitleCtor, sequenceMustBeGreaterThanZero)
{
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    ASSERT_THROW(Subtitle(0, start, end, text), std::invalid_argument);
}

TEST(SubtitleCtor, startMustBeLessThanEnd)
{
    Timecode start(1h, 2min, 3s, 4ms), end(1h, 2min, 3s, 4ms);
    std::string text = "Once upon a time...\n";
    ASSERT_THROW(Subtitle(1, start, end, text), std::invalid_argument);
}

TEST(SubtitleString, convertToString)
{
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    Subtitle subtitle(1, start, end, text);

    std::string str = subtitle.str();
}

TEST(SubtitleString, matchFormattedString)
{
    Timecode start(1h, 2min, 3s, 4ms), end(5h, 6min, 7s, 8ms);
    std::string text = "Once upon a time...\n";
    Subtitle subtitle1(1, start, end, text), subtitle2(2, start, end, text);

    std::string expected1 = "1\n"
                            "01:02:03,004 --> 05:06:07,008\n"
                            "Once upon a time...\n\n",
                expected2 = "2\n"
                            "01:02:03,004 --> 05:06:07,008\n"
                            "Once upon a time...\n\n";
    ASSERT_EQ(subtitle1.str(), expected1);
    ASSERT_EQ(subtitle2.str(), expected2);
}
