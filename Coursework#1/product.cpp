//
//  product.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <string>
#include <iomanip>

#include "shop.hpp"
#include "product.hpp"
#include "errorHandling.hpp"

Product::Product() : name_(""), price_(0), shop_(Shop()) {}

Product::Product(string name, Shop shop, int price) : name_(name), price_(price), shop_(shop) {}

Product::Product(const Product& otherProduct) : name_(otherProduct.name_), shop_(otherProduct.shop_), price_(otherProduct.price_) {}

bool Product::operator==(const Product& otherProduct)
{
    return  name_ == otherProduct.name_ &&
    shop_ == otherProduct.shop_ &&
    price_ == otherProduct.price_;
}

bool Product::operator>(const Product& otherProduct)
{
    return price_ > otherProduct.price_;
}

void Product::operator=(const Product& otherProduct)
{
    name_ = otherProduct.name_;
    shop_ = otherProduct.shop_;
    price_ = otherProduct.price_;
}

Product& Product::operator++()
{
    price_++;
    return *this;
}

Product operator++(Product& product, int value)
{
    Product temp(product);
    product.price_++;
    return temp;
}

extern int maxProductLength;
extern int maxShopLength;
extern int maxPriceLength;

ostream& operator<<(ostream& output, const Product& product) {
    output << setw(maxProductLength) << left << product.name_ << '|' << setw(maxShopLength) << left << product.shop_ << '|' << setw(maxPriceLength - 7) << left << product.price_ << " рублей|" << endl;
    return output;
}

istream& operator>>(istream& input, Product& product) {
    input >> product.name_ >> product.shop_ >> product.price_;
    return input;
}

bool operator==(const Product& firstProduct, const Product& secondProduct)
{
    return  firstProduct.name_ == secondProduct.name_ &&
            firstProduct.shop_ == secondProduct.shop_ &&
            firstProduct.price_ == secondProduct.price_;
}

bool operator>(const Product& firstProduct, const Product& secondProduct)
{
    return firstProduct.price_ > secondProduct.price_;
}

string Product::getShopName()
{
    return shop_.getName();
}

string Product::getProductName()
{
    return this->name_;
}

int Product::getProductPrice()
{
    return this->price_;
}

bool Product::isValidProduct(const string product)
{
    return ErrorHandling::isValidField(product);
}

Product::~Product() { }
