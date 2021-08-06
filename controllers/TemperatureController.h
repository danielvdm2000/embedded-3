#ifndef TEST_CONTROLLER
#define TEST_CONTROLLER

#include "Router.h"

class TemperatureController {
    public:
        static Response* getTemperature(Request req);
        static Response* postTemperature(Request req);
};

#endif