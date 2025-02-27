    #include <glfw3.h>
    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>
    #include<iostream>
    #include<cmath>

    #define M_PI  3.1415f

    #define RED_COLOR      1.0f, 0.0f, 0.0f
    #define GREEN_COLOR    0.0f, 1.0f, 0.0f
    #define BLUE_COLOR     0.0f, 0.0f, 1.0f

    #define ORANGE_COLOR   1.0f, 0.5f, 0.0f
    #define SKY_BLUE_COLOR 0.0f, 1.0f, 1.0f
    #define YELLOW_COLOR   1.0f, 1.0f, 0.0f

    #define BLACK_COLOR    0.0f, 0.0f, 0.0f
    #define PINK_COLOR     1.0f, 0.7f, 0.7f
    #define PURPLE_COLOR   0.5f, 0.0f, 0.5f 

    #define BROWN_COLOR    0.647f, 0.165f, 0.165f
    #define GRAY_COLOR     0.5f, 0.5f, 0.5f
    #define GOLD_COLOR     1.0f, 0.843f, 0.0f

    #define WHITE_COLOR    1.0f, 1.0f, 1.0f
    #define BEIGE_COLOR    0.961f, 0.961f, 0.863f
    #define FUCHSIA_COLOR  1.0f, 0.0f, 1.0f

    float color[6][3] = { {RED_COLOR}, {GREEN_COLOR}, {BLUE_COLOR}, {ORANGE_COLOR}, {PINK_COLOR}, {FUCHSIA_COLOR} };

    GLfloat fPozycja_swiatla[4] = { 100.0f, 100.0f, 50.0f, 1.0f };
    GLfloat fSlabe_swiatlo[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat fMocne_swiatlo[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLfloat fMocne_swiatlo2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat fSlabe_swiatlo2[] = { 0.25f, 0.25f, 0.25f, 1.0f };


    GLfloat fPozycja_reflektora[4] = { 0.0f, -10.0f, -2.5f, 1.0f };
    GLfloat fKierunek_reflektora[4] = { 0.0f, 2.0f, 0.0f, 1.0f }; // kierunek w którym ma świecić reflektor

    float leftq = -16;
    float rightq = 16;
    float bottomq = -12;
    float topq = 10;
    float nearq = 7;  
    float farq = 30; 

    bool orto = false;

    float cameraAngleX = 35;
    float cameraAngleZ = 0;
    float cameraDistance = 10;

    float pozx = 0.0;
    float pozy = 0.5;
    float pozz = 0.0;

    #define LICZBA_OB_TEXTUR 22
    unsigned int obiektyTextur[LICZBA_OB_TEXTUR];
    unsigned int texture;
    const char* plikiTextur[LICZBA_OB_TEXTUR] = { "../textury/p1.jpg",
    "../textury/p2.jpg",
    "../textury/p4.jpg",
    "../textury/p3.jpg",
    "../textury/p5.jpg",
    "../textury/p5.jpg",
    "../textury/b1.jpg", 
    "../textury/b2.jpg",
    "../textury/a1.jpg",
    "../textury/a2.jpg",
    "../textury/a3.jpg",
    "../textury/a4.jpg",
    "../textury/a5.jpg",
    "../textury/a6.jpg",
    "../textury/l1.jpg",
    "../textury/l2.jpg",
    "../textury/l4.jpg",
    "../textury/l3.jpg",
    "../textury/l5.jpg",
    "../textury/d1.jpg" ,
    "../textury/d2.jpg",
    "../textury/d3.jpg" };

    using namespace std;

    bool perekl = true;

    void drawRectangularPrism(float length, float width, float height, GLuint* textureID) {
        float x = length / 2.0f;
        float y = width / 2.0f;
        float z = height / 2.0f;

        bool flag = textureID != nullptr;

        if (flag) {
            glColor3f(WHITE_COLOR);
            glBindTexture(GL_TEXTURE_2D, textureID[0]);
            glEnable(GL_TEXTURE_2D);
        }
        else {
            glDisable(GL_TEXTURE_2D);
        }
        glBegin(GL_QUADS);

        // Front face 

        if (flag) {}
        else { glColor3f(color[0][0], color[0][1], color[0][2]); }

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-x, y, z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-x, -y, z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, -y, z);
        glEnd();

        if (flag) glBindTexture(GL_TEXTURE_2D, textureID[1]);
        else glColor3f(color[1][0], color[1][1], color[1][2]);
        glBegin(GL_QUADS);
        // Back face 

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-x, y, -z);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, -z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, -y, -z);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-x, -y, -z);
        glEnd();
        // Left face 
        if (flag) glBindTexture(GL_TEXTURE_2D, textureID[2]);
        else glColor3f(color[2][0], color[2][1], color[2][2]);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-x, y, z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-x, y, -z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-x, -y, -z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-x, -y, z);
        glEnd();

        // Right face 
        if (flag) glBindTexture(GL_TEXTURE_2D, textureID[3]);
        else glColor3f(color[3][0], color[3][1], color[3][2]);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, -z);

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, -y, z);

        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, -y, -z);

        glEnd();

        // Top face 
        if (flag) glBindTexture(GL_TEXTURE_2D, textureID[4]);
        else glColor3f(color[4][0], color[4][1], color[4][2]);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, y, z);

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, -z);

        glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, y, -z);

        glEnd();
        // Bottom face
        if (flag) glBindTexture(GL_TEXTURE_2D, textureID[5]);
        else glColor3f(color[5][0], color[5][1], color[5][2]);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-x, -y, -z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, -y, -z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, -y, z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-x, -y, z);

        glEnd();
    }

    void drawTransformedRectangularPrism(
        float length, float width, float height,
        float centerX, float centerY, float centerZ, GLuint* texture = nullptr,
        float rotateX = 0, float rotateY = 0, float rotateZ = 0
    ) {

        glPushMatrix();

        // Translate to the specified center
        glTranslatef(centerX, centerY, centerZ);

        glRotatef(rotateX, 1.0, 0.0, 0.0);  // Rotate around the X-axis
        glRotatef(rotateY, 0.0, 1.0, 0.0);  // Rotate around the Y-axis
        glRotatef(rotateZ, 0.0, 0.0, 1.0);  // Rotate around the Z-axis

        // Draw the rectangular prism
        drawRectangularPrism(length, width, height, texture);

        glPopMatrix();
    }
    bool a = false;
    bool b = true;
    bool c = false;
    bool d = false;
    int x = 0;
    int liczba = 1;

    float k = 1.0f;
    float rotate = 0.05;

    int iCull = 0;
    int iOutline = 0;
    int iDepth = 0;
    int iClock = 0;
    int iFill = 0;

    float rotx = 0.0f;
    float roty = 0.0f;
    float rotz = 0.0f;

    int kll = 3;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_1:
                a = !a;
                break;
            case GLFW_KEY_2:
                b = !b;
                break;
            case GLFW_KEY_3:
                c = !c;
                break;

            case GLFW_KEY_4:
                d = !d;
                break;
            case GLFW_KEY_5:
                fPozycja_reflektora[0] += 1;
                break;
            case GLFW_KEY_6:
                fPozycja_reflektora[0] -= 1;
                break;

            case GLFW_KEY_7:
                fMocne_swiatlo2[0] += 0.5;
                fMocne_swiatlo2[1] += 0.5;
                fMocne_swiatlo2[2] += 0.5;
                fSlabe_swiatlo2[0] += 0.3;
                fSlabe_swiatlo2[1] += 0.3;
                fSlabe_swiatlo2[2] += 0.3;
                break;
            case GLFW_KEY_8:
                fMocne_swiatlo2[0] -= 0.5;
                fMocne_swiatlo2[1] -= 0.5;
                fMocne_swiatlo2[2] -= 0.5;
                fSlabe_swiatlo2[0] -= 0.3;
                fSlabe_swiatlo2[1] -= 0.3;
                fSlabe_swiatlo2[2] -= 0.3;
                break;

            case GLFW_KEY_F2:
                fMocne_swiatlo2[0] += 0.5;
                fMocne_swiatlo2[1] += 0.5;
                fSlabe_swiatlo2[0] += 0.3;
                fSlabe_swiatlo2[1] += 0.3;
                break;
            case GLFW_KEY_F3:
                fMocne_swiatlo2[0] -= 0.5;
                fMocne_swiatlo2[1] -= 0.5;
                fSlabe_swiatlo2[0] -= 0.3;
                fSlabe_swiatlo2[1] -= 0.3;
                break;
            case GLFW_KEY_N:
                --liczba;
                break;
            case GLFW_KEY_M:
                ++liczba;
                break;
            case  GLFW_KEY_RIGHT:
                if (perekl) ++pozx;
                else rotz += 5;
                break;
            case  GLFW_KEY_LEFT:
                if (perekl) --pozx;
                else rotz -= 5;
                break;
            case  GLFW_KEY_UP:
                if (perekl) ++pozz;
                else rotx += 5;
                break;
            case  GLFW_KEY_DOWN:
                if (perekl) --pozz;
                else rotx -= 5;
                break;
            case  GLFW_KEY_U:
                if (perekl) --pozy;
                else roty -= 5;
                break;
            case  GLFW_KEY_I:
                if (perekl) ++pozy;
                else roty += 5;
                break;
            case  GLFW_KEY_R:
                ::rotate = 0;
                break;
            case  GLFW_KEY_T:
                ::rotate += 0.05;
                break;

            case  GLFW_KEY_W:
                cameraAngleX += 5;
                break;
            case  GLFW_KEY_S:
                cameraAngleX -= 5;
                break;
            case  GLFW_KEY_A:
                cameraAngleZ += 5;
                break;
            case  GLFW_KEY_D:
                cameraAngleZ -= 5;
                break;

            case  GLFW_KEY_0:
                cameraDistance += 5;
                break;
            case  GLFW_KEY_9:
                cameraDistance -= 5;
                break;

            case  GLFW_KEY_L:
                k += 0.25f;
                if (k > 2.6) k = 2.5f;
                break;
            case  GLFW_KEY_K:
                k -= 0.25f;
                if (k < 0.2) k = 0.25f;
                break;

            case GLFW_KEY_Z:
                iCull = ~iCull;
                break;
            case GLFW_KEY_X:
                iDepth = ~iDepth;
                break;
            case GLFW_KEY_C:
                iOutline = ~iOutline;
                break;
            case GLFW_KEY_V:
                iFill = ~iFill;
                break;
            case GLFW_KEY_B:
                iClock = ~iClock;
                break;

            case GLFW_KEY_Q:
                orto = !orto;
                break;
            case GLFW_KEY_F1:
                perekl = !perekl;
                break;

            case GLFW_KEY_F4:
                ++kll;
                break;
            case GLFW_KEY_F5:
                --kll;
                break;
            }
        }
    }

    void Steve(float k = 1.0f) {

        float bodyLength = 1.1f * k, bodyWidth = 1.55f * k, bodyHeight = 1.0f * k;
        float headLength = bodyLength * 1.15f, headWidth = headLength, headHeight = bodyLength;
        float armLength = bodyLength * 0.5f, armWidth = bodyWidth, armHeight = bodyHeight;
        float legLength = bodyLength * 0.5f, legWidth = bodyWidth, legHeight = bodyHeight;

        glTranslatef(pozx * 1.75f * k, pozy * 1.75f * k + (k - 1) * 1.75, pozz * 1.75f * k);

        glRotatef(rotx, 1, 0, 0);
        glRotatef(roty, 0, 1, 0);
        glRotatef(rotz, 0, 0, 1);

        // Head
        GLuint head[6];
        copy(obiektyTextur, obiektyTextur + 6, head);
        drawTransformedRectangularPrism(headLength, headWidth, headHeight, 0.0f, (bodyWidth + headWidth) * 0.5f, 0.0f, head);
        // Body
        GLuint boadi[6];
        fill(boadi, boadi + 6, obiektyTextur[5]);
        boadi[0] = obiektyTextur[6];
        boadi[1] = obiektyTextur[7];
        drawTransformedRectangularPrism(bodyLength, bodyWidth, bodyHeight, 0.0f, 0.0f, 0.0f, boadi);
        // Left Arm
        GLuint arm[6];
        copy(obiektyTextur + 8, obiektyTextur + 14, arm);
        drawTransformedRectangularPrism(armLength, armWidth, armHeight, (bodyLength + armLength) * -0.5f, (bodyWidth - armWidth) * 0.5f, 0.0f, arm);
        // Right Arm
        drawTransformedRectangularPrism(armLength, armWidth, armHeight, (bodyLength + armLength) * 0.5f, (bodyWidth - armWidth) * 0.5f, 0.0f, arm);

        // Left Leg
        GLuint leg[6];
        copy(obiektyTextur + 14, obiektyTextur + 19, leg);
        leg[5] = obiektyTextur[18];
        drawTransformedRectangularPrism(legLength, legWidth, legHeight, (legLength - bodyLength) * 0.5f, (legWidth + bodyWidth) * -0.5f, 0.0f, leg);
        // Right Leg
        drawTransformedRectangularPrism(legLength, legWidth, legHeight, (bodyLength - legLength) * 0.5f, (legWidth + bodyWidth) * -0.5f, 0.0f, leg);

    }

    GLuint* Dirty() {
        GLuint* text = new GLuint[6];
        fill(text, text + 4, obiektyTextur[19]);

        text[4] = obiektyTextur[20];
        text[5] = obiektyTextur[21];
        return text;
    }

    void platform(int liczba = 3, float r = 1.0f) {
        GLuint* text = Dirty();
        float size = 1.75f * r;
        int max = 1 + 2 * liczba + kll - 3;
        for (int z = 0; z < liczba; ++z) {
            int ilocz = (max - z * 2);
            for (int j = 0; j < ilocz; ++j) {
                for (int i = 0; i < ilocz; ++i) {
                    drawTransformedRectangularPrism(size, size, size, size * (j - ilocz / 2), -2.0f - size * (1 - z) - (liczba - 2) * size, size * (i - ilocz / 2), text);
                }
            }
        }
        delete[] text;
    }

    void PrintInfo()
    {
        std::cout << "F1 zmienic glowny cel (translate/roteted)" << std::endl;

        std::cout << "GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN" << std::endl;

        std::cout << "N, N: powoduja zmiany liczby warstw piramidy" << std::endl;

        std::cout << "Q, W, E, A, S, D: powoduja zmiany kamery" << std::endl;
        std::cout << "1, 2, 3, 4, 5, 6 F2 F3: powoduja prace oswetlenia" << std::endl;

        std::cout << "Z: GL_CULL_FACE, X: GL_DEPTH_TEST, C: glPolygonMode(GL_BACK, GL_LINE) / glPolygonMode(GL_BACK, GL_FILL);, V: GL_FLAT, B: GL_CW, N: " << std::endl;

        std::cout << "Q: zmiana FRUSTRUM/ORTOGANAL" << std::endl;
    }


    void display(float size, int width, int height) {

        const double tt = glfwGetTime() / 100;
        const double aa = tt * 90.0;

        static double angle = 0;  // Угол вращения

        if (a) glDisable(GL_LIGHTING);
        else glEnable(GL_LIGHTING);

        if (b) glDisable(GL_LIGHT0);
        if (c) {
            glEnable(GL_LIGHT1); // włączenie światła 1
        }
        else {
            glDisable(GL_LIGHT1);
        }

        if (iCull)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        if (iDepth)
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);
        if (iOutline)
            glPolygonMode(GL_BACK, GL_LINE);
        else
            glPolygonMode(GL_BACK, GL_FILL);
        if (iFill)
            glShadeModel(GL_FLAT);
        else
            glShadeModel(GL_SMOOTH);
        if (iClock)
            glFrontFace(GL_CW);
        else
            glFrontFace(GL_CCW);

        glPushMatrix();

        glTranslatef(0.0f, 0.0f, -cameraDistance);
        glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(cameraAngleZ, 0.0f, 0.0f, 1.0f);


        glPushMatrix();
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        //glRotatef(aa * 60, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        Steve(k);
        glPopMatrix();

        platform(liczba, k);
        glPopMatrix();

        glPopMatrix();

        angle += ::rotate;
        if (angle > 360.0) {
            angle -= 360.0;
        }

    }

    const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };


    int main(void)
    {
        PrintInfo();
        if (!glfwInit()) {
            return -1;
        }

        GLFWwindow* window = glfwCreateWindow(800, 800, "Przykladowe Okno GLFW", NULL, NULL);

        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        glEnable(GL_TEXTURE_2D); // wlaczenie teksturowania
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glEnable(GL_DEPTH_TEST);

        glGenTextures(LICZBA_OB_TEXTUR, obiektyTextur); // wygenerowanie obiektów tekstur
        for (int i = 0; i < LICZBA_OB_TEXTUR; i++) {
            GLint iWidth, iHeight, nrChannels;
            glBindTexture(GL_TEXTURE_2D, obiektyTextur[i]); // dowiazanie obiektów tekstur
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            unsigned char* data = stbi_load(plikiTextur[i], &iWidth, &iHeight,
                &nrChannels, 0); // Zaladowanie tekstur
            //cout << iWidth << "\t" << obiektyTextur[i] << endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB,
                GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, obiektyTextur[2]);


        while (!glfwWindowShouldClose(window))
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Очищаем буфер цвета и глубины

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            //glOrtho(-width / 20.0, width / 20.0, -height / 20.0, height / 20.0, -10.0, 10.0);
            if (orto)
                glOrtho(-8.0, 8.0, -8.0, 8.0, -15.0, 15.0);
            else
                glFrustum(leftq, rightq, bottomq, topq, nearq, farq);


            glMatrixMode(GL_MODELVIEW);

            float squareSize = static_cast<float>(std::min(width, height)) * 0.2f;
            glfwSetKeyCallback(window, key_callback);

            glLightfv(GL_LIGHT0, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
            glLightfv(GL_LIGHT0, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
            glLightfv(GL_LIGHT0, GL_SPECULAR, fMocne_swiatlo); // światło odbite
            glLightfv(GL_LIGHT0, GL_POSITION, fPozycja_swiatla); // pozycja światła


            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f); // reflektor o kącie rozwarcia 60 stopni
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f); // stopień skupienia reflektora

            glLightfv(GL_LIGHT1, GL_AMBIENT, fSlabe_swiatlo2); // światło otoczenia
            glLightfv(GL_LIGHT1, GL_DIFFUSE, fMocne_swiatlo2); // światło rozproszenia
            glLightfv(GL_LIGHT1, GL_SPECULAR, fMocne_swiatlo2); // światło odbite
            glLightfv(GL_LIGHT1, GL_POSITION, fPozycja_reflektora); // pozycja światła
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, fKierunek_reflektora); // kierunek w który odwrócony jest reflektor




            display(squareSize, width, height);

            glEnable(GL_CULL_FACE);
            glClearColor(1, 1, 1, 1);
            glfwSwapBuffers(window);

            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LIGHTING);


            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }