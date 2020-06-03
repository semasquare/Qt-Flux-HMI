#include "caractions.h"

// global
#include <QVariant>

// local
#include "flux_qt/action.h"
#include "flux_qt/dispatcher.h"

// project
#include "actiontypes.h"

namespace car
{
    void CarActions::setTemperature(int temperature)
    {
        auto payload = QVariant::fromValue(temperature);
        auto type = ActionTypes::SetTemperature;

        auto action = QSharedPointer<flux_qt::Action>::create(type, payload);
        flux_qt::Dispatcher::instance().dispatch(action);
    }

    void CarActions::setActualTemperature(int actualTemperature)
    {
        auto payload = QVariant::fromValue(actualTemperature);
        auto type = ActionTypes::SetActualTemperature;

        auto action = QSharedPointer<flux_qt::Action>::create(type, payload);
        flux_qt::Dispatcher::instance().dispatch(action);
    }
} // namespace car
