#include "item.hpp"


std::map<fs::path, Item>& items()
{
    static std::map<fs::path, Item> _items;
    return _items;
}

