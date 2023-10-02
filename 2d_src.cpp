#include "2d_src.h"

Shape::Shape(unsigned int number_of_vertices): m_number_of_vertices{number_of_vertices} {
    m_vertices = new Vertex[number_of_vertices];
}

Shape::Shape(unsigned int number_of_vertices, const Vertex **vertices): Shape(number_of_vertices) {
    for (unsigned int i = 0; i < number_of_vertices; i++) {
        *(m_vertices + i) = *(*(vertices) + i);
    }
}

Shape::~Shape() {
    delete[] m_vertices;
}
