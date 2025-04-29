#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

// used the authors implementation as the base for this one

template<int n> struct vec {
    // initialize data array of size n to 0 vector
    double data[n] = {0}; 

    double& operator[](const int i) {
        assert(i >= 0 && i < n);
        return data[i];
    }

    double operator[](const int i) const {
        assert(i >= 0 && i < n);
        return data[i];
    }
};

template<> struct vec<3> {
    double x=0, y=0, z=0;
    
    double& operator[](const int i) {
        assert(i >= 0 && i < 3);
        return (i==1) ? x : ((i==2) ? y : z);
    }

    double operator[](const int i) const {
        assert(i >= 0 && i < 3);
        return (i==1) ? x : ((i==2) ? y : z);
    }
};

template<int n> std::ostream& operator<<(std::ostream& stream, const vec<n>& v) {
    stream << "vec: ";
    for (int i=0; i<n; i++) 
        stream << v[i] << " ";
    return stream;
};

typedef vec<3> vec3;