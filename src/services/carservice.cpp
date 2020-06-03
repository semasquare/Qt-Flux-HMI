#include "carservice.h"

namespace car {
    CarService::CarService()  {
        connect(&this->actualTemperatureTimer, &QTimer::timeout, this, &CarService::onActualTemperatureTimeout);
    }

    void CarService::setActualTemperature(int actualTemperature)
    {
        if (actualTemperature != this->actualTemperature)
        {
            this->actualTemperature = actualTemperature;
            emit actualTemperatureChanged(actualTemperature);
        }
    }

    void CarService::setTargetTemperature(int targetTemperature)
    {
        this->targetTemperature = targetTemperature;

        this->actualTemperatureTimer.start(1000);
    }

    void CarService::onActualTemperatureTimeout()
    {
        if (this->actualTemperature < this->targetTemperature) {
            this->setActualTemperature(this->actualTemperature + 1);
        } else {
            this->setActualTemperature(this->actualTemperature + -1);
        }

        if (this->actualTemperature == this->targetTemperature) {
            this->actualTemperatureTimer.stop();
        }
    }
}
