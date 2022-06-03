#include <windows.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //recupere les dimensions de la fenêtre;
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        //glDisable(GL_SCISSOR_TEST);
        //glClearColor(0.f, 1.f, 1.f, 1.f);
        //glClear(GL_COLOR_BUFFER_BIT);

        //temps ecoule depuis le lancement de l'app
        float time = glfwGetTime();

        //matricde de la scene 
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, float(width) / float(height), 0.1f , 100.0f);
        // Necessite de lier avec glu32.lib
        // Include <GL/glu.h>

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(60.f * time, 0.f, 0.f, 1.f);
        //glTranslatef(time,time, time);
        //glScalef(time,time, time);

        //définir la taille du canvas
        glViewport(width / 2, height / 2, width / 2, height / 2);
        glEnable(GL_SCISSOR_TEST);
        glScissor(width / 2, height / 2, width / 2, height / 2);

        /* Render here */
        glClearColor(0.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_TRIANGLES);

        //attributs du 1er sommet
        glColor3f(1.0f, 0.f, 0.f);
        glVertex2f(0.0f, +0.5f);

        //attributs du 2eme sommet
        glColor3ub(0, 255, 0);
        float sommet2[2] = { -0.5f, -0.5f };
        glVertex2fv(sommet2);

        //attributs du 3eme sommet
        glColor3ub(0,0,255);
        glVertex3f(+0.5f, -0.5f, 0.0f);

        glEnd();


        //définir la taille du canvas
        glViewport(0, 0, width / 2, height / 2);
        glEnable(GL_SCISSOR_TEST);
        glScissor(0, 0, width / 2, height / 2);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //matricde de la scene 
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glRotatef(time * time, 0.f, 0.f, 1.f);
        //glTranslatef(time,time, time);
        //glScalef(time,time, time);

        /* Render here */
        glClearColor(0.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_TRIANGLES);

        //attributs du 1er sommet
        glColor3f(1.0f, 0.f, 0.f);
        glVertex2f(0.0f, +0.5f);

        //attributs du 2eme sommet
        glColor3ub(0, 255, 0);
        float sommet3[2] = { -0.5f, -0.5f };
        glVertex2fv(sommet3);

        //attributs du 3eme sommet
        glColor3ub(0, 0, 255);
        glVertex3f(+0.5f, -0.5f, 0.0f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}