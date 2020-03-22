#include <iostream>
using namespace std;
// Declare the enumerated type
//enum Roster { Tom = 1, Sharon, Bill};
enum Roster { Tom, Sharon = 22, Bill};
int print_value_of_enum(int who)
{
    switch (who)
    {
        case Tom :
            cout << "Tom = " << Tom << "\n";
            break;
        case Sharon :
            cout << "Sharon = " << Sharon << "\n";
            break;
        case Bill :
            cout << "Bill = " << Bill << "\n";
            break;
        default :
            cout << "Invalid selection\n";
    }
    return 0;
}

int main()
{
    print_value_of_enum(Tom);
    print_value_of_enum(Sharon);
    print_value_of_enum(Bill);
    return 0;
}
