#include "mbed.h"

#include "mbed_events.h"

using namespace std::chrono;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn btn(USER_BUTTON);

EventQueue printfQueue;
EventQueue eventQueue;


void blink_led2() {
led2 = !led2;
}


void print_toggle_led() {
printf("Toggle LED!\r\n");
}


void btn_fall_irq() {
led1 = !led1;
printfQueue.call(&print_toggle_led);
}


int main() {
Thread printfThread(osPriorityLow);
printfThread.start(callback(&printfQueue, &EventQueue::dispatch_forever));

Thread eventThread(osPriorityNormal);
eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

Ticker ledTicker;
ledTicker.attach(eventQueue.event(&blink_led2), 1s);

btn.fall(&btn_fall_irq);

}
