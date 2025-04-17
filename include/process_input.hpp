#pragma once

#include <string_view>
#include <chrono>
#include <string>

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
