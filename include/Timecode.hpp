#pragma once

#include <chrono>
#include <string>

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

    /**
     * @brief Convert the timecode to a string representation
     *
     * @return std::string The timecode as a string
     */
    std::string str() const;

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

/**
 * @brief Compare two timecodes for less-than ordering
 *
 * @param lhs The left-hand side timecode
 * @param rhs The right-hand side timecode
 * @return true if `lhs` is less than `rhs`
 * @return false if `lhs` is greater than or equal to `rhs`
 */
bool operator<(const Timecode &lhs, const Timecode &rhs);

/**
 * @brief Shift a timecode by the given time components
 *
 * @param timecode The timecode to shift
 * @param h The number of hours to shift by
 * @param m The number of minutes to shift by
 * @param s The number of seconds to shift by
 * @param ms The number of milliseconds to shift by
 * @return Timecode The shifted timecode
 */
Timecode shift(const Timecode &timecode, std::chrono::hours h,
               std::chrono::minutes m, std::chrono::seconds s,
               std::chrono::milliseconds ms);
