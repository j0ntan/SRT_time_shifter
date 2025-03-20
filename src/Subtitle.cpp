#include <Subtitle.hpp>

Subtitle::Subtitle(std::size_t sequence, Timecode start, Timecode end,
                   std::string text)
    : SEQUENCE(sequence), START(start), END(end), TEXT(text)
{
}
