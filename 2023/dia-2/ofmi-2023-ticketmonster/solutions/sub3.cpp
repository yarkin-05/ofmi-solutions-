#include <iostream>
int main() {
  int N, B, R, L;
  std::cin >> N >> B >> R >> L;
  for (int i = 0; i < N; ++i) {
    int Di;
    std::cin >> Di;
    if (Di > L) {
      std::cout << L << "\n";
    } else {
      std::cout << Di << "\n";
    }
  }
  return 0;
}
