
#include <string_view>
#include <string>
#include <utility>
#include <cctype>
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>

int dial = 50;
int targetCounter = 0;
const int target = 0;
const char right = 'R';

enum class Mode
{
    AfterRotation,
    DuringRotation
};

void checkIncrementDial()
{
    if (dial == target)
    {
        targetCounter++;
    }
}

int rotateDial(int rotation, int direction, Mode mode)
{
    if (mode == Mode::DuringRotation)
    {
        int start = ((dial % 100) + 100) % 100;

        int k = (direction == 1) ? ((100 - start) % 100) : (start % 100);

        if (k == 0)
        {
            k = 100;
        }

        int passes = 0;

        if (rotation >= k)
        {
            passes = 1 + (rotation - k) / 100;
        }

        targetCounter += passes;

        int final = rotation % 100;

        dial += direction * final;
    }

    else
    {
        dial += direction * rotation;
    }

    dial %= 100;

    if (dial < 0)
    {
        dial += 100;
    }

    if (mode == Mode::AfterRotation)
    {
        checkIncrementDial();
    }

    return dial;
}

std::pair<int, int> parseLine(std::string_view s)
{
    if (s.empty())
    {
        return {0, 1};
    }

    int rotation = std::stoi(std::string(s.substr(1)));

    int direction = s.front() == right ? 1 : -1;

    return {rotation, direction};
}

std::vector<std::string_view> parseText(std::string_view text)
{
    std::vector<std::string_view> res;

    size_t pos = 0;

    while (pos < text.size())
    {
        size_t e = text.find('\n', pos);

        std::string_view line = (e == std::string_view::npos) ? text.substr(pos) : text.substr(pos, e - pos);

        if (!line.empty() && line.back() == '\r')
        {
            line.remove_suffix(1);
        }

        if (!line.empty())
            res.push_back(line);

        if (e == std::string_view::npos)
            break;

        pos = e + 1;
    }

    return res;
}

Mode parseModeFromArgs(int argc, char *argv[])
{
    if (argc >= 3)
    {
        std::string a = argv[2];

        if (a == "--during" || a == "--method=0x434C49434B")
        {
            return Mode::DuringRotation;
        }
    }

    return Mode::AfterRotation;
}

const char *getModeString(Mode m)
{
    return (m == Mode::AfterRotation) ? "Normal Password Mode" : "Password Method 0x434C49434B";
}

int main(int argc, char *argv[])
{
    std::string content;

    Mode mode = parseModeFromArgs(argc, argv);

    if (argc >= 2)
    {
        std::ifstream ifs(argv[1], std::ios::binary);

        if (!ifs)
        {
            return 1;
        }

        content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    }

    else
    {
        content.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
    }

    auto res = parseText(std::string_view(content));

    for (std::string_view line : res)
    {
        std::pair<int, int> p = parseLine(line);
        int rotation = p.first;
        int direction = p.second;

        rotateDial(rotation, direction, mode);
    }

    std::cout << "Mode: " << getModeString(mode) << "Amount of times the dial pointed at the target value (" << target
              << "): " << targetCounter << '\n';
}