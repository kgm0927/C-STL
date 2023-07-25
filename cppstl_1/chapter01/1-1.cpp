#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


//
//
// 
// 구조체 형태의 바인딩에 맞게 pair나 tuple, 또는 구조체의 각 멤버 변수에 접근하는 방법과
// 새로운 if와 switch 구분의 변수 초기화 능력으로 변수 사용 영역을 제한하고자 한다.
// 
// 템플릿 클래스 인스턴스의 정확한 유형은 실제 생성자 인자에서 추론하게 된다. 그리고 템플릿
// 클래스의 서로 다른 특수화가 완전히 다른 코드를 만들어내려면 constexpr-if로 쉽게 표현할 수
// 있다. 템플릿 함수에서 가변 파라미터 묶음을 다루는 것 또한 새로운 '표현식(fold expression)'
// 로 더욱 쉬워졌다. 끝으로 예전에는 함수에서만 가능했던 인라인 변수 정의 기능이 새로 추가된
// 덕분에 헤더 전용 라이브러리에 전역적으로 접근 가능한 정적 객체를 정의하기 편리해졌다.
// 
// 
// 
//			- 묶음으로 된 반환값을 풀기 위해 구조체 형태의 바인딩 사용
// 
// C++ 17 신택스 슈거(syntactic sugar)와 자동화 타입 추론이 결합된 새로운 '구조체 형태의
// 바인딩'(structured bindings)기능이 추가됐다. 이는 'pair'이나 'tuple', 또는 구조체로부터
// 개별 변수에 일정 값을 할당할 수 있게 해 준다. 다른 프로그래밍 언어에서는 '언패킹(unpacking)'
// 이라고 한다.
// 
// 
// 
// 
//



//우선 C++17 이전에는 어떻게 했는지 살펴본다. 그리고 그 이후에는 어떻게 하는지 살펴보겠다.
// 
//  * std::pair의 각 값에 대한 접근: 배당금(dividend)과 제수(divisor) 파라미터를 받으며,
//	분수 값 뿐만 아니라 나머지 값도 반환해야 하는 수학 함수 divide_remainder가 있다고 할 때,
// 이는 std::pair를 사용해 해당 값들을 반환하게 된다.
//
/*
pair<int, int> divide_remainder(int dividend, int divisor) {
	int ans = dividend / divisor;
	int rest = dividend % divisor;

	return make_pair(ans,rest);
}

*/




//
// 구조체 형태의 바인딩은 std::tuple과도 함께 동작한다. 온라인 주식 정보를 구하는 예제 함수이다.
// 
// std::tuple<std::string, std::chrono::system_clock::time_point,unsigned> stock_info(const std::string &name);
// 
//



//
// 또한 구조체의 형태의 바인딩은 사용자 정의 구조체와도 함께 동작한다. 다음과 같은 구조가 있다고 생각해보자.
// 
//


struct employee {
	unsigned id;
	std::string name;
	std::string role;
	unsigned salary;
};

// 이제 구조체 형태의 바인딩을 사용해 해당 멤버 변수에 접근할 수 있다. 다음과 같은 벡터가 있을 경우
// 반복문에서도 처리할 수 있다.(main 함수 제일 마지막 참고.)
/*

*/

//




//
// 예제 분석
// 
// 구조체 형태의 바인딩은 항상 같은 패턴이 적용된다.
//
// auto[var1, var2, ...] =<pair,tuple, struct 또는 array 표현식>;
// 
// * 변수 var1, var2, ... 의 목록은 할당되는 표현식에 포함되는 변수의 개수와 정확하게 일치해야 한다.
//		* <pair나 tuple, struct, 또는 array 표현식>은 다음 중 하나여야 한다.
//		* std::pair
//		* std::tuple
//		* struct로, 모든 멤버 변수는 비정적이며, 동일한 기본 클래스에서 정의되어야 한다. 첫 번째로 정의한 멤버 변수
//			는 첫 번째 변수에 할당되고, 두 번째로 고정된 멤버 변수는 두 번째 변수에 할당된다.
//		* 고정 크기의 배열
//		* 자료형은 auto, const auto, const auto&&나 auto&&도 될 수 있다.
// 
// -------------------------------------------------------------------------------------------------------------
// tip: 반드시 성능 때문만은 아니더라도 필요한 경우에는 항상 레퍼런스를 사용해 불필요한 복사를 최소화해야 한다.
// 




// 
// 꺾쇠 괄호 안에 필요 이상으로 많거나 적은 변수를 작성하면 컴파일러는 오류를 발생해 문제점을 알려준다.
//  
// 
std::tuple<int, float, long> tup{1, 2.0, 3};
// auto [a, b] = tup;	// 동작하지 않는다.


//
// 이 예제는 세 멤버 변수를 갖는 tuple 변수에 두 멤버 변수를 채워 넣으려 시도하는데, 즉시 컴파일러가 문제를
// 발견해서 알려준다.
//

//
// 
// 부연 설명
// 
// STL의 기본 데이터 구조체 상당수가 구조체 형태의 바인딩으로, 별다른 변경 없이 곧바로 볼 수 있다.
// 예를 들어 std::map의 모든 구성 요소를 출력하는 반복문을 살펴본다.
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


// 이 위의 예제는 std::map 컨테이너를 순환하는 단계마다 std::pair<const key_type , value_type> 노드를 구해서 동작하게 된다.
// 정확히는 반복문 내에서 개별 값에 접근할 수 있도록 해당 노드들이 구조체 형태의 바인딩 기능(key_type은 species 문자열, value_type
// 은 인구수 size_t)을 통해 값을 구하는 것이다.
// 
// 
// C++ 17 이전에는 std::tie를 통하여 유사한 효과를 볼 수 있었다.
// 
// int remainder;
// std::tie(std::ignore, remainder)=divide_remainder(16,5);
// std::cout<<"16%5 is"<<remainder<<"\n";
// 
// 
// 이 예제는 결과 쌍(pair) 값을 두 개의 변수에 넣는 방법을 보여준다. std::tie는 결합하는 모든 변수를 정의해야 하므로
// 구조체 바인딩보다 효과적이지 않다. 반면 구조체 형태의 바인딩에서는 없는 더미 변수로 처리되는 std::ignore값을 가짐으로써
// std::tie의 강점을 보여준다. 이 예제에서 필요없는 값은 버려 해당 결과의 일부만 할당하게 된다.
// 
// 
// 
// 
// 다시 앞으로 돌아가 다음과 같이 출력 파라미터를 사용하여 divide_remainder 함수를 구현할 수 있다.
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
        {20202020,"김근육","role",500}
    
    };

    for (const auto& [id, name, role, salary] : employees) {
        cout << "Name: " << name << "Role: " << role << "Salary: " << salary << '\n';

    }

}