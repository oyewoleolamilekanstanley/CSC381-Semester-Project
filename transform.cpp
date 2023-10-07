#include "transform.h"
#include <cmath>
#include <iostream>
#include <cmath>

Shape::Shape(size_t numPoints) {
    this->numberOfPoints = numPoints;
    this->points = new Point[numPoints];
    this->color = new float[3];
    this->drawHandler = nullptr;
}
Shape::~Shape() {
    delete[] this->points;
    delete[] this->color;
}

Point& Shape::operator[](size_t index) {
    return this->points[index];
}

void Shape::setColor(float red, float green, float blue) {
    this->color[0] = red;
    this->color[1] = green;
    this->color[2] = blue;
}

Point &Shape::getPoint(size_t index) {
    return this->points[index];
}

void Shape::setPoint(size_t index, Point pointt) {
    (*(this))[index] = pointt;
}

void Shape::setPoint(size_t index, float x, float y, float z) {
    (*this)[index].x = x;
    (*this)[index].y = y;
    (*this)[index].z = z;
}

size_t Shape::getNumberOfPoints() const {
    return this->numberOfPoints;
}

const float *Shape::getColor() {
    return this->color;
}

void Shape::setDrawHandler(void (*handler)(Shape &)) {
    this->drawHandler = handler;
}

void (*Shape::getDrawHandler()) (Shape&) {
    return this->drawHandler;
}

void scaleShape(Shape& shape, float scale) {
    size_t length = shape.getNumberOfPoints();

    for (size_t i = 0; i < length; i++) {
        shape[i].x *= scale;
        shape[i].y *= scale;
        shape[i].z *= scale;
    }
}

void translateShape(Shape& shape, Point& point) {
    size_t length = shape.getNumberOfPoints();

    for (size_t i = 0; i < length; i++) {
        shape[i].x += point.x;
        shape[i].y += point.y;
    }
}

void rotateShape(Shape& shape, float angle) {
    size_t length = shape.getNumberOfPoints();
    float x, y;

    for (size_t i = 0; i < length; i++) {
        x = shape[i].x;
        y = shape[i].y;

        shape[i].x = std::cos(angle) * x - std::sin(angle) * y;
        shape[i].y = sin(angle) * x + std::cos(angle) * y;
    }
}

void rotateShapeX(Shape& shape, float angle) {
    size_t length = shape.getNumberOfPoints();
    float y, z;
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (size_t i = 0; i < length; i++) {
        y = shape[i].y;
        z = shape[i].z;

        shape[i].y = cosA * y - sinA * z;
        shape[i].z = sinA * y + cosA * z;
    }
}
void rotateShapeY(Shape& shape, float angle) {
    size_t length = shape.getNumberOfPoints();
    float x, z;
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (size_t i = 0; i < length; i++) {
        x = shape[i].x;
        z = shape[i].z;

        shape[i].x = cosA * x - sinA * z;
        shape[i].z = sinA * x + cosA * z;
    }
}

void reflectShape(Shape& shape) {
    scaleShape(shape, -1.0f);
}

void horizontallyShearShape(Shape& shape, float scale) {
    size_t length = shape.getNumberOfPoints();

    // x1 = x + b * y

    for (size_t i = 0; i < length; i++) {
        shape[i].x = shape[i].x + scale * shape[i].y;
    }

}

void verticallyShearShape(Shape& shape, float scale) {
    size_t length = shape.getNumberOfPoints();
    // y1 = c * x + y

    for (size_t i = 0; i < length; i++) {
        shape[i].y = scale * shape[i].x + shape[i].y;
    }
}
