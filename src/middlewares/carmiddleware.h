#ifndef CAR_MIDDLEWARE_H
#define CAR_MIDDLEWARE_H

#include <QObject>

#include "flux_qt/action.h"
#include "flux_qt/middleware.h"

#include "actions/caractions.h"
#include "services/carservice.h"

namespace car
{
    class CarMiddleware : public QObject, public flux_qt::Middleware
    {
    private:
        CarActions *carActions;
        CarService carService;

        void onActualTemperatureChanged(int actualTemperature);

        void processSetTemperature(const QSharedPointer<flux_qt::Action> &action);
    public:
        CarMiddleware(CarActions *carActions);

        QSharedPointer<flux_qt::Action> process(const QSharedPointer<flux_qt::Action> &action);
    };
} // namespace car

#endif // CAR_MIDDLEWARE_H
