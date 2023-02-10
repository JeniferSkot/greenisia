#include "storage.hpp"
#include <string>

using std::string;


void write8(std::ofstream& file, uint8_t data)
{
    char input = static_cast<char>(data);
    file.write(&input, 1);
}

void write32(std::ofstream& file, uint32_t data)
{
    char input[4] {
        static_cast<char>(data >> 24),
        static_cast<char>(data >> 16),
        static_cast<char>(data >> 8),
        static_cast<char>(data)
    };

    file.write(&input[0], 4);
}


uint8_t read8(std::ifstream& file)
{
    char input;
    file.read(&input, 1);
    return static_cast<uint8_t>(input);
}


uint32_t read32(std::ifstream& file)
{
    char input[4];
    file.read(&input[0], 4);

    uint32_t data = input[0];
    for(int i = 1; i < 4; ++i) {
        data = data << 8;
        data += static_cast<uint8_t>(input[i]);
    }

    return data;
}


void write(std::ofstream& file, string data)
{
    write32(file, data.size());
    file << data;
}

string read(std::ifstream& file)
{
    size_t size = read32(file);

    string input(size, '?');
    file.read(&input[0], size);

    return input;
}
