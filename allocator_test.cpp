#include "Allocator.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    SS::allocator<int> alloc1;
    int * a = alloc1.allocate(1);

    alloc1.construct(a, 7);
    cout << a[0] << " " << a[1] << " " << a[2] << endl;
    alloc1.deallocate(a, 1);
}