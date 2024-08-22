#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>


using namespace std;
#if 0
void insert_sorted(vector<string> &v,const string &word){
    const auto insert_pos(lower_bound(begin(v),end(v),word));
    v.insert(insert_pos,word);
}

#else
template<typename C,typename T>
void insert_sorted(C &v,const T &item){
    const auto insert_pos(lower_bound(begin(v),end(v),item));
    v.insert(insert_pos,item);
}
#endif

int main(){
    vector<string> v{"some","random","words","without","order","aaa","yyy"};

    assert(false==is_sorted(begin(v),end(v)));
    sort(begin(v),end(v));
    assert(true==is_sorted(begin(v),end(v)));

    insert_sorted(v,"foobar");
    insert_sorted(v,"zzz");

    for (const auto &w : v)
    {
        cout<<w<<" ";
    }
    cout<<endl;
    

}