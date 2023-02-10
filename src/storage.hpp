#ifndef INCLUDE_STORAGE_HPP
#define INCLUDE_STORAGE_HPP

#include <cstdint>
#include <fstream>
#include <string>


void write8(std::ofstream& file, uint8_t);
void write32(std::ofstream& file, uint32_t);
void write(std::ofstream& file, std::string);

uint8_t read8(std::ifstream& file);
uint32_t read32(std::ifstream& file);
std::string read(std::ifstream& file);


#endif // INCLUDE_STORAGE_HPP
