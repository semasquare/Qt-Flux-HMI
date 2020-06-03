#ifndef CAR_SERVICE_H
#define CAR_SERVICE_H

#include <QObject>
#include <QTimer>

namespace car {
    class CarService : public QObject {
        Q_OBJECT
    private:
        int targetTemperature;
        int actualTemperature;
        QTimer actualTemperatureTimer;

        void setActualTemperature(int actualTemperature);
    public:
        CarService();

        void setTargetTemperature(int targetTemperature);

        void onActualTemperatureTimeout();

    Q_SIGNALS:
        void actualTemperatureChanged(int actualTemperature);
    };
}

#endif // CAR_SERVICE_H
