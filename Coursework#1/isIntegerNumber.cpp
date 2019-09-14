//
//  isIntegerNumber.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <string>

#include "isIntegerNumber.hpp"

bool isIntegerNumber(const string str) // метод, проверяющий, содержится ли в строке целое число или нет
{
    int number = atoi(str.c_str());
    return str.length() == to_string(number).length();
}
