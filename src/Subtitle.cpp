#include <Subtitle.hpp>

#include <stdexcept>

Subtitle::Subtitle(std::size_t sequence, Timecode start, Timecode end,
                   std::string text)
    : SEQUENCE(sequence), START(start), END(end), TEXT(text)
{
    if (SEQUENCE == 0)
    {
        throw std::invalid_argument("Sequence number must be greater than zero");
    }

    if (!(start < end))
    {
        throw std::invalid_argument("End time must be greater than start time");
    }
}

std::string Subtitle::str() const
{
    return std::to_string(SEQUENCE) + "\n" + START.str() + " --> " +
           END.str() + "\n" + TEXT + "\n";
}
