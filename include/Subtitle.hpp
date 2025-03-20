#pragma once

#include <cstddef>
#include <string>

#include <Timecode.hpp>

/**
 * @brief A subtitle frame that follows the SubRip format
 *
 */
class Subtitle
{
public:
    /**
     * @brief Construct a new Subtitle object
     *
     * @param sequence The sequence number of the subtitle
     * @param start The start time of the subtitle
     * @param end The end time of the subtitle
     * @param text The text of the subtitle
     */
    Subtitle(std::size_t sequence, Timecode start, Timecode end,
             std::string text);

    std::string str() const;

    ////////////////////////
    /// Member Variables ///
    ////////////////////////

    const std::size_t SEQUENCE;
    const Timecode START;
    const Timecode END;
    const std::string TEXT;
};
