char *p1, *p2, buf[100000];
#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)
inline int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (ch < 48 || ch > 57)
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (ch >= 48 && ch <= 57)
        x = x * 10 + ch - 48, ch = nc();
    return x * f;
}
inline void write(int x)
{
    if (x == 0)
    {
        putchar('0');
        return;
    }
    int len = 0, k1 = x, c[10005];
    if (k1 < 0)
        k1 = -k1, putchar('-');
    while (k1)
        c[len++] = k1 % 10 + '0', k1 /= 10;
    while (len--)
        putchar(c[len]);
}
