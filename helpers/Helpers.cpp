#include <algorithm>
#include "Helpers.h"

std::vector<char*> Helpers::splitString(char* target, char* separator) {
    std::vector<char*> results;

    char *current;
    current = std::strtok(target, separator);

    while (current != NULL) {
        results.push_back(current);
        current = std::strtok(NULL, separator);
    }

    return results;
}