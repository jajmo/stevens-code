#include "main.hh"


/**
 * Split a string at a delimiter
 *
 * Precondition: None
 * Postcondition: The string is split, and a vector is returned
 *
 * @param const std::string &s The string to split
 * @param char delim The delimiter to split at
 * @return std::vector<std::string> The split string
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

/**
 * Split a string and put it into a vector
 *
 * Precondition: None
 * Postcondition: The string is split, and the vector is returned
 *
 * @param const std::string &s The string to split
 * @param char delim The delimiter
 * @param std::vector<std::string> &elems The vector to put the elements into
 * @return std::vector<std::string> The vector with the tokens
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
