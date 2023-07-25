#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


//
//
// 
// ����ü ������ ���ε��� �°� pair�� tuple, �Ǵ� ����ü�� �� ��� ������ �����ϴ� �����
// ���ο� if�� switch ������ ���� �ʱ�ȭ �ɷ����� ���� ��� ������ �����ϰ��� �Ѵ�.
// 
// ���ø� Ŭ���� �ν��Ͻ��� ��Ȯ�� ������ ���� ������ ���ڿ��� �߷��ϰ� �ȴ�. �׸��� ���ø�
// Ŭ������ ���� �ٸ� Ư��ȭ�� ������ �ٸ� �ڵ带 �������� constexpr-if�� ���� ǥ���� ��
// �ִ�. ���ø� �Լ����� ���� �Ķ���� ������ �ٷ�� �� ���� ���ο� 'ǥ����(fold expression)'
// �� ���� ��������. ������ �������� �Լ������� �����ߴ� �ζ��� ���� ���� ����� ���� �߰���
// ���п� ��� ���� ���̺귯���� ���������� ���� ������ ���� ��ü�� �����ϱ� ��������.
// 
// 
// 
//			- �������� �� ��ȯ���� Ǯ�� ���� ����ü ������ ���ε� ���
// 
// C++ 17 ���ý� ����(syntactic sugar)�� �ڵ�ȭ Ÿ�� �߷��� ���յ� ���ο� '����ü ������
// ���ε�'(structured bindings)����� �߰��ƴ�. �̴� 'pair'�̳� 'tuple', �Ǵ� ����ü�κ���
// ���� ������ ���� ���� �Ҵ��� �� �ְ� �� �ش�. �ٸ� ���α׷��� ������ '����ŷ(unpacking)'
// �̶�� �Ѵ�.
// 
// 
// 
// 
//



//�켱 C++17 �������� ��� �ߴ��� ���캻��. �׸��� �� ���Ŀ��� ��� �ϴ��� ���캸�ڴ�.
// 
//  * std::pair�� �� ���� ���� ����: ����(dividend)�� ����(divisor) �Ķ���͸� ������,
//	�м� �� �Ӹ� �ƴ϶� ������ ���� ��ȯ�ؾ� �ϴ� ���� �Լ� divide_remainder�� �ִٰ� �� ��,
// �̴� std::pair�� ����� �ش� ������ ��ȯ�ϰ� �ȴ�.
//
/*
pair<int, int> divide_remainder(int dividend, int divisor) {
	int ans = dividend / divisor;
	int rest = dividend % divisor;

	return make_pair(ans,rest);
}

*/




//
// ����ü ������ ���ε��� std::tuple���� �Բ� �����Ѵ�. �¶��� �ֽ� ������ ���ϴ� ���� �Լ��̴�.
// 
// std::tuple<std::string, std::chrono::system_clock::time_point,unsigned> stock_info(const std::string &name);
// 
//



//
// ���� ����ü�� ������ ���ε��� ����� ���� ����ü�͵� �Բ� �����Ѵ�. ������ ���� ������ �ִٰ� �����غ���.
// 
//


struct employee {
	unsigned id;
	std::string name;
	std::string role;
	unsigned salary;
};

// ���� ����ü ������ ���ε��� ����� �ش� ��� ������ ������ �� �ִ�. ������ ���� ���Ͱ� ���� ���
// �ݺ��������� ó���� �� �ִ�.(main �Լ� ���� ������ ����.)
/*

*/

//




//
// ���� �м�
// 
// ����ü ������ ���ε��� �׻� ���� ������ ����ȴ�.
//
// auto[var1, var2, ...] =<pair,tuple, struct �Ǵ� array ǥ����>;
// 
// * ���� var1, var2, ... �� ����� �Ҵ�Ǵ� ǥ���Ŀ� ���ԵǴ� ������ ������ ��Ȯ�ϰ� ��ġ�ؾ� �Ѵ�.
//		* <pair�� tuple, struct, �Ǵ� array ǥ����>�� ���� �� �ϳ����� �Ѵ�.
//		* std::pair
//		* std::tuple
//		* struct��, ��� ��� ������ �������̸�, ������ �⺻ Ŭ�������� ���ǵǾ�� �Ѵ�. ù ��°�� ������ ��� ����
//			�� ù ��° ������ �Ҵ�ǰ�, �� ��°�� ������ ��� ������ �� ��° ������ �Ҵ�ȴ�.
//		* ���� ũ���� �迭
//		* �ڷ����� auto, const auto, const auto&&�� auto&&�� �� �� �ִ�.
// 
// -------------------------------------------------------------------------------------------------------------
// tip: �ݵ�� ���� �������� �ƴϴ��� �ʿ��� ��쿡�� �׻� ���۷����� ����� ���ʿ��� ���縦 �ּ�ȭ�ؾ� �Ѵ�.
// 




// 
// ���� ��ȣ �ȿ� �ʿ� �̻����� ���ų� ���� ������ �ۼ��ϸ� �����Ϸ��� ������ �߻��� �������� �˷��ش�.
//  
// 
std::tuple<int, float, long> tup{1, 2.0, 3};
// auto [a, b] = tup;	// �������� �ʴ´�.


//
// �� ������ �� ��� ������ ���� tuple ������ �� ��� ������ ä�� ������ �õ��ϴµ�, ��� �����Ϸ��� ������
// �߰��ؼ� �˷��ش�.
//

//
// 
// �ο� ����
// 
// STL�� �⺻ ������ ����ü ������ ����ü ������ ���ε�����, ���ٸ� ���� ���� ��ٷ� �� �� �ִ�.
// ���� ��� std::map�� ��� ���� ��Ҹ� ����ϴ� �ݺ����� ���캻��.
//

map<string, size_t> animal_population{
	{"humans", 700000000},
	{ "chickens",1098765456790 },
	{ "camels",24246291 },
	{ "sheep",1086881528 },
};

/*
for (const auto& [species, count] : animal_population) {
	cout << "There are" << count << " " << speices << "on this planet. \n";
}
*/


// �� ���� ������ std::map �����̳ʸ� ��ȯ�ϴ� �ܰ踶�� std::pair<const key_type , value_type> ��带 ���ؼ� �����ϰ� �ȴ�.
// ��Ȯ���� �ݺ��� ������ ���� ���� ������ �� �ֵ��� �ش� ������ ����ü ������ ���ε� ���(key_type�� species ���ڿ�, value_type
// �� �α��� size_t)�� ���� ���� ���ϴ� ���̴�.
// 
// 
// C++ 17 �������� std::tie�� ���Ͽ� ������ ȿ���� �� �� �־���.
// 
// int remainder;
// std::tie(std::ignore, remainder)=divide_remainder(16,5);
// std::cout<<"16%5 is"<<remainder<<"\n";
// 
// 
// �� ������ ��� ��(pair) ���� �� ���� ������ �ִ� ����� �����ش�. std::tie�� �����ϴ� ��� ������ �����ؾ� �ϹǷ�
// ����ü ���ε����� ȿ�������� �ʴ�. �ݸ� ����ü ������ ���ε������� ���� ���� ������ ó���Ǵ� std::ignore���� �������ν�
// std::tie�� ������ �����ش�. �� �������� �ʿ���� ���� ���� �ش� ����� �Ϻθ� �Ҵ��ϰ� �ȴ�.
// 
// 
// 
// 
// �ٽ� ������ ���ư� ������ ���� ��� �Ķ���͸� ����Ͽ� divide_remainder �Լ��� ������ �� �ִ�.
// 
//
//

#include <iostream>
#include <tuple>
#include <map>
#include <stdexcept>

bool divide_remainder(int dividend, int divisor, int& fraction, int& remainder)
{
    if (divisor == 0) {
        return false;
    }
    fraction = dividend / divisor;
    remainder = dividend % divisor;
    return true;
}

std::pair<int, int> divide_remainder(int dividend, int divisor)
{
    if (divisor == 0) {
        throw std::runtime_error{"Attempt to divide by 0"};
    }
    return { dividend / divisor, dividend % divisor };
}

int main()
{

    { // old school way
        int fraction, remainder;
        const bool success{ divide_remainder(16, 3, fraction, remainder) };
        if (success) {
            std::cout << "16 / 3 is " << fraction << " with a remainder of " << remainder << "\n";
        }
    }



    { // C++11 way
        const auto result(divide_remainder(16, 3));
        std::cout << "16 / 3 is " << result.first << " with a remainder of " << result.second << "\n";
    }



    { // C++11, ignoring fraction part of result
        int remainder;
        std::tie(std::ignore, remainder) = divide_remainder(16, 5);
        std::cout << "16 % 5 is " << remainder << "\n";
    }



    { // C++17, use structured bindings
        auto [fraction, remainder] = divide_remainder(16, 3);
        std::cout << "16 / 3 is " << fraction << " with a remainder of " << remainder << "\n";
    }



    { // C++17, decompose a tuple into individual vars
        std::tuple<int, float, long> tup {1, 2.0, 3};
        auto [a, b, c] = tup;
        std::cout << a << ", " << b << ", " << c << "\n";
    }



    { // C++17, use structured binding in for-loop


      



        for (const auto& [species, count] : animal_population) {
            std::cout << "There are " << count << " " << species << " on this planet.\n";
        }
    }


    vector<employee> employees{
        {20202020,"�����","role",500}
    
    };

    for (const auto& [id, name, role, salary] : employees) {
        cout << "Name: " << name << "Role: " << role << "Salary: " << salary << '\n';

    }

}