//
// Created by efg on 22.04.19.
//

#ifndef LAB4_TIMETABLE_H
#define LAB4_TIMETABLE_H

#include <string>
#include <vector>
#include "List.h"

#pragma once

std::vector<std::string> read_file(const std::string &FILEPATH);
void parse(std::string str, List<std::string> *vertex);
void empty_matrix(unsigned short **matr, size_t v_num);
void make_matrix(std::string str, List<std::string> *vertices,  unsigned short **matrix);
void print_matrix(size_t v_num, unsigned short **matrix);
unsigned short **find_min_paths(size_t v_num, unsigned short **matrix);  //create minimal paths matrix
unsigned short min_path(std::string vertex1, std::string vertex2, unsigned short **matrix, List<std::string> *vertices);

#endif //LAB4_TIMETABLE_H
