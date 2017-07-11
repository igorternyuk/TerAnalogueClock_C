#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define TITLE "TerAnalogClock"
#define WIDTH 400
#define HEIGHT 400
#define WINDOW_X (1366 - 400) / 2
#define WINDOW_Y (768 - 400) / 2
#define HOUR_HAND_LEN 200
#define MINUTE_HAND_LEN 320
#define SECOND_HAND_LEN 350
#define SCALE_MARK_LEN 30
#ifndef M_PI
#define M_PI     3.14159265358979323846
#endif

char *numbers[12] = {"XII\0", "I\0", "II\0", "III\0", "IV\0", "V\0", "VI\0", "VII\0",
                     "VIII\0", "IX\0", "X\0", "XI\0"};
void display();
void timer();
void drawWord(char *word, float x_, float y_, float step, int red, int green, int blue);

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(WINDOW_X, WINDOW_Y);
    glutCreateWindow(TITLE);
    glClearColor(0, 0, 72.0 / 255, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -400, 400, -400, 400);
    glutDisplayFunc(display);
    timer();
    glutMainLoop();
    return 0;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0);
    glBegin(GL_LINES);
    for(int i = 0; i < 12; ++i){
        float x = sin(2 * M_PI / 12 * i);
        float y = cos(2 * M_PI / 12 * i);
        glVertex2f(WIDTH * x, HEIGHT * y);
        glVertex2f((WIDTH - SCALE_MARK_LEN) * x, (WIDTH - SCALE_MARK_LEN) * y);
    }
    //Numbers

    // XII
    // get current time now
    time_t t = time(0);
    struct tm  *now = localtime(&t);
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;


    //Hour hand

    float x = HOUR_HAND_LEN * sin(2 * M_PI * (hour * 60 + min) / 12 / 60);
    float y = HOUR_HAND_LEN * cos(2 * M_PI * (hour * 60 + min) / 12 / 60);
    glVertex2f(0, 0);
    glVertex2f(x, y);

    //Minute hand

    x = MINUTE_HAND_LEN * sin(2 * M_PI * min / 60);
    y = MINUTE_HAND_LEN * cos(2 * M_PI * min / 60);
    glVertex2f(0, 0);
    glVertex2f(x, y);

    //Second hand

    x = SECOND_HAND_LEN * sin(2 * M_PI * sec / 60);
    y = SECOND_HAND_LEN * cos(2 * M_PI * sec / 60);

    glVertex2f(0, 0);
    glVertex2f(x, y);
    glEnd();

    for(int i = 0; i < 12; ++i)
    {
        float x = 320 * sin(2 * M_PI / 12 * i);
        float y = 320 * cos(2 * M_PI / 12 * i);
        drawWord(numbers[i], (i < 6) ? x - 40 : x, y, 30, 255, 255, 0);
    }
    drawWord("CLOCK\0", -120, 100, 50, 255, 255, 0);
    glutSwapBuffers();
}

void drawWord(char *word, float x_, float y_, float step, int red, int green, int blue)
{
    if(red < 0) red = 0;
    if(red > 255) red = 255;
    if(green < 0) green = 0;
    if(green > 255) green = 255;
    if(blue < 0) blue = 0;
    if(blue > 255) blue = 255;
    glColor3f(red / 255.f, green / 255.f, blue / 255.f);
    for(int i = 0; i < strlen(word); ++i)
    {
        glRasterPos2f(x_ + i * step, y_);
        char ch = word[i];
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)ch);
    }

}

void timer(){
    display();
    glutTimerFunc(10, timer, 0);
}
