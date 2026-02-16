struct P2d {
    double x, y;
};

double sumxy_p(const P2d* p) {
    return p->x + p->y;
}