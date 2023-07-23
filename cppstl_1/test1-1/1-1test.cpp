#include <iostream>
#include <vector>
#include <map>
using namespace std;


pair<int, int> divide_remainder(int dividend, int divisor) {
    int ans = dividend / divisor;
    int rest = dividend % divisor;

    return std::make_pair(ans, rest);
}




struct employee {
    unsigned id;
    std::string name;
    std::string role;
    unsigned salary;
};



map<string, size_t> animal_population{
    {"humans", 700000000},
    { "chickens",1098765456790 },
    { "camels",24246291 },
    { "sheep",1086881528 },
};








int main() {
    // 이전에 쓰던 방법

    const auto result(divide_remainder(16, 3));

    cout << "16/3 is" << result.first << "with a remainder of" << result.second << '\n';


    // C++ 17 이후에 쓰는 방법


    cout << "이 방법은 C++ 17 이후에 쓰는 방식이다."<<endl<<endl;

    auto [fraction, remainder] = divide_remainder(16, 3);
    cout << "16/3 is" << fraction << "with a remainder of " << endl;





    vector<employee> employees{
        {20202020,"김근육","role",500}
    };


    for (const auto& [id, name, role, salary] : employees)
    {
        cout << "Name: " << name << "Role: " << role << "Salary: " << salary << "\n";
    }


    for (const auto& [species, count] : animal_population) {
        cout << "There are" << count << " " << species << " on this planet \n";
    }
    // 33.page

    int remainder2;

    tie(ignore, remainder2) = divide_remainder(16, 5);// 두 개를 묶음 //ignore은 그냥 무시하는 값이다.
    cout << "16%5 is" << remainder2 << '\n';


}