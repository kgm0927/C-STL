#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;


std::vector<int> v{1, 2, 3, 4, 5};

template <typename ... Ts>
auto product(Ts ... ts) {

	return (ts*...*1);
}


template<typename T, typename ... Ts>
bool insert_all(T& set, Ts ...ts);

template <typename T, typename ... Ts>
bool within(T min, T max, Ts ... ts);


template <typename R, typename ... Ts>
auto matchs(const R& range, Ts ... ts) {
	return (std::count(std::begin(range), std::end(range), ts) + ...);
}

template <typename T,typename ... Ts>
void insert_all(std::vector<T>& vec, Ts ... ts);
//
// 
//		표현식 접기로 간편한 헬퍼 함수 구현
// 
// 
// 때에 따라 파라미터는 하나의 표현식이 한꺼번에 합쳐져 함수 결과를
// 이끌어내기도 한다.
// 
//



// 1. 첫 번째로 시그니처를 정의한다.
// 
// 2. 이제 파라미터 묶음 ts를 가지게 되었으며, 해당 함수는 표현식 접기를 이용해서 사용해
// 파라미터 전부를 모두 펼쳐서 더해야 한다. ...과 함께 특정 연산자(예를 들어 +)를 사용한다면
// 괄호로 표현식을 감싸줘야 모든 값에 대해 처리할 수 있다.
//


template <typename ... Ts>
auto sum(Ts ... ts) {
	return (ts +...);

	// 아니면 return (ts +...+0);도 있다.
	// 
	// 이는 ts+...+0일 경우 정수만이 가능하다 문자열의 경우 이런 식은 불가능하다.
	// 
	//
}







int main() {

	// 3. 이렇게 하면 다음과 같은 방법으로 호출할 수 있다.
	// 
	//

	int the_sum{sum(1,2,3,4,5)};
	std::cout << the_sum << endl;


	// int 타입만 작동되는 것은 아니다. + 연산자로 구현함으로써
	// std::string을 포함한 어느 타입이건 호출할 수 있다.
	// 
	// 
	//

	string a{"Hello "};
	string b{ "World" };
	std::cout << (string)sum(a, b) << endl;	// 출력 : Hello World

	// 예제 분석
	// 
	// 위의 예제는 파라미터에 바이너리 연산자(+)의 간단한 재귀 애플리케이션이다.
	// 
	// 이를 일반적으로 폴딩(folding)이라고 부른다. C++17에서는 표현식 접기가 추가되어 적은 코드로 같은 아이디어를
	// 표현하게 해 준다.
	// 
	// 이러한 종류의 표현식을 단항 접기(unary fold)라고 한다. 다음과 같은 바이너리 연산자로 파라미터 묶음 접기를 지원한다.
	// +,-,*,/,%,^,&,|,=,<,>, <<, >>, +=, -=, *=, /=, %=, ^=, &=, |=, <<=, >>=,
	// !=, <=, >=, &&, ||, , , .* , ->* 등등이 있다.
	// 
	// 
	// 예제 코드에선 (ts+...)든 (...+ts); 둘 중 어떤 식으로 작성해도 작동하는 데 문제가 없었다. 그러나
	// ...가 연산자 쪽으로 오른쪽에 놓이면 오른쪽 접기가 호출되고, 연산자의 왼쪽에 놓이면 왼쪽 접기가 호출된다.
	// 
	// 
	// sum 함수 예제에서는 왼쪽 단항 접기가 1+(2+(3+(4+5))))로 펼쳐지지만, 단항 오른쪽 접기는 (((1+2)+3)+4)+5로 펼쳐진다.
	// 사용되는 연산자에 따라 값이 달라진다. 숫자를 더할 때는 상관이 없지만
	// 
	//


	// 개별 요소 범위의 일치의 match 함수 실행(부분 참조)

	matchs(v, 2, 5);					// 2 반환
	matchs(v, 100, 200);				// 0 반환
	matchs("abcdefg", 'x', 'y', 'z');	// 0 반환
	matchs("abcdefg", 'a', 'd', 'f');	// 3 반환


	// set에 복수의 삽입 성공 여부 확인 함수 실행(부분 참조)
	std::set<int> my_set{1, 2, 3};
	
	insert_all(my_set, 4, 5, 6);
	insert_all(my_set, 7, 8, 2);


	// 이미 my_set 안에 2가 있으므로 2와 5는 쓰이지도 못하고 종료된다.
	insert_all(my_set, 4, 2, 5);
	// 이제 set는 5를 제외한 {1, 2, 3, 4}를 포함한다.


	within(10, 20, 1, 15, 30);				// -->false
	within(10, 20, 11, 12, 13);				// -->true
	within(5.0, 5.5, 5.1, 5.2, 5.3);		// -->true




	std::string aaa{"aaa" };
	std::string bcd{"bcd"};
	std::string def{"def"};
	std::string zzz{"zzz"};

	within(aaa, zzz, bcd, def);	// true
	within(aaa, def, bcd, zzz);	// true


	std::vector<int> v{1, 2, 3};
	insert_all(v, 4, 5, 6);

}


//
// 
// 
//		부연 설명
// 
// 인자 없는 sum()을 호출할 시 가변 파라미터 묶음에는 접힐 수 있는 값이 포함되지 않는다. 대부분의
// 연산자에서는 여기서 오류가 발생한다.
// 
// 그래서 오류가 발생하게 놔둘지 빈 합계를 특정 값으로 놔둘지를 결정해야 한다. 올바른 방향은 아무것도 없는
// 합은 0으로 놔두는 것이다.
// 
// 이 방법으로 sum()은 0으로 평가가 된다. 그리고 sum(1,2,3)은 (1+(2+(3+0)))과 같이 평가된다. 이처럼 초깃값을 통해
// 접는 것을 바이너리 접기(binary fold)라고 한다.
//
// (ts+...+0)이나 (o+...+ts) 둘 다 작동하지만 이는 바이너리 접기를 바이너리 오른쪽 접기 또는 바이너리 왼쪽 접기로 만든다.
// 
// 
// 
// 
// 인자 없는 구현을 하기 위해 바이너리 접기를 사용할 때 식별 값의 개념이 중요할 수 있다.
// 여기서는 특정 값에 0을 더하면 변경되는 게 없으므로 0을 식별 값으로 만들 수 있다. 이러한
// 속성으로 +나 - 연산자와 함께 특정 표현식 접기에 0을 더할 수 있다.
// 
// 곱셈에도 이것이 적용이 된다.
// 
//
/*
template <typename ... Ts>
auto product(Ts ... ts) {

	return (ts*...*1);
}
*/
//
// product(2,3)의 결과 값는 6이며, product()와 같이 파라미터가 없는 경우 결과 값은 1이다.
// 
// 
// 논리 연산자 &&와 || 는 내장된 자체 식별자를 가진다. &&로 빈 파라미터를 접으면 &&이 되며,
// ||는 false가 된다.
// 
// 빈 파라미터를 적용할 때 올바른 표현식으로 또 다른 연산자(,)가 있다. 기본값은 void()이다.
// 
// 이 밑에 구현할 수 있는 간단한 헬퍼 함수를 몇개 살펴보면서 영감을 얻는다.
//

 



//			개별 요소 범위의 일치
// 
// 
// 다음과 같이 일정 범위 안에 가변 파라미터로 제공된 값이 최소 한 개 포함되는지 알려주는 값이 있다. 
//



/*
template <typename R,typename ... Ts>
auto matchs(const R& range, Ts ... ts) {
	return (std::count(std::begin(range), std::end(range), ts) + ...);
	// return (count(begin(range),end(range),ts));
}
*/


//
// 
// 헬퍼 함수는 STL의 std::count 함수를 사용한다. 이 함수는 세 개의 파라미터를
// 취한다. 맨 처음 두 개의 파라미터는 반복 간으한 범위의 시작(begin)과 끝(end) 반복자다.
// 그리고 세 번째 파라미터는 해당 범위의 모든 요소를 비교하게 되는 값이다. std::count 함수는
// 세 번째 파라미터와 같은 범위에 있는 모든 요소의 개수를 반환한다.
// 
// 
// 표현식 접기에서 std::count 함수는 계속 같은 범위의 파라미터 시작과 끝 반복자를 전달한다.
// 이와 다르게 세 번째 파라미터는 파라미터 묶음에서 매번 또 다른 파리미터 하나를 전달한다.
// 마지막으로 이 함수는 모든 결과를 합해 전달한다.
// 
// 
// 다음과 같이도 사용할 수 있다.(matchs 함수 사용은 main 함수안에서 사용해 보겠다.)
//



//
// std::vector<int> v{1, 2, 3, 4, 5};
// 
// 여기서 알 수 있듯이 matchs 헬퍼 함수는 상당히 다재다능 하다. 벡터나 심지어는 문자열까지 곧바로 호출할 수 있다.
// 또한 초기화 목록이나 std::list, std::array, std::set 등의 인스턴스로도 동작할 수 있다.
// 
//






//
// 
//		 set에 복수의 삽입 성공 여부 확인
// 
// std::set에 임의의 개수로 가변 파라미터를 삽입해 성공 여부를 반환하는 헬퍼 함수를 작성해보자.
// 
// 
template<typename T, typename ... Ts>
bool insert_all(T& set, Ts ...ts) {
	return (set.insert(ts).second && ...);


	// 이것은 어떻게 동작하는 것일까? std::set의 삽입 함수는 다음과 같은 시그니처를 가진다.
	// 
	// std::pair<iterator,bool> insert(const value_type& value);
	// 
	// 이는 삽입을 할 때 insert 함수가 반복자iterator, bool 변수 두개를 반환하는 것이다. 삽입이
	// 성공되면 bool은 true가 되며, 반복자는 set에 새로운 요소를 가리키게 된다. 반대로 실패하면
	// 반복자는 삽입하려는 값과 충돌되는 기존 요소를 가리킨다.
	//


	//
	// 이 헬퍼 함수는 아이템을 삽입한 다음 .second에 접근한다. 이는 삽입 성공 또는 실패를 나타내는
	// bool 변수다. 모든 반환 쌍이 true로 되면 모든 삽입이 성공했음을 의미한다. 표현식 접기는
	// 모든 삽입 결과를 && 연산자로 합쳐 결과 값을 반환한다.
	// 
	// 
	// 다음과 같이 사용할 수 있다. (main 함수 참고)
	//

	//
	// 예를 들어 세 개의 요소를 삽입하려고 할 때 두 번째 요소가 이미 삽입돼 있는 상태면
	// && ... 표현식 접기는 다른 요소의 삽입도 중지하게 된다.
	//
}




//
//		모든 파라미터가 해당 범위에 들어있는지 여부를 검사
// 
// 하나의 변수가 특정 범위에 들어 있는지 여부를 확인할 수 있다면 표현식 접기를
// 통해 복수의 변수에 대해서도 동일하게 처리할 수 있다.
// 
// 
//
template <typename T,typename ... Ts>
bool within(T min, T max, Ts ... ts) {
	return ((min <= ts && ts <= max)&& ...);


	//
	// (min <= ts && ts <= max) 표현식은 파라미터 묶음의 모든 값이 min과 max를 포함한
	// 범위 내에 들어있는지 알려준다. 여기서는 모든 불리언 결과 값을 하나의 값으로 줄이기
	// 위해 && 연산자를 선택했다. 그러면 모든 개별 결과 값이 전부 true일 때만 true가 된다.
	// 
	//(main 함수 사용 참조)
}

//
// 
// 흥미롭게 이 함수는 아주 다재다능한데 사용하는 타입에 대한 유일한 요구 사항이 <= 연산자에 필적하기
// 때문이다. 이는 곧 std::string으로도 구현할 수 있다.
// 
//

/*	std::string aaa{"aaa" };
	std::string bcd{"bcd"};
	std::string def{"def"};
	std::string zzz{"zzz"};

	within(aaa, zzz, bcd, def);	// true
	within(aaa, def, bcd, zzz);	// true
*/

//
// 
// vector에 복수의 요소 넣기
// 
// 결과 값을 줄일 필요 없이 복수의 같은 행동을 처리하도록 헬퍼 함수를 작성하는 것도 가능하다.
// std::vector에 요소들을 삽입하는 것처럼 이는 어떤 결과 값도 반환하지 않는다
// (std::vector::insert()는 예외적으로 오류를 던지게 되어 있다).
//
template <typename T,typename ... Ts>
void insert_all(std::vector<T>& vec, Ts ... ts) {
	(vec.push_back(ts), ...);
}
// (작동은 main()함수 제일 마지막 줄 확인)
// 
// 실제 결과 값에 표현식 접기를 쓰지 않는 개별 vec.push_back(...)으로 파라미터
// 묶음을 펼치지 위해 여기서 (,) 연산자를 사용한 것에 주목하자. 이 함수는 빈 파라미터
// 묶음과도 잘 작동한다. (,) 연산자가 '아무것도 아무 처리도 하지 않는' 암시적인 식별 값 void()를
// 가지고 있기 때문이다.
//

