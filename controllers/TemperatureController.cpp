#include "TemperatureController.h"
#include "TemperatureRepository.h"

TemperatureRepository temperatureRepository;

Response* TemperatureController::getTemperature(Request req) {
    Response *res;

    int temperature = temperatureRepository.getTemperature();

    return res
        ->status(StatusCode::_200)
        ->text(std::to_string(temperature));
};

Response* TemperatureController::postTemperature(Request req) {
    Response *res;

    // TODO get temperature from req
    // temperatureRepository.setTemperature();

    return res
        ->status(StatusCode::_200)
        ->text("Hello World!");
};