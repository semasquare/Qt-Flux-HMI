#ifndef ACTION_TYPES_H
#define ACTION_TYPES_H

#include <QObject>

class ActionTypes : public QObject

{
    Q_OBJECT

public:
    enum Enum
    {
        SetTemperature,
        SetActualTemperature
    };
    Q_ENUM(Enum)
};

#endif // ACTION_TYPES_H
