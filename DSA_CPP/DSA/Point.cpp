#include "Point.h"

int Point::num = 0;
Point::Point() : x(0), y(0) { num++; }
Point::Point(int a, int b) : x(a), y(b) { num++; }
Point::Point(Point &p) : x(p.x), y(p.y) { num++; }

void Point::print()
{
    printf("{%.1f, %.1f}", x, y);
}

double getLine(const Point *a, const Point *b)
{
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

void Tri::print()
{
    cout << "a = ";
    (*a).print();
    cout << ", b = ";
    (*b).print();
    cout << ", c = ";
    (*c).print();

    printf("\nab = %.2f, ac = %.2f, bc = %.2f\n", ab, ac, bc);
}

bool Tri::isTri()
{
    if (a->x == b->x && a->x == c->x)
        return false;
    if (a->y == b->y && a->y == c->y)
        return false;
    if ((ab + ac) > bc)
        return true;
    if ((ab + bc) > ac)
        return true;
    if ((bc + ac) > ab)
        return true;
    return false;
}

void Tri::forTri(Point *a, Point *b, Point *c)
{
    ab = getLine(a, b);
    ac = getLine(a, c);
    bc = getLine(b, c);
    cout << setiosflags(ios::boolalpha) << isTri() << endl;
    print();
}

Tri::Tri()
{
    int x, y;

    cin >> x >> y;
    a = new Point(x, y);
    cin >> x >> y;
    b = new Point(x, y);
    cin >> x >> y;
    c = new Point(x, y);

    forTri(a, b, c);
}

Tri::Tri(int ax, int ay, int bx, int by, int cx, int cy)
{
    a = new Point(ax, ay);
    b = new Point(bx, by);
    c = new Point(cx, cy);

    forTri(a, b, c);
}