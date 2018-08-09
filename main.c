#include <stdio.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 20
#define X WIDTH/2
#define Y HEIGHT/2
#define XMAX WIDTH-X-1
#define XMIN -(WIDTH-X)
#define YMAX HEIGHT-Y
#define YMIN -(HEIGHT-Y)+1

char grid[HEIGHT][WIDTH];
void printSine(float A,float B, float C,float D,float period);
int plot(int x, int y);
double transformSineX(float A,float B, float C,float D,float x);
void init_grid(void);
void show_grid(void);


int main()
{
    // TODO create CLI interface to read parameters of printSine from the user.
    // TODO refact code to make the size of the plotted area configurable
    // TODO make the size of the plotted area and the resolution of the function 
    // dynamic. When I change the ABCD parameters I want to see a complete period of sine on the screen
    // FYI: https://www.mathsisfun.com/sets/function-transformations.html
    printSine(1.0f,1.0f,0.0f,0.0f,1.0f);
    return(0);
}

void printSine(float A,float B, float C,float D,float period){
    float x,y;

    init_grid();
    for(x=-3.14159*period;x<=3.14159*period;x+=0.1)
    {
        y = transformSineX(A,B,C,D,x);
        plot(rintf(x*10),rintf(y*8));
    }
    show_grid();
}

/*
 * @param A:  is vertical stretch/compression
 *  |A| > 1 stretches 
 *  |A| < 1 compresses 
 *  A < 0 flips the graph upside down
 * @param B: is horizontal stretch/compression
 *  |B| > 1 compresses 
 *  |B| < 1 stretches 
 *  B < 0 flips the graph left-right
 * @param C: is horizontal shift
 *  C < 0 shifts to the right 
 *  C > 0 shifts to the left
 * @param D: is vertical shift
 *  D > 0 shifts upward 
 *  D < 0 shifts downward
 * @return the calculated value of y
 */
double transformSineX(
            float A, 
            float B, 
            float C, 
            float D,
            float x)
{
    return A*sin(B*(x+C))+D;
}

/* Set "pixel" at specific coordinates */
int plot(int x, int y)
{
    if( x > XMAX || x < XMIN || y > YMAX || y < YMIN )
        return(-1);

    grid[Y-y][X+x] = '*';
    return(1);
}

/* Initialize grid */
void init_grid(void)
{
    int x,y;

    for(y=0;y<HEIGHT;y++)
        for(x=0;x<WIDTH;x++)
            grid[y][x] = ' ';
    /* draw the axis */
    for(y=0;y<HEIGHT;y++)
        grid[y][X] = '|';
    for(x=0;x<WIDTH;x++)
        grid[Y][x] = '-';
    grid[Y][X] = '+';
}

/* display grid */
void show_grid(void)
{
    int x,y;

    for(y=0;y<HEIGHT;y++)
    {
        for(x=0;x<WIDTH;x++)
            putchar(grid[y][x]);
        putchar('\n');
    }
}