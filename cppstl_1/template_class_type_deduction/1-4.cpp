//
//
// 
// 생성자에서 자동으로 템플릿 클래스 타입 추론
// 
// 
// 일반적으로 많은 종류의 C++ 클래스가 자료형에 대해 특화되어 있으며,
// 사용자가 생성자를 호출할 때 배치하는 변수들의 자료형으로부터 손쉽게 추론할 수 있다.
// 그런데도 C++17 이전에는 표준화된 기능이 아니었다. C++17에서는 생성자 호출 시 컴파일러가 자동으로
// 템플릿 타입을 추론한다.
//
#include <tuple>
#include <string>
#include <type_traits>
#include <iostream>



//
//		예제 구현
// 
// 이에 아주 간단한 사용 예제로 std::pair와 std::tuple 인스턴스 생성이 있다.
// 이 둘은 한 번에 특수화 및 인스턴스로 만들 수 있다.
/*
	std::pair my_pair(123, "abc");					// std::pair <int, const char*>
	std::tuple my_tuple(123, 12, 3, "abc");			// std::tuple <int, double, const char*>
*/

//
//		예제 분석
//

std::pair my_pair(123,"abc");
std::tuple my_tuple(123, 12, 3, "abc");


template<typename T1,typename T2, typename T3>
class my_wrapper {
	T1 t1;
	T2 t2;
	T3 t3;

public:
	explicit my_wrapper(T1 t1_,T2 t2_,T3 t3_): t1{t1_}, t2{t2_}, t3{t3_}
		// explicit 키워드는 자신이 원하지 않은 형변환이 일어나지 않도록 제한하는 키워드이다.


	{}
};



//
// 이는 단지 또 다른 템플릿 클래스일 뿐이다. 이전에는 인스턴스로 만들기 위해 다음과 같이 작성해야 했다.
//

my_wrapper<int, double, const char*> wrapper{123,1.23,"abc"};

//
// 혹은 템플릿 특수화 부분을 생략할 수 있다.( 지금 여기 쓸수 없지만, my_wrapper wrapper{}; 형식으로 가능하다.)
//



//
// 
// C++ 17 이전에는 헬퍼(helper) 함수를 구해야만 생략이 가능했다.
// 
// my_wrapper<T1,T2,T3> make_wrapper(T1 t1,T2 t2,T3 t3){
//
//	return {t1,t2,t3};
// }
// 
// 이와 같은 헬퍼 함수를 사용해야만 비슷한 효과를 낼 수 있었다.
// 
// 
// auto wrapper (make_wrapper(123,1.23,"abc"));
// 
//


//
// i
// 
// STL은 std::make_shared, std::make_unique, std::make_tuple 등과 같이 여전히 많은 헬퍼 함수가 존재한다.
// C++17에서는 이와 같은 함수들 대부분이 거의 필요없게 됐다. 물론 호환성의 이유로 제공은 계속 될 것이다.
//


//
//		부연 설명
// 
// 이번 예제에서는 암시적 템플릿 타입 추론에 대해 배웠다. 일부 경우에는 암시적 타입 추론에 의존할 수가 없다. 다음
// 예제 클래스를 보자.
// 
// 
//

template <typename T>
struct sum {
	T value;

	template <typename ... Ts>
	sum(Ts&& ... values): value{(values+ ...)}{}
};

//
// 
// sum 구조체는 임의의 개수의 파라미터를 허용하며, 표현식 접기를 사용해 이 파라미터를
// 모두 한꺼번에 추가한다.
// 
// sum 구조체는 멤버 변수 값을 저장한다. 여기서 질문이 생길 것이다. 과연 T는 어떤 타입일까?
// 이를 명시적으로 나타내지 않을 경우 의심의 여지없이 생성자에게 제공되는 값에 따라 달라질 것이다.
// 
// 즉, 문자열의 인스턴스가 사용되면 std::string이 된다.
// 
// 또는 정수가 사용되면 int형이 돼야 한다. 정수와 실수, double을 함께 사용하면 컴파일러는 자료의 손실없이
// 모든 값에 맞는 자료형을 나타낼 것이다. 이를 위한 명시적 추론 가이드가 있다.
//
//

template <typename ... Ts>
sum(Ts&& ... ts)-> sum<std::common_type_t<Ts...>>;

// 이 내용은 컴파일러에게 std::common_type_t 특성값을 사용하라고 알려준다. 그래서 모든 값에 맞는 기본 자료형을 찾을 수 있게 해준다.





int main() {
	my_wrapper wrap(123, 4.56, std::string{"foo"});

	std::pair  pair(123, std::string{"string"});
	std::tuple tuple(123, 4.56, std::string{"string"});

	sum s{ 1u, 2.0, 3, 4.0f };
	sum string_sum{ std::string{"abc"}, "def" };

	std::cout << s.value << '\n'
		<< string_sum.value << '\n';
}

//
// 
// 첫 번째 줄에서 unsigned와 double, int, float 형의 인자를 받는 생성자로 sum 객체
// 를 인스턴스화 한다. std::common_type는 기본 자료형의 double를 반환해 sum <double>
// 인스턴스를 구한다. 
// 
// 두 번째 줄에서는 std::string 인스턴스와 C 스타일 string을 사용하고
// 있다. 이련 추론 가이드에 따라 컴파일러는 sum<std::string> 인스턴스를 생성한다.
//
// 
// 이 코드를 실행하면 숫자 sum의 객체는 10으로 출력하고, 문자열 sum의 객체는 abcdef를 출력한다.
//