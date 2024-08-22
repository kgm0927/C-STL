#include <iostream>
#include <cstdio>
#include <map>
#include <string>

using namespace std;


// c++17 이전

template <typename T>
void print_charcount_cpp11(const T& map,char c){
    const auto itr(map.find(c));
    if (itr!=map.end())
    {
        cout<<"There are"<<itr->second<<" "<<c<<" character"<<"\n";
        // itr은 유효하며, 접근이 가능하다.
    }
    else{
        cout<<"there are"<<0<<" "<<c<<" character"<<"\n";
        // itr이 유효하며, 접근할 수 있지만 사용이 가능하다.
    }
    // 여전히 itr에 접근이 가능하다.
    
}

// C++17

template <typename T>
void print_charcount_cpp17(const T& map,char c){
    if(const auto itr(map.find(c)); itr!=map.end()){
        cout<<"There are"<<itr->second<<" "<<c<<"characters."<<endl;
    }
    else
    {
        cout<<"There are "<<0<<" "<<c<<"charcters."<<endl;
    }
    // cpp11과 다르게 더 이상 접근할 수 없다.
    
}

int main(){
    map<char,size_t> character_map{{'a',10},{'b',20},{'c',30}};

    print_charcount_cpp11(character_map,'a');
    print_charcount_cpp11(character_map,'c');

    print_charcount_cpp17(character_map,'a');
    print_charcount_cpp17(character_map,'c');
}