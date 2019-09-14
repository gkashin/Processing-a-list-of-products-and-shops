//
//  shop.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <string>

#include "shop.hpp"
#include "errorHandling.hpp"

Shop::Shop() : name_("") {}

Shop::Shop(string name) : name_(name) {}

void Shop::operator=(const Shop &otherShop)
{
    name_ = otherShop.name_;
}

bool operator==(const Shop &firstShop, const Shop &secondShop)
{
    return firstShop.name_ == secondShop.name_;
}

bool Shop::operator==(const Shop &otherShop)
{
    return name_ == otherShop.name_;
}

ostream& operator<<(ostream& output, const Shop& shop)
{
    output << shop.name_;
    return output;
}

istream& operator>>(istream& input, Shop& shop)
{
    input >> shop.name_;
    return input;
}

string Shop::getName()
{
    return name_;
}

bool Shop::isValidShop(const string shop)
{
    return ErrorHandling::isValidField(shop);
}
