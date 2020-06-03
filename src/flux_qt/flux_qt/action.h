#ifndef FLUX_QT_ACTION_H
#define FLUX_QT_ACTION_H

#include <type_traits>
#include <utility>

#include <QVariant>

namespace flux_qt
{


class Action final
{
public:
    template <class ScopedEnum>
    Action(ScopedEnum type, QVariant &payload, bool error = false)
        : type_(static_cast<int>(type)), payload_(payload), error_(error)
    {
    }

    template <class ScopedEnum>
    Action(ScopedEnum type, QVariant &&payload = QVariant(), bool error = false)
        : type_(static_cast<int>(type)), payload_(std::move(payload)), error_(error)
    {
    }

    Action(const Action &) = default;
    Action(Action &&) = default;
    Action &operator=(const Action &) = default;
    Action &operator=(Action &&) = default;
    ~Action() = default;

    template <class ScopedEnum>
    ScopedEnum getType() const
    {
        return static_cast<ScopedEnum>(type_);
    }

    template <class T>
    T getPayload() const
    {
        if (!payload_.canConvert<T>()) {
            auto errorMessage = QString("unknown type %1").arg(payload_.toString());
            throw std::runtime_error(errorMessage.toLocal8Bit().constData());
        }

        return qvariant_cast<T>(payload_);
    }

    QVariant getPayloadVariant() const {
        return payload_;
    }

    bool getError() const
    {
        return error_;
    }

private:
    int type_;
    QVariant payload_;
    bool error_;
};

} // namespace flux_qt

#endif
