#include <iostream>
using namespace std;

constexpr long double operator"" _ms(long double ms) {
    return ms / 1000.0; 
}

constexpr long double operator"" _s(long double s) {
    return s; 
}

constexpr long double operator"" _h(long double h) {
    return h * 3600.0; 
}


constexpr long double operator"" _cm(long double cm) {
    return cm / 100.0;
}

constexpr long double operator"" _m(long double m) {
    return m;
}

constexpr long double operator"" _km(long double km) {
    return km * 1000.0; 
}

/**
    Computes velocity in meters per second.
    @param distance  distance in meters
    @param time      time in seconds
    @return velocity in meters per second.
*/
double computeVelocity(double distance, double time){
    return distance / time;
}

int main(){
    cout << computeVelocity(100.0_m, 5.0_s) << endl;     // 20
    cout << computeVelocity(360.0_km, 2.0_h) << endl;    // 50
    cout << computeVelocity(3.6_km, 0.02_h) << endl;     // 50
    cout << computeVelocity(250.0_cm, 2.5_ms) << endl;   // 1000
    return 0;
}
