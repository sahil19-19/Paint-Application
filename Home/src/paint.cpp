#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

int height, width;
void makeWindow()
{
    setcolor(2);
    setfillstyle(SOLID_FILL, 7);

    bar(30, 30, 110, 75);  // Save
    bar(150, 30, 250, 75); // line
    bar(300, 30, 400, 75); // circle
    bar(450, 30, 550, 75); // rectangle
    bar(600, 30, 700, 75); // triangle
    bar(900, 30, 1000, 75); // clear
    bar(30, 90, 110, 140);  // car
    setbkcolor(7);
    setcolor(0);
    outtextxy(50, 40, "Save");
    outtextxy(185, 40, "Line");
    outtextxy(330, 40, "Circle");
    outtextxy(470, 40, "Rectangle");
    outtextxy(620, 40, "Flood fill");
    outtextxy(925, 40, "Clear");
    outtextxy(50, 105, "Car");

    // colours
    for (int i = 0; i <= 15; i++)
    {
        setfillstyle(SOLID_FILL, i);
        bar(150 + i * 60, 100, 150 + i * 60 + 40, 140);
    }

    setfillstyle(SOLID_FILL, WHITE);
}

void whiteBG()
{
    setfillstyle(SOLID_FILL, 15);
    bar(0, 300, 1000, 1000);
}

void showPopup(int clr, char *msg)
{
    setfillstyle(SOLID_FILL, clr);
    bar(1100, 10, 1500, 150);
    outtextxy(1150, 70, msg);
}

void cFloodFill(int x, int y, int clr, int oc)
{
    if (getpixel(x, y) == oc)
    {
        putpixel(x, y, clr);
        cFloodFill(x, y + 1, clr, oc);
        cFloodFill(x + 1, y, clr, oc);
        cFloodFill(x, y - 1, clr, oc);
        cFloodFill(x - 1, y, clr, oc);
    }
}

void beginDrawing(int xcl, int ycl, int clr, char cmd)
{
    setcolor(clr);
    clearmouseclick(WM_LBUTTONUP);
    if (cmd == 'l')
    {
        showPopup(8, " FIRST POINT SELECTED ");
        int newx = -1, newy = -1;
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                newx = mousex();
                newy = mousey();
            }
        } while (newx == -1 && newy == -1);
        line(xcl, ycl, newx, newy);

        showPopup(8, " LINE ");
    }
    else if (cmd == 'c')
    {
        showPopup(8, " CENTRE SELECTED ");
        int newx = 0, newy = 0;
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                newx = mousex();
                newy = mousey();
            }
        } while (!(newx < 1090 && newx > 260 && newy < 890 && newy > 10));
        int r = sqrt((xcl - newx) * (xcl - newx) + (ycl - newy) * (ycl - newy));
        circle(xcl, ycl, r);
        circle(xcl, ycl, r - 1);

        showPopup(8, " CIRCLE ");
    }
    else if (cmd == 'r')
    {
        showPopup(8, " INITIAL POINT SELECTED ");
        int newx = 0, newy = 0;
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                newx = mousex();
                newy = mousey();
            }
        } while (!(newx < 1090 && newx > 260 && newy < 890 && newy > 10));
        rectangle(xcl, ycl, newx, newy);
        rectangle(xcl + 1, ycl + 1, newx - 1, newy - 1);

        showPopup(8, " RECTANGLE ");
    }
    else if (cmd == 't')
    {
        showPopup(8, " INITIAL POINT SELECTED ");
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                x1 = mousex();
                y1 = mousey();
            }
        } while (!(x1 < 1090 && x1 > 260 && y1 < 890 && y1 > 10));
        showPopup(8, " SECOND POINT SELECTED ");
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                x2 = mousex();
                y2 = mousey();
            }
        } while (!(x2 < 1090 && x2 > 260 && y2 < 890 && y2 > 10));
        line(xcl, ycl, x1, y1);
        line(xcl, ycl + 1, x1, y1 + 1);
        line(xcl - 1, ycl, x1 - 1, y1);
        line(x2, y2, xcl, ycl);
        line(x2, y2 + 1, xcl, ycl + 1);
        line(x2 - 1, y2, xcl - 1, ycl);
        line(x1, y1, x2, y2);
        line(x1, y1 + 1, x2, y2 + 1);
        line(x1 - 1, y1, x2 - 1, y2);
    }
    else if (cmd == 'f')
    {
        setfillstyle(SOLID_FILL, clr);
        int oc = getpixel(xcl, ycl);
        // floodfill(xcl, ycl, clr);

        // a custom flood fill function so that the user can select the colour of the boundary as well as the fill
        cFloodFill(xcl, ycl, clr, oc);

        // setfillstyle(SOLID_FILL, 8);
        // makeWindow();
    }
    clearmouseclick(WM_LBUTTONDOWN);
}

void handleMouse()
{
    int xcl = -1, ycl = -1, clr = 4;
    char cmd;
    clearmouseclick(WM_LBUTTONDOWN);
    while (1)
    {
        bool carb = 0;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            xcl = mousex();
            ycl = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if (xcl > 900 && xcl < 1000 && ycl > 30 && ycl < 70) // clear
            {
                setfillstyle(SOLID_FILL, 15);
                bar(0, 0, width, height);
                makeWindow();
                handleMouse();
            }
            if (xcl > 30 && xcl < 110 && ycl > 90 && ycl < 140) // car
            {
                int x = 100;
                int pg = 0;
                while (1)
                {
                    setactivepage(pg);
                    setvisualpage(1 - pg);
                    cleardevice();
                    setfillstyle(SOLID_FILL, 15);
                    bar(0, 0, width, height);
                    makeWindow();
                    showPopup(8, " LEFT/RIGHT TO MOVE\n ESCAPE to exit ");
                    for (int i = 0; i <= 10; i++)
                    {
                        rectangle(x + i - 50, 550 + i, x + 450 - i, 650 - i);
                        rectangle(x + i + 50, 450 + i, 350 + i + x, 550);
                        circle(x + 100, 650, 50 - i);
                        circle(x + 300, 650, 50 - i);
                    }
                    if (GetAsyncKeyState(VK_RIGHT))
                    {
                        x += 10;
                    }
                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        x -= 10;
                    }
                    else if (GetAsyncKeyState(VK_RBUTTON))
                    {
                        carb = 1;
                        break;
                    }
                    delay(10);
                    pg = 1 - pg;
                }
                if (carb)
                {
                    cleardevice();
                    makeWindow();
                }
            }
            if (ycl > 30 && ycl < 75)
            {
                if (xcl > 150 && xcl < 250)
                {
                    cmd = 'l';
                    showPopup(8, " Line ");
                }
                else if (xcl > 300 && xcl < 400)
                {
                    cmd = 'c';
                    showPopup(8, " Circle ");
                }
                else if (xcl > 450 && xcl < 550)
                {
                    cmd = 'r';
                    showPopup(8, " Rectangle ");
                }
                else if (xcl > 600 && xcl < 700)
                {
                    cmd = 'f';
                    showPopup(8, " Flood Fill ");
                }
                else if (xcl > 30 && xcl < 110)
                {
                    writeimagefile("img.jpeg");
                    showPopup(8, " Image saved ");
                    delay(500);
                }
            }

            // colours
            for (int i = 0; i <= 15; i++)
            {
                if (xcl > 150 + i * 60 && xcl < 150 + i * 60 + 40 && ycl > 100 && ycl < 140)
                {
                    clr = i;
                    setcolor(clr);
                    showPopup(clr, " Colour ");
                }
            }

            if (ycl > 300)
                beginDrawing(xcl, ycl, clr, cmd);
        }
    }
}

int main()
{
    int gd = DETECT, gm;                                                                                           // gd-> graphics driver -- integer that specifies the graphics driver to be used
    char data[] = "C:\\Program Files (x86)\\mingw-w64\\i686-8.1.0-posix-dwarf-rt_v6-rev0\\mingw32\\lib\\libbgi.a"; // path to driver

    height = GetSystemMetrics(SM_CYSCREEN);
    width = GetSystemMetrics(SM_CXSCREEN);
    // initgraph(&gd, &gm, data);

    initwindow(width, height, "project", -3, -3);

    setfillstyle(SOLID_FILL, 15);
    bar(0, 0, width, height);

    makeWindow();

    handleMouse();

    getch();
    closegraph();
    return 0;
}
