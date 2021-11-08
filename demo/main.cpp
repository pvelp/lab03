#include <myptr.hpp>


int main() {
  SharedPtr<int> p1(new int(12));
  std::cout << "p1.use_count " << p1.use_count() << std::endl;
  std::cout << "bool(p1) " << (bool(p1) ? "true" : "false") << std::endl;

  SharedPtr<int> p2(new int(10));
  std::cout << "p2.use_count " << p2.use_count() << std::endl;
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << std::endl;

  std::cout << "===================\n";
  SharedPtr<int> p3(p1);
  std::cout << "p1.use_count " << p3.use_count() << std::endl;
  std::cout << "bool(p3) " << (bool(p3) ? "true" : "false") << std::endl;

  std::cout << "p2.use_count " << p2.use_count() << "\n";
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << std::endl;

  std::cout << "p3.use_count " << p3.use_count() << "\n";
  std::cout << "bool(p3) " << (bool(p3) ? "true" : "false") << std::endl;

  std::cout << "===================\n";

  p2.mswap(p1);
  std::cout << "p1.use_count " << p1.use_count() << std::endl;
  std::cout << "bool(p1) " << (bool(p1) ? "true" : "false") << std::endl;

  std::cout << "p2.use_count " << p2.use_count() << "\n";
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << std::endl;

  std::cout << "===================\n";

  p3 = p2;
  std::cout << "p3.use_count " << p3.use_count() << "\n";
  std::cout << "bool(p3) " << (bool(p3) ? "true" : "false") << std::endl;

  std::cout << "p2.use_count " << p2.use_count() << std::endl;
  std::cout << "bool(p2) " << (bool(p2) ? "true" : "false") << std::endl;

  std::cout << "===================\n";
  int* p4 = new int(1);
  SharedPtr<int> p5(nullptr);
  p5.reset(p4);
  std::cout << "p5.use_count " << p5.use_count() << std::endl;
  std::cout << "bool(p5) " << (bool(p5) ? "true" : "false") << std::endl;

  std::cout << p5.operator->() << std::endl;
  std::cout << p5.get() << std::endl;

}
