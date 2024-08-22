#include <iostream>
#include <vector>

template <typename T>
class addable
{
private:
    T val;
public:
    addable(T v):val{v} {}
    // C++ 11
    #if 0
    template<typename U>
    std::enable_if_t<!std::is_same<T,std::vector<U>>::value,T>
    T add(U x)const{
        return val+x;
    }

    template<typename U>
    std::enable_if_t<std::is_same<T,std::vector<U>>::value,std::vector<U>>
    add(U x) const{
        auto copy(val);
        for (auto &n : copy)
        {
            n+=x;
        }
        return copy;
    }
    
    #else
    // the C++17 way
    template <typename U>
    T add(U x) {
    if constexpr(std::is_same_v<T,std::vector<U>>)
    {    auto copy(val); // 벡터 멤버의 사본을 구한다.
        for (auto &&n : copy)
        {
            n+=x;
        }
        return copy;
        }else{
            return val+x;
        }
        
    }
    #endif
};


int main(){
    addable<int> {1}.add(2);                    // 3이 된다.
    addable<float> {1.0}.add(2);                // 3.0이 된다.
    addable<std::string>{"aa"}.add("bb");       // "aabb"가 된다.

    std::vector<int> v {1,2,3};
    addable<std::vector<int>> {v}.add(10);
    // std::vector<int>{11,12,13}이 된다.

    std::vector<std::string> sv {"a","b","c"};
    addable<std::vector<std::string>>{sv}.add(std::string{"z"});
    // {"az","bz","cz"}이 된다.
}