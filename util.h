#pragma once

#include <string>
#include <functional>
#include <vector>

namespace util {

/**
 * itterate over each line in a file and call f with the line as input
 * 
 * @param file_name the name of the file
 * @param f the function to call for each line
 */
void for_each_line(std::string file_name, const std::function<void(const std::string&)>& f);

/**
 *  itterate over the lines of a file and call f every n lines with a vector of the last n lines
 *
 *  @param file_name the name of the file
 *  @param n the amout of lines to parse before callign f
 *  @param f the function to call every n lines
 */
void for_n_lines(std::string file_name, size_t n, const std::function<void(const std::vector<std::string>&)>& f);
}
