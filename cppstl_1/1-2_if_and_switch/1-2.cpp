//
// * if�� switch �������� ������ ������ ����
// 
// ������ ������ �ִ��� �����ϴ� ���� ���� ��������, ó���� �� ����
// ���� ���� �ִٰ� Ȯ���� ������ �����ϸ� �׶� �� ���� ������ ó���ؾ� �ϴ� ��찡 ����
// ���̴�.
// 
// �̸� if�� switch������ ������ �ִ�.
// 
// 
// 
//			���� ����
// 
// 
// �� ���� ����� �ʱ�ȭ ������ �̿��� �ڵ带 ����ϰ� �����ϴ� ����� ���캻��.
// 



// * if��: std::map�� find �Լ��� ����� ���ڿ� �ʿ��� Ư�� ���ڸ� ã�� ��츦 ������ ����.
//
#include <iostream>
#include <cstdio>
#include <map>
#include <string>

using namespace std;
/*
if (auto itr(character_map.find()); itr != character_map.end()) {
	// * itr�� ��ȿ�ϸ�, �۾��� �����Ѵ�.
}
else{
	// itr�� ������ �ݺ��ڴ�. �������� �� ��
}
// itr�� �� �̻� ����� �� ����.
*/




//
// switch ����: ������ Ű �Է� ���ڸ� ���ϴ� ���ÿ� swtich������ �ش� ���� Ȯ���� 
// ��ǻ�� ������ �����ϴ� ����� �����ش�.
//
//
// switch(char (getchar());c){
// case 'a':
//	case 'b':
//....
// 
// 
// }
//


//
//			���� �м�
// 
// if���� switch ���� �ʱ�ȭ�� �⺻������ ���ý� ����(syntax sugar)�̴�. ���� �� ������
// �����ϴ�.
// 
// C++17 ����
//


template <typename T>
void print_charcount_cpp11(const T& map, char c) {
	const auto itr(map.find(c));
	if (itr != map.end()) {

		cout << "There are" << itr->second << " " << c << " characters" << "\n";
		// itr�� ��ȿ�ϸ�, ������ �����ϴ�.
	}
	else {

		cout << "There are" << 0 << " " << c << " characters" << "\n";
		// itr�� ��ȿ�ϸ�, ������ �� ������ ����� �����ϴ�.

	}
	// ������ itr�� ������ �����ϴ�.
}

// C++17


template <typename T>
void print_charcount_cpp17(const T& map, char c)
{
	if (const auto itr(map.find()); itr != map.end()) {

		
		std::cout << "There are " << itr->second << " " << c << " characters." << "\n";
	}
	else {
		std::cout << "There are " << 0 << " " << c << " characters." << "\n";
	}
	// cpp11 �� �ٸ��� �� �̻� ������ �� ����.
}


int main() {
	{
		map<char, size_t> character_map{{'a', 10}, { 'b',20 }, {'c',30}};
		print_charcount_cpp11(character_map, 'a');
		print_charcount_cpp11(character_map, 'c');

		print_charcount_cpp17(character_map, 'a');
		print_charcount_cpp17(character_map, 'c');

	}



	//
	// switch �������� �����ϰ� ������ �ȴ�.
	// 
	// {
	//		auto var (init_value);
	//		switch(var):
	//			case 1:
	//			case 2:
	//			...
	// }
	// // ������ var�� ������ �����ϴ�.
	//}


	{
		cout << "Please enter a character: ";
		switch (char c(getchar()); c) {
		case  'a':
			cout << "You entered a lower case letter: " << c << "\n";
			break;
		case  'b':
			cout << "You entered a lower case letter: " << c << "\n";
			break;
		case  'c':
			cout << "You entered a lower case letter: " << c << "\n";
			break;

		default:
			cout << "You entered something else:" << c << "\n";

		}
		// �� �̻� ������ �� ����.
	}



}
//		�ο� ����
// 
// �� �ٸ� ��̷ο� ���� ���ѵ� ũ��Ƽ�� ������ ������ �ִ�. ���� ������ ���캻��.
// 
// 
// 
//

/*if (std::lock_guard<std::mutex> lg {my_mutex}; some_condition) {
	// �۾��� �����Ѵ�.
}*/


//
// ���� ���� std::lock_guard�� �����ߴ�. �̴� �������� ���ڷ� ���ؽ�(mutex)�� �޴� Ŭ�����̴�.
// �����ڿ��� ���ؽ��� ��׸�, ������ ����� �Ҹ��ڿ��� �ٽ� ����� Ǭ��.
// 
// 
// �� �ܿ��� weak ������ ������ ���õ� ��̷ο� ���� �ִ�. ������ ��츦 ����� ����.
// 
//

/*
if (auto shared_pointer(weak_pointer.lock()); shared_pointer != nullptr) {
	// ������ shared ��ü�� ����ؼ� �����Ѵ�.
}
else {
	// shared_pointer ������ ������ �����ϴ� null �������̴�.
}
// �� �̻� shared_pointer ������ ������ �� ����.

*/

//
// if ���ǹ��̳� �߰� �߰�ȣ �ۿ��� ���������� ���ʿ��� ���¸鼭 ���� ���������� 
// �ʿ� ���� shared_pointer ������ ���� �� �ٸ� ������� �� �� �ִ�.
// 
// 
//

//
// �ʱ�ȭ�� �ϴ� if ������ ��� �Ķ���ͷ�, ���� API�� ����� �� �ſ� �����ϴ�.
// 
// 
//
/*
if (DWORD exit_code; GetExitCodeProcess(process_handle, &exit_code)) {
	cout << "Exit code of process was: " << exit_code << "\n";
}

// if ���ǹ� �ۿ����� ���ʿ��� exit_code ������ ������ �ʴ´�.
*/