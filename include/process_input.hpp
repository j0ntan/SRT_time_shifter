#pragma once

#include <string_view>

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
