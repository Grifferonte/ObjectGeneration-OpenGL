#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../common/GLShader.h"

GLShader g_BasicShader;


struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;
};

struct Vertex
{
    Vector2 position;
    Vector3 color;

    //float position[2];
    //float color[2];
} vertex;

GLuint VBO;

// (x,y)
static const Vertex triangle[] = {
    0.0f, 0.5f,
    0.0, 1.0, 0.0,//sommet #0

    -0.5f, -0.5f,
    1.0, 0.0, 1.0,//sommet #1

    0.5f, -0.5f,
    0.0, 1.0, 1.0,//sommet #2
};

bool Initialise()
{
    glewInit();
    g_BasicShader.LoadVertexShader("basic.vs");
    g_BasicShader.LoadFragmentShader("basic.fs");
    g_BasicShader.Create();

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData alloue et transfert 4 * 2 * 3 octets issus du tableau triangle[]
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 3, triangle, GL_STATIC_DRAW);
    // je recommande de reinitialiser les etats a la fin pour eviter les effets de bord
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}
void Terminate() {
    g_BasicShader.Destroy();
    glDeleteBuffers(1, &VBO);
}

void Render(GLFWwindow* window) {
    //recupere les dimensions de la fenêtre;
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    //temps ecoule depuis le lancement de l'app
    float time = glfwGetTime();

    // (x,y)
    //static const float triangle[] = {
    //    0.0f, 0.5f,
    //    0.0, 1.0, 0.0,//sommet #0

    //    -0.5f, -0.5f,
    //    1.0, 0.0, 1.0,//sommet #1

    //    0.5f, -0.5f,
    //    0.0, 1.0, 1.0,//sommet #2
    //};
 
    // etape a. A vous de recuperer/passer les variables width/height

    glViewport(0, 0, width, height);

    // etape b. Notez que glClearColor est un etat, donc persistant

    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // etape c. on specifie le shader program a utiliser

    auto basicProgram = g_BasicShader.GetProgram();
    glUseProgram(basicProgram);

    // etape d.

    const uint32_t stride = sizeof(float) * 5;
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, false, stride, triangle);
    int loc_position = glGetAttribLocation(basicProgram, "a_position");
    int loc_color = glGetAttribLocation(basicProgram, "a_color");
    glEnableVertexAttribArray(loc_position);
    glEnableVertexAttribArray(loc_color);
    //glVertexAttribPointer(loc_position, 2, GL_FLOAT, false, stride, triangle);
    //glVertexAttribPointer(loc_color, 3, GL_FLOAT, false, stride, triangle+2);
    glVertexAttribPointer(loc_position, 2, GL_FLOAT, false, stride, &triangle->position);
    glVertexAttribPointer(loc_color, 3, GL_FLOAT, false, stride, &triangle->color);

    // etape e.
    // etape f. dessin de triangles dont la definition provient d’un tableau
    // le rendu s’effectue ici en prenant 3 sommets a partir du debut du tableau (0)

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // on suppose que la phase d’echange des buffers front et back
    // le « swap buffers » est effectuee juste apres

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    //glEnableVertexAttribArray(0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    Initialise();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Terminate();


    glfwTerminate();
    return 0;
}


