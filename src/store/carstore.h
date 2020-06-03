#ifndef CAR_STORE_H
#define CAR_STORE_H

#include <QObject>

#include "flux_qt/action.h"
#include "flux_qt/store.h"

namespace car
{
    class CarStore : public QObject, public flux_qt::Store
    {
        Q_OBJECT
        Q_PROPERTY(int temperature READ getTemperature NOTIFY temperatureChanged)
        Q_PROPERTY(int actualTemperature READ getActualTemperature NOTIFY actualTemperatureChanged)

    private:
        int temperature = 23;
        int actualTemperature = 0;

        void processTemperature(const QSharedPointer<flux_qt::Action> &action);

        void processActualTemperature(const QSharedPointer<flux_qt::Action> &action);

        void setTempearture(int temperature);
        void setActualTemperature(int actualTemperature);

    public:
        void process(const QSharedPointer<flux_qt::Action> &action);

        int getTemperature() const;
        int getActualTemperature() const;

    Q_SIGNALS:
        void temperatureChanged(int temperature);
        void actualTemperatureChanged(int actualTemperature);
    };
} // namespace car

#endif // CAR_STORE_H
