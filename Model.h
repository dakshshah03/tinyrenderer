#include <vector>
#include <string>
#include "vec.h"

class Model {
    std::vector<vec3> vertices = {};
    // every 3 items in this corresponds to 1 face 
    // Each vertex is 1 higher than its index in vertices
    std::vector<int> face_vertices = {};
    public:
        // create functions for loading the obj file
        int vertex_count;
        int face_count;
        Model(const std::string filename);
        vec3 getVert(const int n); // return nth vertex
        vec3 getVert(const int face, const int i); // return i \in {0,1,2} h vertex associated with a given face
};
