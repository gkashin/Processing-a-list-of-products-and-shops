//
//  shops.hpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#ifndef shops_hpp
#define shops_hpp

#include <vector>

using namespace std;

class Shop;

class Shops
{
public:
    
    bool addShop(string name);
    int shopsCount();
    Shop operator[](int index);
    
    friend void operator<<(ofstream& output, Shops &shopsList);
    
private:
    
    vector<Shop> shopsList;
};

#endif /* shops_hpp */
