#include <gtest/gtest.h>

#include "timecode_str_identifier.hpp"

TEST(timecode_str_identifier, callFunction)
{
    std::string_view str_v;
    bool result = is_timecode_range_str(str_v);
}

TEST(timecode_str_identifier, identifyBaseCase)
{
    std::string_view str_v("01:02:03,456 --> 02:03:04,567");

    ASSERT_TRUE(is_timecode_range_str(str_v));
}

TEST(timecode_str_identifier, matchExactLength)
{
    std::string_view too_long("01:02:03,456 --> 02:03:04,5670");
    std::string_view too_short("01:02:03,456 --> 02:03:04,56");

    ASSERT_FALSE(is_timecode_range_str(too_long));
    ASSERT_FALSE(is_timecode_range_str(too_short));
}

TEST(timecode_str_identifier, matchArrowSeparator)
{
    // replace each char in arrow & assert false
    std::string_view str_1("01:02:03,456.--> 02:03:04,567");
    std::string_view str_2("01:02:03,456 .-> 02:03:04,567");
    std::string_view str_3("01:02:03,456 -.> 02:03:04,567");
    std::string_view str_4("01:02:03,456 --. 02:03:04,567");
    std::string_view str_5("01:02:03,456 -->.02:03:04,567");

    ASSERT_FALSE(is_timecode_range_str(str_1));
    ASSERT_FALSE(is_timecode_range_str(str_2));
    ASSERT_FALSE(is_timecode_range_str(str_3));
    ASSERT_FALSE(is_timecode_range_str(str_4));
    ASSERT_FALSE(is_timecode_range_str(str_5));
}

TEST(timecode_str_identifier, matchTimeSeparators)
{
    // replace each char in separator symbols & assert false
    std::string_view str_1("01.02:03,456 --> 02:03:04,567");
    std::string_view str_2("01:02.03,456 --> 02:03:04,567");
    std::string_view str_3("01:02:03.456 --> 02:03:04,567");
    std::string_view str_4("01:02:03,456 --> 02.03:04,567");
    std::string_view str_5("01:02:03,456 --> 02:03.04,567");
    std::string_view str_6("01:02:03,456 --> 02:03:04.567");

    ASSERT_FALSE(is_timecode_range_str(str_1));
    ASSERT_FALSE(is_timecode_range_str(str_2));
    ASSERT_FALSE(is_timecode_range_str(str_3));
    ASSERT_FALSE(is_timecode_range_str(str_4));
    ASSERT_FALSE(is_timecode_range_str(str_5));
    ASSERT_FALSE(is_timecode_range_str(str_6));
}

TEST(timecode_str_identifier, matchTimeDigits)
{
    // replace each digit char & assert false
    std::string_view str_1(".1:02:03,456 --> 02:03:04,567");
    std::string_view str_2("0.:02:03,456 --> 02:03:04,567");
    std::string_view str_3("01:.2:03,456 --> 02:03:04,567");
    std::string_view str_4("01:0.:03,456 --> 02:03:04,567");
    std::string_view str_5("01:02:.3,456 --> 02:03:04,567");
    std::string_view str_6("01:02:0.,456 --> 02:03:04,567");
    std::string_view str_7("01:02:03,.56 --> 02:03:04,567");
    std::string_view str_8("01:02:03,4.6 --> 02:03:04,567");
    std::string_view str_9("01:02:03,45. --> 02:03:04,567");
    std::string_view str_10("01:02:03,456 --> .2:03:04,567");
    std::string_view str_11("01:02:03,456 --> 0.:03:04,567");
    std::string_view str_12("01:02:03,456 --> 02:.3:04,567");
    std::string_view str_13("01:02:03,456 --> 02:0.:04,567");
    std::string_view str_14("01:02:03,456 --> 02:03:.4,567");
    std::string_view str_15("01:02:03,456 --> 02:03:0.,567");
    std::string_view str_16("01:02:03,456 --> 02:03:04,.67");
    std::string_view str_17("01:02:03,456 --> 02:03:04,5.7");
    std::string_view str_18("01:02:03,456 --> 02:03:04,56.");

    ASSERT_FALSE(is_timecode_range_str(str_1));
    ASSERT_FALSE(is_timecode_range_str(str_2));
    ASSERT_FALSE(is_timecode_range_str(str_3));
    ASSERT_FALSE(is_timecode_range_str(str_4));
    ASSERT_FALSE(is_timecode_range_str(str_5));
    ASSERT_FALSE(is_timecode_range_str(str_6));
    ASSERT_FALSE(is_timecode_range_str(str_7));
    ASSERT_FALSE(is_timecode_range_str(str_8));
    ASSERT_FALSE(is_timecode_range_str(str_9));
    ASSERT_FALSE(is_timecode_range_str(str_10));
    ASSERT_FALSE(is_timecode_range_str(str_11));
    ASSERT_FALSE(is_timecode_range_str(str_12));
    ASSERT_FALSE(is_timecode_range_str(str_13));
    ASSERT_FALSE(is_timecode_range_str(str_14));
    ASSERT_FALSE(is_timecode_range_str(str_15));
    ASSERT_FALSE(is_timecode_range_str(str_16));
    ASSERT_FALSE(is_timecode_range_str(str_17));
    ASSERT_FALSE(is_timecode_range_str(str_18));
}
