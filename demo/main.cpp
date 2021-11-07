#include <myptr.hpp>


int main() {
  SharedPtr<int> p1(new int(9));
  std::cout << "p1.use_count " << p1.use_count() << "\n";
  std::cout << "bool(p1) " << (bool(p1) ? "true" : "false") << "\n\n";

  SharedPtr<int> p2(new int(10));
  std::cout << "p2.use_count " << p2.use_count() << "\n";
  std::cout << "bool(p2) " << (bool (p2) ? "true" : "false") << "\n\n";

  std::cout << "===================\n";
  SharedPtr<int> p3(p1);
  std::cout << "p1.use_count " << p3.use_count() << "\n";
  std::cout << "bool(p3) " << (bool (p3) ? "true" : "false") << "\n\n";

  std::cout << "p2.use_count " << p2.use_count() << "\n";
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << "\n\n";

  std::cout << "p3.use_count " << p3.use_count() << "\n";
  std::cout << "bool(p3) " << (bool(p3) ? "true" : "false") << "\n\n";

  std::cout << "===================\n";

  p2.swap(p1);
  std::cout << "p1.use_count " << p1.use_count() << "\n";
  std::cout << "bool(p1) " << (bool(p1) ? "true" : "false") << "\n\n";

  std::cout << "p2.use_count " << p2.use_count() << "\n";
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << "\n\n";

  p3 = p2;
  std::cout << "p3.use_count " << p3.use_count() << "\n";
  std::cout << "bool(p3) " << (bool(p3) ? "true" : "false") << "\n\n";

  std::cout << "p2.use_count " << p2.use_count() << "\n";
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << "\n\n";

}
