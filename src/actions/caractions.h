#ifndef CAR_ACTIONS_H
#define CAR_ACTIONS_H

#include <QObject>

namespace car
{
    class CarActions : public QObject
    {
        Q_OBJECT
    public:
        CarActions() = default;

        // functions invoked by QML
        Q_INVOKABLE void setTemperature(int temperature);

        // functions for C++ only
        void setActualTemperature(int actualTemperature);
    };
} // namespace car

#endif // CAR_ACTIONS_H
