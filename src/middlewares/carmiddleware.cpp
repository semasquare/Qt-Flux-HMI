#include "carmiddleware.h"

#include "actions/actiontypes.h"

namespace car
{
    CarMiddleware::CarMiddleware(CarActions *carActions) {
        this->carActions = carActions;

        connect(&this->carService, &CarService::actualTemperatureChanged, this, &CarMiddleware::onActualTemperatureChanged);
    }

    void CarMiddleware::onActualTemperatureChanged(int actualTemperature)
    {
        // dispatch action
        carActions->setActualTemperature(actualTemperature);
    }

    void CarMiddleware::processSetTemperature(const QSharedPointer<flux_qt::Action> &action)
    {
        auto temperature = action->getPayload<int>();

        // start long running task
        this->carService.setTargetTemperature(temperature);
    }

    QSharedPointer<flux_qt::Action> CarMiddleware::process(const QSharedPointer<flux_qt::Action> &action)
    {
        switch (action->getType<ActionTypes::Enum>())
        {
        case ActionTypes::SetTemperature:
            this->processSetTemperature(action);
            break;
        default:
            // TODO: add error handling
            break;
        }
        return action;
    }

} // namespace car
