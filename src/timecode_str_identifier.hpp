#pragma once

#include <string_view>
#include <cctype>

namespace
{
    /**
     * @brief Check if a string follows the timecode format
     *
     * The accepted format is NN:NN:NN,NNN where N represents a number.
     *
     * @param timecode_str_v String view that is being checked
     * @ @return true If the string matches the required format
     * @return false If the string does not match the required format
     */
    bool is_timecode_str(std::string_view timecode_str_v)
    {
        const std::size_t COLON_POSITION1 = 2, COLON_POSITION2 = 5,
                          COMMA_POSITION = 8;
        bool format_matches = true;

        for (std::size_t i = 0;
             i < timecode_str_v.length() && format_matches; ++i)
        {
            if (i == COMMA_POSITION)
                format_matches = timecode_str_v[i] == ',';
            else if (i == COLON_POSITION1 || i == COLON_POSITION2)
                format_matches = timecode_str_v[i] == ':';
            else
                format_matches = std::isdigit(timecode_str_v[i]);
        }

        return format_matches;
    }
};

/**
 * @brief Check if a string follows the timecode range format
 *
 * The accepted format is NN:NN:NN,NNN --> NN:NN:NN,NNN where N represents a
 * number.
 *
 * @param timecode_range_str_v String view that is being checked
 * @return true If the string matches the required format
 * @return false If the string does not match the required format
 */
bool is_timecode_range_str(std::string_view timecode_range_str_v)
{
    const size_t EXPECTED_FULL_LENGTH = 29, ARROW_POS = 12, TIMECODE_LEN = 12,
                 FIRST_TIMECODE_POS = 0, SECOND_TIMECODE_POS = 17;

    return timecode_range_str_v.length() == EXPECTED_FULL_LENGTH &&
           timecode_range_str_v.substr(ARROW_POS, 5) == " --> " &&
           is_timecode_str(timecode_range_str_v.substr(
               FIRST_TIMECODE_POS, TIMECODE_LEN)) &&
           is_timecode_str(timecode_range_str_v.substr(
               SECOND_TIMECODE_POS, TIMECODE_LEN));
}
