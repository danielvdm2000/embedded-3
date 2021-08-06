#include "TemperatureRepository.h"

void TemperatureRepository::setTemperature(int temperature) {
    this->temperature = temperature;
}

int TemperatureRepository::getTemperature() {
    return this->temperature;
}