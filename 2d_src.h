#ifndef CSC381_2D_SRC_H
#define CSC381_2D_SRC_H

struct Point{
    float x, y, z;
};

struct Color {
    float Red, Green, Blue, Alpha;
};

struct Vertex {
    Point position;
    Color color;
};

class Shape {
private:
    unsigned int m_number_of_vertices;
    Vertex *m_vertices;

public:
    explicit Shape(unsigned int number_of_vertices);
    Shape(unsigned int number_of_vertices, const Vertex **vertices);
    ~Shape();
};


#endif //CSC381_2D_SRC_H
