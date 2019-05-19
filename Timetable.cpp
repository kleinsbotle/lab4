//
// Created by efg on 22.04.19.
//

#include <fstream>
#include "Timetable.h"

std::vector<std::string> read_file(const std::string &FILEPATH){
    std::vector<std::string> strings;
    std::ifstream in(FILEPATH);
    if (in.is_open()){
        while (!in.eof()){
            std::string line;
            getline(in, line);
            if (!line.empty())
                strings.push_back(line);
        }
    } else
        throw std::runtime_error("Could not open file");
    in.close();
    return strings;
}

void make_matrix(std::string str, List<std::string> *vertices,  unsigned short **matrix){
    short flag = 0;
    unsigned short in1, in2;
    std::string v_name = "";
    std::string weight = "";
    for (int i = 0; i < str.size() + 1; i++){
        if (flag == 0){
            if (str[i] != ';')
                v_name += str[i];
            else{
                in1 = vertices->find(v_name);
                flag++;
                v_name = "";
            }
        }
        else if (flag == 1){
            if (str[i] != ';')
                v_name += str[i];
            else{
                in2 = vertices->find(v_name);
                flag++;
            }
        }
        else if (flag == 2){
            if (str[i] != ';')
                weight += str[i];
            else{
                if (weight != "N/A")
                    matrix[in1][in2] = std::stoi(weight);
                flag++;
                weight =  "";
            }
        }
        else{
            if (str[i] != '\0')
                weight += str[i];
            else{
                if (weight != "N/A")
                    matrix[in2][in1] = std::stoi(weight);
            }
        }
    }
}


void parse(std::string str, List<std::string> *vertex){
    std::string v_name = "";   //name of the vertex
    short flag = 0;
    unsigned i = 0;
    while (flag < 2){
        if (str[i] != ';')
            v_name += str[i];
        else{
            flag++;
            if (!vertex->is_in(v_name)){
                vertex->push_back(v_name);
            }
            v_name = "";
        }
        i++;
    }
}

unsigned short **find_min_paths(size_t v_num, unsigned short **matrix){
    //make a copy of adjacency matrix
    unsigned short **min_paths = new unsigned short *[v_num];
    for (int i = 0; i < v_num; i++)
        min_paths[i] = new unsigned short[v_num];
    for (int i = 0; i < v_num; i++){
        for (int j = 0; j < v_num; j++)
            min_paths[i][j] = matrix[i][j];
    }


    for (int k = 1; k < v_num; k++){
        for (int i = 0; i < v_num; i++){
            for (int j = 0; j < v_num; j++){
                if (((min_paths[i][k] + min_paths[k][j]) < min_paths[i][j]) && (i != j))
                    min_paths[i][j] = min_paths[i][k] + min_paths[k][j];
            }
        }
    }
    return min_paths;
}


void print_matrix(size_t v_num, unsigned short **matrix){
    for (int i = 0; i < v_num; i++){
        for (int j = 0; j < v_num; j++){
            if (matrix[i][j] == 65535)
                std::cout << "--" << ' ';
            else
                std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void empty_matrix(unsigned short **matr, size_t v_num){
    //make an empty matrix
    for (int i = 0; i < v_num; i++){
        matr[i] = new unsigned short[v_num];
    }
    //all elements are equal 65535 by default (max unsigned short value)
    //a[i][j] = 65535 means that there is no path from i to j
    for (int i = 0; i < v_num; i++){
        for (int j = 0; j < v_num; j++){
            matr[i][j] = 65535;
        }
    }
}

unsigned short min_path(std::string vertex1, std::string vertex2, unsigned short **matrix, List<std::string> *vertices){
    int in1, in2;
    in1 = vertices->find(vertex1);
    in2 = vertices->find(vertex2);
    if ((in1 == -1) || (in2 == -1))
        throw std::invalid_argument("Wrong input");
    unsigned short **min_paths = find_min_paths(vertices->get_size(), matrix);
    if (min_paths[in1][in2] == 65535)
        return 0;
    return min_paths[in1][in2];
}