#include <iostream>
#include <string>
using namespace std;


//
// 
//		인라인 변수로 해더 전용 라이브러리 활성화
// 
// 
// C++에서는 언제든 개별 함수 인라인(inline)을 정의하는게 가능한데, C++17에서는
// 추가로 변수 인라인을 정의할 수 있게 됬다. 덕분에 헤더 전용 라이브러리의 구현이
// 더 쉬워졌다.
// 
// 
// 
// 
// 이번 예제의 핵심 목표는 inline 키워드를 이용하여 전역으로 가능한 인스턴스를 생성하는 것이다.
// 이는 C++17 이전 버전에는 불가능했다.
// 
// 
// 
//
//



// 1. process_moniter 클래스에는 정적 멤버 변수를 포함하여 전역적으로 접근이 가능해야 한다.
// 그리고 복수의 번역 단위에 포함될 때 두 개의 정의된 심볼을 생성하게 될 것이다.
// 
// 
// 2. 이제 이를 컴파일하고 연결시키기 위해 여러 개의 .cpp 파일에 해당 변수를
// 포함시키면 링커 단계에서 빌드가 실패한다. 이를 해결하기 위해 inline 키워드를
// 추가한다.
//


// foo_lib.hpp

class process_monitor {
public:
    static inline const std::string standard_string{"some static globally available string"};
};

inline process_monitor global_process_monitor;



//
//      예제분석
// 
// C++ 프로그램은 보통 여러 개의 C++ 소스 파일(.cpp 또는 .cc 확장자)로 구성된다.
// 이들은 각각 모듈이나 오브젝트 파일로 컴파일된다. 모듈 또는 오브젝트 파일은
// 모두 하나의 실행 파일이나 공유/정적 라이브러리로 함께 연결되는 것이 마지막 단계다.
// 
// 링커가 하나의 특정한 심볼 정의를 여러 번에 걸쳐 찾게 되면 링크 단계에서 오류가 생긴다.
// 예를 들어 int foo();로 명시된 함수를 갖는다고 하자. 두 개의 함수를 정의하고 있다면
// 어떤 함수가 올바른 함수라고 판단할까? 이를 판단하기 위해 링커가 주사위를 돌리진 않는다.
// 
// 전역적으로 가능한 함수를 제공하는 전역적인 방법은 헤더 파일에 해당 함수를 정의하는 것이다.
// 그래서 호출이 필요한 어느 C++ 모듈에나 포함될 것이다. 이러한 함수의 정의는 모두 분리된
// 모듈 파일로 각각 배치되어야 한다. 
// 
// 그러면 해당 함수들이 사용되길 원하는 모듈에 연결이 된다. 이를 '하나의 정의 규칙'(ODR, One Definition Rule)
// 이라고도 부른다. 
// 
// 
// 하지만 이것이 유일한 방법이었다면 헤더 전용 라이브러리를 제공하는 게 불가능했을 것이다.
// 헤더 전용 라이브러리는 C++ 파일 어디에서나 #include를 이용해 포함되기만 하면 곧바로 사용할 수
// 있기 때문에 아주 간편해진다. 
// 
// 헤더 전용이 아닌 라이브러리들을 사용하기 위해서는 링커가 소유한 모듈과 함께 라이브러리 모듈이 
// 연결되게 프로그래머가 빌드 스크립트도 맞춰야 한다. 특히 아주
// 짧은 함수만으로 구성된 라이브러리에서는 이 과정이 아주 번거롭다.
// 
// 
// 
// 이러한 경우 inline 키워드로 예외 상황을 만들어 서로 다른 모듈에 있는 여러 개의 같은
// 심볼의 정의를 허용할 수 있다. 링커가 동일한 시그니처(signature)로 된 여러 개의
// 심볼을 찾았는데, 인라인으로 정의돼 있으면 첫 번째 심볼을 선택하고 다른 심볼도 같은
// 정의를 갖고 있다고 신뢰하게 된다. 즉, 똑같은 인라인 심볼은 전부 완전히 동일하게 정의된다는
// 것을 프로그래머가 약속하는 것이다.
// 
// 이 예제의 경우 링커는 foo_lib.hpp를 포함한 모든 모듈에서 process_monitor::standard_string 심볼을
// 찾게 된다. inline 키워드가 없다면 어떤 심볼이 가장 알맞은지 알 수가 없어 작업을 중단하고 오류가 생긴다.
// 
// 
// 
// 두 개의 같은 inline 심볼을 정의하면 첫 번째로 등장하는 심볼만 허용하고 나머지 심볼은 버리게 된다.
//
// 
// C++17 이전 버전에는 추가적인 C++ 모듈 파일을 이용해 이 심볼을 제공하는 방법이 최선이었다. 즉, 해당 라이브러리를
// 사용하는 프로그래머가 링크 단계에서 이 파일을 포함시켜야 했다.
// 
// inline 키워드에는 예전부터 또 다른 하나의 기능이 있는데, 인라인 키워드는 해당 구현을 취해 호출되는 곳에 곧바로 놓이게
// 함으로써 컴파일러에게 함수 호출을 제거할 수 있음을 알려준다. 코드에 함수 호출 하나가 줄어드니 더 빨라지는 셈이다.
// 
// 
// 반대로 인라인 함수가 상당히 크다면 바이너리 크기가 증가해 최종적으로 코드를 더 빠르게 처리하지 못하는 경우도 있다. 따라서
// 컴파일러에는 판별에 inline 키워드만으로 사용하여, 인라인을 통해 함수 호출을 제거하게 된다. 그러나 프로그래머가 인라인을
// 선언하지 않아도 일부는 알아서 인라인 함수가 될 수 있다.
//

//
//      부연 설명
// 
// C++ 17 이전 버전에서 가능한 해결책 중 하나는 static 객체의 레퍼런스를 반환하는 static 함수를 제공하는 것이다.
class foo {


public:
    static std::string& standard_string() {
        static std::string s{"some standard string" };
        return s;
    }


};



// 이 방법으로 복수의 모듈에 헤더 파일이 허용해서 어디서든 완전히 같은 인스턴스에 접근하게 된다. 그러나 해당 객체는
// 프로그램의 시작과 동시에 곧바로 생성되지 않고  첫 함수 호출시에만 생성된다.
// 정적 생성자의 경우 프로그램이 시작될 때 중요한 처리를 할 만한 전역 객체가 필요할 수 있는데(예제 라이브러리 클래스와 같이),
// 프로그램이 끝날 때쯤 호출되면 너무 늦어질 수 있다.
// 
// 
// 또 다른 해결책은 비템플릿 클래스 foo를 템플릿 클래스로 만드는 것이다. 그래서 템플릿과 같은 규칙이 적용될 수 있다.
//
