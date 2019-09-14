//
//  errorsType.h
//  Coursework#1
//
//  Created by Георгий Кашин on 16/05/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#ifndef errorsType_h
#define errorsType_h

class ErrorsType
{
public:
    
    enum class StringDataErrors
    {
        isFieldEmpty,
        incorrectKeyboardLayout,
        incorrectSymbols,
        incorrectRegister
    };
    
    enum class NumericDataErrors
    {
        nonInteger,
        nonPositive
    };
    
    enum class FileErrors
    {
        didNotOpen,
        isEmpty
    };
};

#endif /* errorsType_h */
