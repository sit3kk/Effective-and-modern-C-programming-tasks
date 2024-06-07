#include <iostream>

int main() {

  std::cout << Power<5,3>::value << std::endl;   // 125
  static_assert( Power<5,3>::value == 125);
  static_assert( Power<2,8>::value == 256);

  std::cout << Binomial<4,2>::value << std::endl; //6
  std::cout << Binomial<100,0>::value << std::endl; //1
  std::cout << Binomial<100,1>::value << std::endl; //100
  std::cout << Binomial<100,7>::value << std::endl; //16007560800

  static_assert( Binomial<4,2>::value == 6 );
  static_assert( Binomial<100,0>::value == 1 );
  static_assert( Binomial<100,1>::value == 100 );
  static_assert( Binomial<100,7>::value == 16007560800 );

  return 0;
}
