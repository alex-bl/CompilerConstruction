/* Generates a diamond pattern */

void main() {
  
  int n;
  int space;
  n = 10;
  space = n - 1;
   
  int k;
  int c;
  k = 1;
  while (k <= n) {
    c = 1;
    while (c <= space) {
      print(" ");
      c = c + 1;
    }
    space = space - 1;
    c = 1;
    while (c <= space) {
      print("*");
      c = c + 1;
    }
    print("\n");
    k = k + 1;
  }

  space = 1;

  k = 1;
  while (k <= n) {
    c = 1;
    while (c <= space) {
      print(" ");
      c = c + 1;
    }
    space = space + 1;
    c = 1;
    while (c <= 2*(n-k)-1) {
      print("*");
      c = c + 1;
    }
    print("\n");
    k = k + 1;
  }
}
