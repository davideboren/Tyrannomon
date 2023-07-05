#include <EventQueue.h>

EventQueue::EventQueue(){
    idx = 0;
    clear();
}

void EventQueue::push(Event event){
    events[idx] = event;
    idx = (idx + 1) % 10;
}

void EventQueue::clear(){
    idx = 0;
    for(int i = 0; i < 10; i++){
        events[i] = NONE;
    }
}