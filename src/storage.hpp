#ifndef INCLUDE_STORAGE_HPP
#define INCLUDE_STORAGE_HPP

#include <cstdint>
#include <fstream>

using std::ifstream;
using std::ofstream;


const uint32_t MAP_DATA_VERSION = 1;


void write8(ofstream& file, uint8_t);
void write32(ofstream& file, uint32_t);

uint8_t read8(ifstream& file);
uint32_t read32(ifstream& file);


#endif // INCLUDE_STORAGE_HPP
