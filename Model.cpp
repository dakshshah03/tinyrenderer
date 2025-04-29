#include <fstream>
#include <sstream>
#include "Model.h"

Model::Model(const std::string fname) {
    std::ifstream file;
    std::string line;
    file.open(fname);
    char tmp;
    char del = '/';
    int token_to_int;
    std::string token;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        if(line.compare(0, 2, "v ") == 0) {
            iss >> tmp; // dumps the v
            vec3 vertex;

            for(int i : {0,1,2})
                iss >> vertex[i];

            vertices.push_back(vertex);
            vertex_count += 1;
        } else if(line.compare(0, 2, "f ") == 0) {
            iss >> tmp; // dumps the f

            for(int i : {0,1,2}) {
                std::getline(iss, token, del);
                token_to_int = std::stoi(token) - 1;        // subtracts 1 to match index of vertex array
                face_vertices.push_back(token_to_int);
            }
            face_count += 1;
        }
    }
}

vec3 Model::getVert(const int n) {
    return vertices[n];
}

vec3 Model::getVert(const int f, const int i) {
    return vertices[face_vertices[f * 3 + i]];
}
