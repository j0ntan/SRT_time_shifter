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

    /**
     * @brief Construct a `Timecode` object with the given time components
     *
     * @param h The number of hours
     * @param m The number of minutes
     * @param s The number of seconds
     * @param ms The number of milliseconds
     *
     * @throw `std::invalid_argument` if any of the time components are
     * out-of-range
     *
     */
    Timecode(std::chrono::hours h, std::chrono::minutes m,
             std::chrono::seconds s, std::chrono::milliseconds ms);

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

    /**
     * @brief Valid range for each time component
     *
     */
    static constexpr std::chrono::hours HOURS_MIN{0};
    static constexpr std::chrono::hours HOURS_MAX{99};
    static constexpr std::chrono::minutes MINUTES_MIN{0};
    static constexpr std::chrono::minutes MINUTES_MAX{59};
    static constexpr std::chrono::seconds SECONDS_MIN{0};
    static constexpr std::chrono::seconds SECONDS_MAX{59};
    static constexpr std::chrono::milliseconds MILLISECONDS_MIN{0};
    static constexpr std::chrono::milliseconds MILLISECONDS_MAX{999};
};
