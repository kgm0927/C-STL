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
    // ������ ���� ���

    const auto result(divide_remainder(16, 3));

    cout << "16/3 is" << result.first << "with a remainder of" << result.second << '\n';


    // C++ 17 ���Ŀ� ���� ���


    cout << "�� ����� C++ 17 ���Ŀ� ���� ����̴�."<<endl<<endl;

    auto [fraction, remainder] = divide_remainder(16, 3);
    cout << "16/3 is" << fraction << "with a remainder of " << endl;





    vector<employee> employees{
        {20202020,"�����","role",500}
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

    tie(ignore, remainder2) = divide_remainder(16, 5);// �� ���� ���� //ignore�� �׳� �����ϴ� ���̴�.
    cout << "16%5 is" << remainder2 << '\n';


}