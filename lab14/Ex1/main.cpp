import emcpp:Vector;
import <iostream>;

int main()
{
    using namespace emcpp;
    Vector<int, 100, SafePolicy> intVec;
    Vector<double, 100, SafePolicy> doubleVec;
    Vector<std::string, 100, SafePolicy> stringVec;

    std::cout << "Vector module loaded successfully.\n";
    return 0;
}
