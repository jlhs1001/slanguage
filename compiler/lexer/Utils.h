//
// Created by Liam Seewald on 3/4/24.
//

#ifndef SLANG_UTILS_H
#define SLANG_UTILS_H

#define IS_VALID_ID(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
#define IS_DIGIT(c) (c >= '0' && c <= '9')
#define IS_EOF(c) (c == '\0')

#endif //SLANG_UTILS_H
