//
//  products.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 11/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "errorHandling.hpp"
#include "shops.hpp"
#include "shop.hpp"

#include "product.hpp"
#include "products.hpp"

void Products::addProduct(Product &product)
{
    productsList.push_back(product);
}

Product& Products::operator[](int index)
{
    if (index < 0 || index > productsList.size())
    {
        throw invalid_argument("Index error");
    }
    else
    {
        return productsList[index];
    }
}

const string Products::showTheMostExpensiveProduct()
{
    Product maxProduct = productsList[0];
    for (int i = 1; i < productsList.size(); i++)
    {
        if (productsList[i].getProductName() != "" &&    // если хотя бы какое-то поле строки пустое, то игнорируем ее
            productsList[i].getShopName() != "" &&
            productsList[i].getProductPrice() != 0)
        {
            if (productsList[i] > maxProduct)
            {
                maxProduct = productsList[i];
            }
        }
    }
    
    if (maxProduct.getProductName() != "" &&  // если хотя бы одно поле нашего максимального объекта пустое, выводим ошибку
        maxProduct.getShopName() != "" &&
        maxProduct.getProductPrice() != 0)
    {
        return "The most expensive product: " + maxProduct.getProductName();
    }
    else
    {
        return "Failed to determine the most expensive product";
    }
}

void Products::sort()
{
    int size = static_cast<int>(productsList.size());
    
    for (int i = 0; i < size; ++i)
    {
        int minIndex = i;
        Product minValue = productsList[i];
        
        for (int j = i + 1; j < size; ++j)
        {
            if (minValue > productsList[j])
            {
                minIndex = j;
                minValue = productsList[j];
            }
        }
        
        productsList[minIndex] = productsList[i];
        productsList[i] = minValue;
    }
}

void operator>>(ifstream& input, Products &productsList)
{
    ErrorHandling handler;
    
    extern Shops shopsList;
    
    string handleString; // вся считываемая строка
    
    string productName;
    string productPrice;
    string shopName;
    
    while (!input.eof())
    {
        getline(input, handleString);
        
        if (handler.isValidString(handleString)) // проверяем строку на соответствие требованиям
        {
            handler.removeSpaces(handleString);
            
            productName = handleString.substr(0, handleString.find(';', 0)); // обработанную строку разбиваем на три поля
            handleString = handleString.substr(handleString.find(';', 0) + 1, handleString.find('\n', 0));
            
            shopName = handleString.substr(0, handleString.find(';', 0));
            handleString = handleString.substr(handleString.find(';', 0) + 1, handleString.find('\n', 0));
            
            productPrice = handleString.substr(0, handleString.find('\n', 0));
            
            shopsList.addShop(shopName);
            
            Product product(productName, Shop(shopName), stoi(productPrice));
            productsList.addProduct(product);
        }
    }
}

int Products::size()
{
    return static_cast<int>(productsList.size());
}

void operator<<(ofstream& output, Products &productsList)
{
    extern int maxProductLength;
    extern int maxShopLength;
    extern int maxPriceLength;
    
    string productNameColumn = "Product name";
    string shopNameColumn = "Shop name";
    string productPriceColumn = "Product price";
    
    string separator = "|";
    int separatorLength = static_cast<int>(separator.length());
    
    if (maxProductLength < productNameColumn.length()) { maxProductLength = static_cast<int>(productNameColumn.length()); }
    if (maxShopLength < shopNameColumn.length()) { maxShopLength = static_cast<int>(shopNameColumn.length()); }
    if (maxPriceLength + 7 < productPriceColumn.length()) { maxPriceLength = static_cast<int>(productPriceColumn.length()); }
    
    output << setw(maxProductLength) << left << productNameColumn << separator << setw(maxShopLength) << left << shopNameColumn << separator << setw(maxPriceLength) << left << productPriceColumn << separator << endl;
    
    int stringLength = maxProductLength + separatorLength +
    maxShopLength + separatorLength +
    maxPriceLength + separatorLength;
    
    for (int i = 0; i < stringLength - 1; i++)
    {
        if ((i != maxProductLength) && (i != maxShopLength + maxProductLength + separatorLength)) { output << "-"; }
        else { output << "+"; }
    }
    
    output << '|' << endl;
    
    for (int i = 0; i < productsList.size(); i++)
    {
        if (productsList[i].getProductName() != "" &&    // если хотя бы какое-то поле строки пустое, то в итоговый файл эта строка не попадает
            productsList[i].getShopName() != "" &&
            productsList[i].getProductPrice() != 0)
        {
            output << productsList[i];
        }
    }
    
    for (int i = 0; i < stringLength - 1; i++)
    {
        if ((i != maxProductLength) && (i != maxShopLength + maxProductLength + separatorLength)) { output << "_"; }
        else { output << separator; }
    }
    
    output << separator;
}
