//
//
// 
// constexpr-if로 컴파일 시간 결정 단순화
// 
// 
// 템플릿 코드는 특수화된 각각의 템플릿 타입에 따라 특정한 작업을 해 줘야 한다.
// C++17에서는 constexpr-if 표현식이 추가됐다. constexpr-if 표현식은 이런 상황에서
// 쓰이는 코드를 아주 효과적으로 단순화시킨다.
// 
// 
// 예제 구현
// 
// 이 헬퍼 템플릿 클래스는 다양한 템플릿 타입 특수화를 다룰 수 있는데, 어떤 타입을 특수화하는지에 따라
// 완전히 다른 코드를 선택할 수 있기 때문이다.
// 
// 
// 1. 제너리 코드 일부를 작성한다. 이 예제는 add 함수를 사용해 멤버 변수 T에 U 값을 추가할 수 있는 단순한 클래스이다.
//
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <type_traits>
using namespace std;


template<typename T>
class addable {
	T val;
public:
	addable(T v): val{v}{}

//





//
	template<typename U>

	 T add(U x)const {
		
		 
		 // 3. 다음 마지막 단계는 두 개의 백터를 합치는 것이다. T가 U 요소를 갖는 벡터라면 반복문을 통하여 변경한다. 그렇지 않으면
		// 기본 더하기를 통해 구현한다.
		if constexpr (std::is_same_v<T, vector<U>>) {

			// 
			// 	   2. 타입 T가 std::vector<something>이고 타입 U는 int라고 생각해보자. 전체 벡터에
			// 	   정수를 더한다는 게 어떤 의미일까? 이는 곧 벡터의 모든 요소에 대해 해당 정수를 더한다는
			// 	   의미이다. 반복문을 통해 이를 처리한다.
			//

			auto copy(val);
			for (auto& n : copy) {
				n += x;
			}
			return copy;

		}

		else{	return val + x;}
	}
//
// 
// 	   
//

};






// 1. 제네릭 코드 일부를 작성한다. 이 예제는 add 함수를 사용해
// 멤버 변수 T에 U 값을 추가할 수 있는 단순한 클래스이다.
// 
// 2. 타입 T가 std::vector<something>이고 타입 U는 int라고 생각해보자.
// 전체 벡터에 정수를 더한다는 게 어떤 의미인가? 이는 곧 벡터의 모든
// 요소에 대해 해당 정수를 더한하는 의미이다. 이는 곧 벡터의 모든 요소에
// 대해 해당 정수를 더한다는 뜻이다. 반복문을 통해 처리한다.
// 
// 3. 다음은 두 개의 벡터를 합치는 것이다. T가 U 요소를 갖는 벡터라면
// 반복문을 통해 변경하게 된다. 그렇지 않으면 기본 더하기를 통해 구현한다.
// 
// 4. 이제 이 클래스를 실제 사용해 적용해본다. int나 float, std::vector<int>, std::vector<string>과
// 같이 전혀 다른 타입에서는 어떻게 작동되는지 보자.(main 함수 참고)
//


// 키워드: constexpr 이란.컴파일 시간 상수를 만드는 키워드 컴파일 시간에 결정되는 상수 값으로만 초기화 할 수 있다.


template <typename T>
class addable_cpp_11 {
	T val;
public:
	addable_cpp_11(T v): val{v}{}

		template <typename U>
	std::enable_if_t<!std::is_same<T,std::vector<U>>::value,T>
		add(U x) const { return val + x; }

	template <typename U>
	std::enable_if_t<std::is_same<T, std::vector<U>>::value, std::vector<U>>
		add(U x)const {
		auto copy(val);
		for (auto& n : copy)
		{
			n += x;
		}
		return copy;
	}
	//
	// 
	//			부연 설명
	// 
	// C++17 이전에는 동일한 기능을 어떻게 구현했는지 살펴보면 constexpr-if 생성이 C++에 얼마나
	// 큰 발전을 가져왔는지 확실히 체감할 수 있다.
	//

//
// 새로 개선한 코드의 클래스는 constexpr-if를 사용하지 않고도 다양한 타입에 대해서
// 동작하기는 하지만 상당히 복잡해 보인다. 어떻게 동작하는 것일까?
// 
// 두 개의 서로 다른 add 함수의 구현만 보면 단순하다. 그러나 반환 타입의 정의 부분이
// 매우 복잡해 보인다. 그리고 조건식이 true이면 타입을 평가하는 std::enable_if_t<condition,type>과
// 같은 표현식을 통해 약간의 트릭을 사용하기 있다.
// 
// 이런 방법 없이는 std::enable_if_t 표현식이 아무것도 평가하지 않기 때문이다. 보통은 이런 오류로 보지만
// , 왜 여기서는 그렇지 않은지 살펴보자.
// 
// 두 번째 add 함수에서는 같은 조건을 반대로 사용한다. 이 방법으로 한번에 두 개의 구현중 하나만 true가 될 수 있는 것이다.
// 
// 
// 
// 
// 컴파일러가 같은 이름의 서로 다른 템플릿 함수를 바라보면 이들 중 하나를 선택해야 할 때
// 중요한 원칙은 SFINAE가 진행된다는 점이다. 즉, Substitution Failure is not an Error(치환 실패가 오류가 아니다)라는
// 얘기다. 이 경우 해당 함수 중 하나의 반환값이 잘못된 템플릿 표현식으로부터 추론할 수 없더라도(enable_if에서 false가 될 때)
// 컴파일러 오류가 발생하지 않는다는 것을 의미한다. 그저 단순히 컴파일러에서 다른 함수를 사용해 볼 예정인 것 뿐이다.
// 
// 
// 
// 
};


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
// 책에는 없는 것
// 
//"assert"는 C++ 프로그래밍 언어에서 사용되는 매크로(macros)입니다.주로 디버깅 목적으로 사용되며, 
// 논리적 조건이 참인지 검사하는 데에 쓰입니다.assert 매크로는 조건을 검사하고, 만약 조건이 거짓
// (false)인 경우 프로그램을 중단시키고 오류 메시지를 출력합니다.
// 
// 
// 
// 
//		예제 분석
// 
// 
// 새로운 분석 constexpr-if는 일반적인 if-else 구조와 하는 일이 똑같다. 차이점이 있다면
// 검사하는 조건이 컴파일 타임에 평가되야 한다는 점이다. 프로그램에서 컴파일러가 생성한
// 모든 런타임 코드는 constexpr-if 조건 분기 명령을 포함하지 않는다.
// 
// 전처리기 #if와 #else 텍스트 치환 메크로와 유사한 방법으로 동작할 수 있지만, 코드 문법에
// 맞지 않을 수도 있다. 모든 constexpr-if 분기 명령은 문법에 맞아야 하지만 그렇지 않는
// 분기 명령은 의미상 유효하지 않다.
// 
// 코드에서 하나의 벡터에 x 값을 더해야 하는지 판별하기 위해서는 std::is_same 특성 타입을 사용한다.
// std::is_same<A,B>::value 표현식은 A와 B가 같은 타입이면 불리언(Boolean)값을 true로 평가한다.
// 
// 이 예제에서 사용된 조건식은 std::is_same<T, vector<U>>::value로, T=std::vector<X>로 클래스를 특수화하면
// true로 평가하고 U=X 타입의 파라미터로 add 함수를 호출하게 한다.
// 
// 
// if constexpr(a){
// 
//	// 작업을 수행한다.
// 
// } else if constexpr (b){
// 
//	// 또 다른 작업을 수행한다.
// 
// }
// else{
//		// 완전히 다른 작업을 수행한다.
// }
// 
// 
// 
// 
// 부연 설명 : 클래스 addable_cpp_11
//