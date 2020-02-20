#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;          ///Random
    x=(x^(x>>30))*0xbf58476d1ce4e5b9; ///Random
    x=(x^(x>>27))*0x94d049bb133111eb; ///Random
    return x^(x>>31);
    }
  const uint64_t FIXED_RANDOM = chrono::
    steady_clock::now().time_since_epoch().count();
  size_t operator()(uint64_t x) const {
    return splitmix64(x + FIXED_RANDOM);
  }
  size_t operator()(pair<int, int> x) const {
    return splitmix64((uint64_t(x.first)<<32) +
           x.second + FIXED_RANDOM);
  }
};
gp_hash_table<pair<int,int>,int,custom_hash> ht;
