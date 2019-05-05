#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "List.h"
#include "Timetable.h"



int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int n = RUN_ALL_TESTS();

    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    unsigned short **min_paths;

    strings = read_file("/home/efg/CLionProjects/lab4/input.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    std::cout << std::endl << "List of vertices: ";
    std::cout << vertices;


    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }

    std::cout << std::endl << "Adjacency matrix: " << std::endl;
    print_matrix(vertices->get_size(), matrix);


    min_paths = find_min_paths(vertices->get_size(), matrix);
    std::cout << std::endl << "Shortest paths: " << std::endl;
    print_matrix(vertices->get_size(), min_paths);

    unsigned short res = min_path("Санкт-Петербург", "Хабаровск", matrix, vertices);
    std::cout << res;

    return n;
}






