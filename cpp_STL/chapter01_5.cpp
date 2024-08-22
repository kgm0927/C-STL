#include <string>
#include <iostream>
// foo_lib.cpp
class process_monitor
{

public:
   static const inline std::string standard_string {"some static globally available stirng"};
};

inline process_monitor global_process_monitor;

class foo
{
private:
    /* data */
public:
static std::string &standard_string()
   { static std::string s{"some standard string"};
    return s;
}
};
