// RUN: %clam --crab-track=sing-mem --crab-dom=int --crab-inter --crab-check=assert "%s"  2>&1 | OutputCheck %s
// CHECK: ^1  Number of total safe checks$
extern int int_nd(void);
extern void __CRAB_assert(int);

void g(int x, int* p) {
  *p = x;
}

 

int f() {
  int x = 0;
  int* p = &x;
  g(1, p);
  return x;
}

 

int main(void) {
  int y = f();
  // __CRAB_assert(y == 1);
  __CRAB_assert(y >= 0 && y <= 1);
  return 0;
}
