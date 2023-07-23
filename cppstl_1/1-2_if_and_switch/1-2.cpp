//
// * if와 switch 구문으로 변수의 범위를 제한
// 
// 변수의 범위를 최대한 제한하는 것은 좋은 것이지만, 처음에 몇 가지
// 값만 갖고 있다가 확실한 조건을 만족하면 그때 더 넓은 범위로 처리해야 하는 경우가 있을
// 것이다.
// 
// 이를 if와 switch구문을 가지고 있다.
// 
// 
// 
//			예제 구현
// 
// 
// 두 가지 방법의 초기화 구문을 이용해 코드를 깔끔하게 정리하는 방법을 살펴본다.
// 



// * if문: std::map의 find 함수를 사용해 문자열 맵에서 특정 문자를 찾는 경우를 생각해 본다.
//
#include <iostream>
#include <cstdio>
#include <map>
#include <string>

using namespace std;
/*
if (auto itr(character_map.find()); itr != character_map.end()) {
	// * itr이 유효하며, 작업을 수행한다.
}
else{
	// itr은 마지막 반복자다. 참조하지 말 것
}
// itr는 더 이상 사용할 수 없다.
*/




//
// switch 구문: 다음은 키 입력 문자를 구하는 동시에 swtich문으로 해당 값을 확인해 
// 컴퓨터 게임을 제어하는 방법을 보여준다.
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
//			예제 분석
// 
// if문과 switch 문의 초기화는 기본적으로 신택스 슈거(syntax sugar)이다. 다음 두 예제는
// 동일하다.
// 
// C++17 이전
//


template <typename T>
void print_charcount_cpp11(const T& map, char c) {
	const auto itr(map.find(c));
	if (itr != map.end()) {

		cout << "There are" << itr->second << " " << c << " characters" << "\n";
		// itr은 유효하며, 접근이 가능하다.
	}
	else {

		cout << "There are" << 0 << " " << c << " characters" << "\n";
		// itr이 유효하며, 접근할 수 있지만 사용이 가능하다.

	}
	// 여전히 itr에 접근이 가능하다.
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
	// cpp11 과 다르게 더 이상 접근할 수 없다.
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
	// switch 구문에도 동일하게 적용이 된다.
	// 
	// {
	//		auto var (init_value);
	//		switch(var):
	//			case 1:
	//			case 2:
	//			...
	// }
	// // 여전히 var에 접근이 가능하다.
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
		// 더 이상 접근할 수 없다.
	}



}
//		부연 설명
// 
// 또 다른 흥미로운 점은 제한된 크리티컬 섹션의 범위에 있다. 다음 예제를 살펴본다.
// 
// 
// 
//

/*if (std::lock_guard<std::mutex> lg {my_mutex}; some_condition) {
	// 작업을 수행한다.
}*/


//
// 가장 먼저 std::lock_guard를 생성했다. 이는 생성자의 인자로 뮤텍스(mutex)를 받는 클래스이다.
// 생성자에서 뮤텍스를 잠그며, 범위를 벗어나면 소멸자에서 다시 잠금을 푼다.
// 
// 
// 그 외에도 weak 포인터 범위와 관련된 흥미로운 점이 있다. 다음의 경우를 고려해 본다.
// 
//

/*
if (auto shared_pointer(weak_pointer.lock()); shared_pointer != nullptr) {
	// 예상대로 shared 객체가 계속해서 존재한다.
}
else {
	// shared_pointer 변수에 접근은 가능하니 null 포인터이다.
}
// 더 이상 shared_pointer 변수에 접근할 수 없다.

*/

//
// if 조건문이나 추가 중괄호 밖에서 잠재적으로 불필요한 상태면서 현재 범위에서도 
// 필요 없는 shared_pointer 변수를 갖는 또 다른 예제라고 할 수 있다.
// 
// 
//

//
// 초기화를 하는 if 구문은 출력 파라미터로, 이전 API를 사용할 때 매우 유용하다.
// 
// 
//
/*
if (DWORD exit_code; GetExitCodeProcess(process_handle, &exit_code)) {
	cout << "Exit code of process was: " << exit_code << "\n";
}

// if 조건문 밖에서는 불필요한 exit_code 변수가 사용되지 않는다.
*/