#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <stdexcept>
#include <chrono>

std::pair<int,int> divide_remainder(int dividend,int divisor);


std::tuple<std::string, std::chrono::system_clock::time_point ,unsigned> stock_info(const std::string &name);


typedef struct employee{
    unsigned id;
    std::string name;
    std::string role;
    unsigned salary;
};

std::tuple<int,float,long> tup{1,2.0,3};


std::map <std::string, size_t> animal_population{
 	{"humans", 700000000},
	{ "chickens",1098765456790 },
	{ "camels",24246291 },
	{ "sheep",1086881528 },
};

bool divide_remainder(int dividend,int divisor,int& fraction,int& remainder){

    if(divisor==0){
        return false;
    }

    fraction=dividend/divisor;
    remainder=dividend%divisor;
    return true;
}




int main(){

{ // c++ 17 only   
     const auto result(divide_remainder(16,3));
std::cout<<"16/3 is"<<result.first<<"with a remainder of "<<result.second<<"\n";
}

{
    auto [fraction,remainder]=divide_remainder(16,3);
    std::cout<<"16/3 is "<<fraction<<"with a remainder of "<<remainder<<'\n';

}

const auto[name,valid_time,price]=stock_info("INFO");


std::vector<employee> employee{
     {20202020,"김근육","role",500}
};

for (const auto&[id,name,role,salary]:employee){
    std::cout<<"Name: "<<name
    <<"Role: "<<role
    <<"Salary: "<<salary<<'\n';
}

for (const auto &[species,count] : animal_population)
{
    std::cout<<"There are"<<count<<" "<<species<<" on this planet. \n";
    
}


int remainder;
std::tie(std::ignore,remainder)=divide_remainder(16,5);
std::cout<<"16%5 is "<<remainder<<'\n';



}


