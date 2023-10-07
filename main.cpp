#include <cmath>
#include <iostream>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include <string>
#include <cmath>
#include <ctime>
#include <random>
#include "transform.h"


#define WIDTH 750
#define HEIGHT 600

float rrand() {
    return (float) rand()/RAND_MAX;
}

Shape *createPolygon(size_t points) {
    auto *polygon = new Shape(points);

    const float radius = 0.5f;

    for (int i = 0; i < points; i++) {
        float theta = 2.0f * (float)M_PI * float(i) / float(points); // Calculate angle for each vertex
        float x = radius * std::cos(theta);
        float y = radius * std::sin(theta);

        (*polygon)[i].x = x;
        (*polygon)[i].y = y;
    }

    polygon->setColor(rrand(), rrand(), rrand());

    return polygon;
}

void windowResize(GLFWwindow *window, int width, int height) {

    // 800*(x+4)/8, 600*(3-y)/6
    // width * (x + 4) / 8, heigth * (3 - y) / 6
    glViewport(0, 0, width, height);
}

void drawPolygon(Shape& shape)
{
    size_t points = shape.getNumberOfPoints();

    if (points < 1) {
        return;
    }

    const float *color = shape.getColor();

    glColor3f(color[0], color[1], color[2]);

    /* Draw a Polygon */
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < points; i++)
    {
        glVertex2f(shape[i].x, shape[i].y);
    }
    glEnd();
}

void drawShapes(Shape **shapes, int number, void (*handler)(Shape&))
{
    if (shapes == nullptr)
        return;

    for (int i = 0; i < number; i++)
    {
        handler(*(shapes[i]));
    }
}

void deleteShapes(Shape **shapes, int number)
{
    for (int i = 0; i < number; i++)
    {
        delete shapes[i];
    }
}

int main() {
    std::cout << "Hello Opengl" << std::endl;

    GLFWwindow *window;

    if (!glfwInit()) {
        std::cerr << "Error Initializing GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    window = glfwCreateWindow(
            WIDTH,
            HEIGHT,
            "2D Transformation - CSC 381 Project",
            nullptr, nullptr
    );

    if (!window) {
        std::cerr << "Error Creating Window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, WIDTH, HEIGHT);

    srand( (unsigned)time( nullptr ) );


    Shape* quad = createPolygon(4);

    float rate = 0.0002;

    Shape *polygonsOnScreen[12];
    int p_count = 1;

    Shape *currentShape = quad;
    polygonsOnScreen[0] = quad;
    int currentIndex = 0;


    float lastpress = 0;
    float frameCount = 0;


    std::unordered_map< int, int > polygonKeyMap;
    polygonKeyMap.insert({GLFW_KEY_3, 3});
    polygonKeyMap.insert({GLFW_KEY_4, 4});
    polygonKeyMap.insert({GLFW_KEY_5, 5});
    polygonKeyMap.insert({GLFW_KEY_6, 6});
    polygonKeyMap.insert({GLFW_KEY_7, 7});
    polygonKeyMap.insert({GLFW_KEY_8, 8});
    polygonKeyMap.insert({GLFW_KEY_9, 9});
    polygonKeyMap.insert({GLFW_KEY_0, 10});

    while (!glfwWindowShouldClose(window)) {
        frameCount += 0.001;

        glfwSetFramebufferSizeCallback(window, windowResize);
        glClearColor(0.1f, 0.5f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawShapes(polygonsOnScreen, p_count, drawPolygon);

        // Spawn Shapes
        for (const auto& pair : polygonKeyMap) {
            if (glfwGetKey(window, pair.first)) {
                if ((frameCount - lastpress) > 0.10 && p_count < 12)
                {
                    // Create Polygon
                    Shape * t = createPolygon(pair.second);
                    polygonsOnScreen[p_count++] = t;
                    lastpress = frameCount;
                }
            }
        }

        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            if ((frameCount - lastpress) > 0.10 && (currentIndex < p_count - 1))
            {
                // Select next shape on screen
                currentIndex++;
                currentShape = polygonsOnScreen[currentIndex];
                lastpress = frameCount;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            if ((frameCount - lastpress) > 0.10 && (currentIndex > 0))
            {
                // Select previous shape on screen
                currentIndex--;
                currentShape = polygonsOnScreen[currentIndex];
                lastpress = frameCount;
            }
        }

        // Transformations
        int moveUp = glfwGetKey(window, GLFW_KEY_W); // Moving Shape Up
        if (moveUp == GLFW_PRESS)
        {
            Point p = {0.0f, rate};
            translateShape(*currentShape, p);
        }

        int moveDown = glfwGetKey(window, GLFW_KEY_S);
        if (moveDown == GLFW_PRESS)
        {
            Point p = {0.0f, -rate};
            translateShape(*currentShape, p);
        }

        int moveLeft = glfwGetKey(window, GLFW_KEY_A);
        if (moveLeft == GLFW_PRESS)
        {
            Point p = {-rate, 0.0f};
            translateShape(*currentShape, p);
        }

        int moveRight = glfwGetKey(window, GLFW_KEY_D);
        if (moveRight == GLFW_PRESS)
        {
            Point p = {rate, 0.0f};
            translateShape(*currentShape, p);
        }

        int changeRate = glfwGetKey(window, GLFW_KEY_E);
        if (changeRate == GLFW_PRESS)
        {
            rate *= 1.05;
        }

        changeRate = glfwGetKey(window, GLFW_KEY_Q);
        if (changeRate == GLFW_PRESS)
        {
            rate /= 1.05;
        }

        int scaleUP = glfwGetKey(window, GLFW_KEY_UP);
        if (scaleUP == GLFW_PRESS)
        {
            verticallyShearShape(*currentShape, rate);
        }

        int scaleDOWN = glfwGetKey(window, GLFW_KEY_DOWN);
        if (scaleDOWN == GLFW_PRESS)
        {
            verticallyShearShape(*currentShape, -rate);
        }


        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            horizontallyShearShape(*currentShape, rate);
        }


        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            horizontallyShearShape(*currentShape, -rate);
        }


        if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        {
            scaleShape(*currentShape, 1 + rate);
        }


        if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        {
            scaleShape(*currentShape, 1 - rate);
        }

        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        {
            rotateShape(*currentShape, rate);
        }

        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        {
            rotateShape(*currentShape, -rate);
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            if ((frameCount - lastpress) > 2)
            {
                reflectShape(*currentShape);
            }
        }


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    deleteShapes(polygonsOnScreen, p_count);


    glfwTerminate();

    return EXIT_SUCCESS;
}
