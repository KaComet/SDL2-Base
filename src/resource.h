#ifndef WELT_RESOURCE_H
#define WELT_RESOURCE_H

#include <iostream>
#include <string>
#include <SDL.h>

std::string getResourcePath(const std::string &subDir);

std::string getDelimitedContents(const std::string &input, char DelimitingChar, unsigned int start);

#endif //WELT_RESOURCE_H
