#include "item.hpp"


std::map<fs::path, Item>& items()
{
    static std::map<fs::path, Item> _items;
    return _items;
}

Item& item(fs::path key)
{
    static Item unknown {"Unknown", "", {64, 64}};

    auto itr = items().find(key);
    if(itr == items().end())
        return unknown;
    return itr->second;
}
