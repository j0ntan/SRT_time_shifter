#include <fstream>

#include <process_input.hpp>

using namespace std::chrono_literals;

/**
 * @brief Open the sample file, process the subtitles and produce an output
 * file that can be manually checked. See todo file for future plans
 * (someday...).
 *
 * @return int Return successfully
 */

int main()
{
    std::ifstream in_file("sample.srt");
    std::ofstream out_file("sample.result.srt");

    process_input(ShiftAmount{0h, 2min, 4s, 23ms}, in_file, out_file);

    return 0;
}
