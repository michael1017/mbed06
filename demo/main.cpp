#include "mbed.h"
using namespace std::chrono;

Ticker flipper;
DigitalOut led2(LED2);

void flip()

{
   led2 = !led2;
}

int main()

{
   led2 = 1;
   flipper.attach(&flip, 500ms);
}
