#include "address.h"
#include "customer.h"
#include <iostream>

using namespace std;

int main() {

  Address a("zak@gmail.com", "New York", "10001","123 Main St");
  Customer("Zakarea",a);

  return 0;
}