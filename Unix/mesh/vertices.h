#pragma once
#include <vector>

struct Vertices {
    std::vector<float> data;
    int stride;

    Vertices(int stride = 3)
        : stride(stride) {}

    size_t vertexCount() const {
        return data.size() / stride;
    }
};
