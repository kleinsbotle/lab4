//
// Created by efg on 20.04.19.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>
#include <vector>

#include "Timetable.h"

TEST(FindPath, Vertices_num) {
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/1.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    EXPECT_EQ(vertices->get_size(), 2);
}

TEST(FindPath, Adj_matrix){
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/1.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }
    EXPECT_EQ(matrix[0][1], 10);
}

TEST(FindPath, AdjMatr_diag){
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/1.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }
    EXPECT_EQ(matrix[0][0], matrix[1][1]);
}

TEST(FindPath, AdjMatr_NA){
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/2.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }

    EXPECT_EQ(matrix[2][0], 65535);
}

TEST(FindPath, MinPath_ChangePath){
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    unsigned short **min_paths;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/3.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }

    min_paths = find_min_paths(vertices->get_size(), matrix);

    EXPECT_TRUE(min_paths[0][4] < matrix[0][4]);
}

TEST(FindPath, MinPath_diag){
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    unsigned short **min_paths;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/3.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }

    min_paths = find_min_paths(vertices->get_size(), matrix);
    EXPECT_EQ(min_paths[1][1], 65535);
}

TEST(FindPath, MinPath_NotChangePath){
    std::vector<std::string> strings;
    auto *vertices = new List<std::string>;
    unsigned short **matrix;
    unsigned short **min_paths;
    strings = read_file("/home/efg/CLionProjects/lab4/test_input/3.txt");

    for (int i = 0; i < strings.size(); i++){
        parse(strings[i], vertices);
    }
    matrix = new unsigned short *[vertices->get_size()];
    empty_matrix(matrix, vertices->get_size());

    for (int i = 0; i < strings.size(); i++){
        make_matrix(strings[i], vertices, matrix);
    }

    min_paths = find_min_paths(vertices->get_size(), matrix);

    EXPECT_TRUE(min_paths[1][0] == matrix[1][0]);
}

