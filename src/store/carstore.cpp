#include "carstore.h"

#include <QDebug>

#include "actions/actiontypes.h"

namespace car
{
    void CarStore::processTemperature(const QSharedPointer<flux_qt::Action> &action) {
        auto temperature = action->getPayload<int>();
        this->setTempearture(temperature);

        qDebug() << "setTemperature(" << temperature << ")";
    }

    void CarStore::processActualTemperature(const QSharedPointer<flux_qt::Action> &action) {
        auto actualTemperature = action->getPayload<int>();
        this->setActualTemperature(actualTemperature);

        qDebug() << "setActualTemperature(" << actualTemperature << ")";
    }

    void CarStore::process(const QSharedPointer<flux_qt::Action> &action)
    {
        qDebug() << action->getType<ActionTypes::Enum>();

        switch(action->getType<ActionTypes::Enum>()) {
        case ActionTypes::SetTemperature:
            this->processTemperature(action);
            break;
        case ActionTypes::SetActualTemperature:
            this->processActualTemperature(action);
            break;
        default:
            qWarning() << "unknown action type";
        }
    }

    int CarStore::getTemperature() const
    {
        return this->temperature;
    }

    int CarStore::getActualTemperature() const
    {
        return this->actualTemperature;
    }

    void CarStore::setTempearture(int temperature)
    {
        if (temperature != this->temperature)
        {
            this->temperature = temperature;
            emit temperatureChanged(temperature);
        }
    }

    void CarStore::setActualTemperature(int actualTemperature)
    {
        if (actualTemperature != this->actualTemperature) {
            this->actualTemperature = actualTemperature;
            emit actualTemperatureChanged(actualTemperature);
        }
    }
} // namespace car
