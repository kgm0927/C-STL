//
//
// 
// constexpr-if�� ������ �ð� ���� �ܼ�ȭ
// 
// 
// ���ø� �ڵ�� Ư��ȭ�� ������ ���ø� Ÿ�Կ� ���� Ư���� �۾��� �� ��� �Ѵ�.
// C++17������ constexpr-if ǥ������ �߰��ƴ�. constexpr-if ǥ������ �̷� ��Ȳ����
// ���̴� �ڵ带 ���� ȿ�������� �ܼ�ȭ��Ų��.
// 
// 
// ���� ����
// 
// �� ���� ���ø� Ŭ������ �پ��� ���ø� Ÿ�� Ư��ȭ�� �ٷ� �� �ִµ�, � Ÿ���� Ư��ȭ�ϴ����� ����
// ������ �ٸ� �ڵ带 ������ �� �ֱ� �����̴�.
// 
// 
// 1. ���ʸ� �ڵ� �Ϻθ� �ۼ��Ѵ�. �� ������ add �Լ��� ����� ��� ���� T�� U ���� �߰��� �� �ִ� �ܼ��� Ŭ�����̴�.
//
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;


template<typename T>
class addable {
	T val;
public:
	addable(T v): val{v}{}
	template <typename U>

//
// 
// 	   2. Ÿ�� T�� std::vector<something>�̰� Ÿ�� U�� int��� �����غ���. ��ü ���Ϳ�
// 	   ������ ���Ѵٴ� �� � �ǹ��ϱ�? �̴� �� ������ ��� ��ҿ� ���� �ش� ������ ���Ѵٴ�
// 	   �ǹ��̴�. �ݺ����� ���� �̸� ó���Ѵ�.
//


	//
	// 
	//			�ο� ����
	// 
	// C++17 �������� ������ ����� ��� �����ߴ��� ���캸�� constexpr-if ������ C++�� �󸶳�
	// ū ������ �����Դ��� Ȯ���� ü���� �� �ִ�.
	//
	enable_if_t<!is_same<T,vector<U>>::value,T>
		add(U x)const {
		return val + x;
	}

	template<typename U>
	enable_if_t<is_same<T,vector<U>>::value,vector<U>>

//
// ���� ������ �ڵ��� Ŭ������ constexpr-if�� ������� �ʰ��� �پ��� Ÿ�Կ� ���ؼ�
// �����ϱ�� ������ ����� ������ ���δ�. ��� �����ϴ� ���ϱ�?
// 
// �� ���� ���� �ٸ� add �Լ��� ������ ���� �ܼ��ϴ�. �׷��� ��ȯ Ÿ���� ���� �κ���
// �ſ� ������ ���δ�. �׸��� ���ǽ��� true�̸� Ÿ���� ���ϴ� std::enable_if_t<condition,typ>��
// ���� ǥ������ ���� �ణ�� Ʈ���� ����ϱ� �ִ�.
// 
// �̷� ��� ���̴� std::enable_if_t ǥ������ �ƹ��͵� ������ �ʱ� �����̴�. ������ �̷� ������ ������
// , �� ���⼭�� �׷��� ������ ���캸��.
// 
// �� ��° add �Լ������� ���� ������ �ݴ�� ����Ѵ�. �� ������� �ѹ��� �� ���� ������ �ϳ��� true�� �� �� �ִ� ���̴�.
// 
// 
// 
// 
// �����Ϸ��� ���� �̸��� ���� �ٸ� ���ø� �Լ��� �ٶ󺸸� �̵� �� �ϳ��� �����ؾ� �� ��
// �߿��� ��Ģ�� SFINAE�� ����ȴٴ� ���̴�. ��, Substitution Failure is not an Error(ġȯ ���а� ������ �ƴϴ�)���
// �����. �� ��� �ش� �Լ� �� �ϳ��� ��ȯ���� �߸��� ���ø� ǥ�������κ��� �߷��� �� ������(enable_if���� false�� �� ��)
// �����Ϸ� ������ �߻����� �ʴ´ٴ� ���� �ǹ��Ѵ�. ���� �ܼ��� �����Ϸ����� �ٸ� �Լ��� ����� �� ������ �� ���̴�.
//


	 add(U x)const {

		if constexpr (std::is_same_v<T, vector<U>>) {


			auto copy(val);
			for (auto& n : copy) {
				n += x;
			}
			return copy;

		}

		else{	return val + x;
	}
	}
//
// 
// 	   
//

};






// 1. ���׸� �ڵ� �Ϻθ� �ۼ��Ѵ�. �� ������ add �Լ��� �����
// ��� ���� T�� U ���� �߰��� �� �ִ� �ܼ��� Ŭ�����̴�.
// 
// 2. Ÿ�� T�� std::vector<something>�̰� Ÿ�� U�� int��� �����غ���.
// ��ü ���Ϳ� ������ ���Ѵٴ� �� � �ǹ��ΰ�? �̴� �� ������ ���
// ��ҿ� ���� �ش� ������ �����ϴ� �ǹ��̴�. �̴� �� ������ ��� ��ҿ�
// ���� �ش� ������ ���Ѵٴ� ���̴�. �ݺ����� ���� ó���Ѵ�.
// 
// 3. ������ �� ���� ���͸� ��ġ�� ���̴�. T�� U ��Ҹ� ���� ���Ͷ��
// �ݺ����� ���� �����ϰ� �ȴ�. �׷��� ������ �⺻ ���ϱ⸦ ���� �����Ѵ�.
//


// Ű����: constexpr �̶�.������ �ð� ����� ����� Ű���� ������ �ð��� �����Ǵ� ��� �����θ� �ʱ�ȭ �� �� �ִ�.



int main() {
	using namespace std::string_literals;

	assert(addable<int>{2}.add(3) == 5);
	assert(addable<std::string>{"aa"s}.add("bb"s) == "aabb"s);

	std::vector<int> v1 {1, 2, 3};
	std::vector<int> v2 {11, 12, 13};
	assert(addable<std::vector<int>>{v1}.add(10) == v2);

	std::vector<std::string> sv1 {"a", "b", "c"};
	std::vector<std::string> sv2 {"az", "bz", "cz"};
	assert(addable<std::vector<std::string>>{sv1}.add("z"s) == sv2);

}
//
// 
// å���� ���� ��
// 
//"assert"�� C++ ���α׷��� ���� ���Ǵ� ��ũ��(macros)�Դϴ�.�ַ� ����� �������� ���Ǹ�, 
// ������ ������ ������ �˻��ϴ� ���� ���Դϴ�.assert ��ũ�δ� ������ �˻��ϰ�, ���� ������ ����
// (false)�� ��� ���α׷��� �ߴܽ�Ű�� ���� �޽����� ����մϴ�.
// 
// 
// 
// 
//		���� �м�
// 
// 
// ���ο� �м� constexpr-if�� �Ϲ����� if-else ������ �ϴ� ���� �Ȱ���. �������� �ִٸ�
// �˻��ϴ� ������ ������ Ÿ�ӿ� �򰡵Ǿ� �Ѵٴ� ���̴�. ���α׷����� �����Ϸ��� ������
// ��� ��Ÿ�� �ڵ�� constexpr-if ���� �б� ������ �������� �ʴ´�.
// 
// ��ó���� #if�� #else �ؽ�Ʈ ġȯ ��ũ�ο� ������ ������� ������ �� ������, �ڵ� ������
// ���� ���� ���� �ִ�. ��� constexpr-if �б� ������ ������ �¾ƾ� ������ �׷��� �ʴ�
// �б� ������ �ǹ̻� ��ȿ���� �ʴ�.
// 
// �ڵ忡�� �ϳ��� ���Ϳ� x ���� ���ؾ� �ϴ��� �Ǻ��ϱ� ���ؼ��� std::is_same Ư�� Ÿ���� ����Ѵ�.
// std::is_same<A,B>::value ǥ������ A�� B�� ���� Ÿ���̸� �Ҹ���(Boolean)���� true�� ���Ѵ�.
// 
// �� �������� ���� ���ǽ��� std::is_same<T, vector<U>>::value��, T=std::vector<X>�� Ŭ������ Ư��ȭ�ϸ�
// true�� ���ϰ� U=X Ÿ���� �Ķ���ͷ� add �Լ��� ȣ���ϰ� �Ѵ�.
// 
// 
// if constexpr(a){
// 
//	// �۾��� �����Ѵ�.
// 
// } else if constexpr (b){
// 
//	// �� �ٸ� �۾��� �����Ѵ�.
// 
// }
// else{
//		// ������ �ٸ� �۾��� �����Ѵ�.
// }
// 
//