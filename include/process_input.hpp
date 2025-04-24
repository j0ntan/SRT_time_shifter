#pragma once

#include <string_view>
#include <chrono>
#include <string>
#include <istream>
#include <ostream>

#include <Timecode.hpp>

/**
 * @brief Convert a timecode string to a `Timecode` object
 *
 * Assumes that the string is already timecode formatted
 *
 * @param str_v The timecode string
 * @return Timecode The converted timecode instance
 */
Timecode to_timecode(const std::string_view &str_v);

/**
 * @brief Simple aggregation of timecode components for convenience
 *
 */
struct ShiftAmount
{
    std::chrono::hours hours;
    std::chrono::minutes minutes;
    std::chrono::seconds seconds;
    std::chrono::milliseconds milliseconds;
};

/**
 * @brief Create timecode string that was shifted by a given time amount
 *
 * @param timecode_range Timecode string to be shifted
 * @param sa The shift amount
 * @return std::string The shifted timecode string
 */
std::string shift_timecode_range_str(std::string_view timecode_range,
                                     ShiftAmount sa);

/**
 * @brief Fills an output stream with the SRT text from an input stream with
 * the timecodes shifted by the given amount
 *
 * @param shift_amount Time components used to shift the input timecodes
 * @param in_stream Input stream containing subtitle text in SRT format
 * @param out_stream Output stream containing the shifted timecodes
 */
void process_input(ShiftAmount shift_amount, std::istream &in_stream,
                   std::ostream &out_stream);
