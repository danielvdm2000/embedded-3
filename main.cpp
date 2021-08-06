#include "mbed.h"
#include "EthernetInterface.h"
#include "Router.h"

#include "TemperatureController.h"

EthernetInterface net;

int main()
{
    Router router(&net);

    TemperatureController temperatureController;

    router.get("/temperature", temperatureController.getTemperature);
    router.post("/temperature", temperatureController.postTemperature);

    router.listen(80);
}