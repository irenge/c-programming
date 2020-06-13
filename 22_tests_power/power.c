unsigned power(unsigned x, unsigned y) {
  int m;
  if ((y == 0) ||((x==0) && (y==0))) return 1;
  if (y % 2 == 0) {
    m = power(x, y / 2);
    return m * m;
  } else return x * power(x, y - 1);

}
