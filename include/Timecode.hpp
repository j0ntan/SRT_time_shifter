#pragma once

#include <chrono>

/**
 * @brief  @brief A timecode object that represents a time in hours, minutes,
 * seconds, and millisecond
 *
 * @note This timecode follows the standard SubRip timecode format, as
 * described in https://en.wikipedia.org/wiki/SubRip#Format. This defines the
 * valid range for  each time component.
 *
 */
class Timecode
{
public:
    /**
     * @brief Construct a zero-initialzed `Timecode` object
     *
     */
    Timecode() noexcept = default;

    ////////////////////////
    /// Member Variables ///
    ////////////////////////

    /**
     * @brief Time components that make up the timecode
     *
     */
    const std::chrono::hours HOURS{};
    const std::chrono::minutes MINUTES{};
    const std::chrono::seconds SECONDS{};
    const std::chrono::milliseconds MILLISECONDS{};
};
