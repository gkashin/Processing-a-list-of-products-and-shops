//
//  shops.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#include "shop.hpp"
#include "shops.hpp"

Shop Shops::operator[](int index)
{
    if (index < 0 || index >= shopsList.size())
    {
        throw invalid_argument("Shops index error");
    }
    return shopsList[index];
}

bool Shops::addShop(string name) // добавляем магазин, если он еще не был добавлен
{
    bool sameName = false;
    
    if (shopsList.empty())
    {
        shopsList.push_back(Shop(name));
        return true;
    }
    else
    {
        for (int i = 0; i < shopsList.size(); i++)
        {
            if (name == shopsList[i].getName())
            {
                sameName = true;
                break;
            }
        }
    }
    
    if (!sameName)
    {
        shopsList.push_back(Shop(name));
    }
    
    return !sameName;
}

int Shops::shopsCount()
{
    return static_cast<int>(shopsList.size());
}

void operator<<(ofstream& output, Shops &shopsList)
{
    extern int maxShopLength;
    
    string titleName = "Shops list";
    int titleNameLength = static_cast<int>(titleName.length());
    
    output << setw(maxShopLength) << left << titleName << endl;
    
    if (maxShopLength <= titleNameLength) { maxShopLength = titleNameLength; }
    
    for (int i = 0; i < titleNameLength; i++)
    {
        output << "-";
    }
    
    output << endl;
    
    for (int i = 0; i < shopsList.shopsCount(); i++)
    {
        output << setw(maxShopLength) << left << shopsList[i] << endl;
    }
}
