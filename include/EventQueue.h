#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <Arduino.h>
#include <Events.h>

class EventQueue {

    public:
        EventQueue();

        Event events[10];
        int idx = 0;

        void push(Event event);
        void clear();

};
#endif //EVENT_QUEUE_H