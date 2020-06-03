#ifndef FLUX_QT_DISPATCHER_H
#define FLUX_QT_DISPATCHER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>

#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QQueue>
#include <QtGlobal>
#include <QSharedPointer>
#include <QVector>

#include "middleware.h"
#include "store.h"

namespace flux_qt
{
class Action;

class Dispatcher final : public QObject
{
    Q_OBJECT

public:
    static Dispatcher &instance()
    {
        static Dispatcher self;
        return self;
    }

    void registerMiddleware(Middleware *middleware)
    {
        middlewares_.push_back(middleware);
    }

    void registerStore(Store *store)
    {
        stores_.push_back(store);
    }

    void dispatch(QSharedPointer<Action> action)
    {
        QMutexLocker locker(&mutex_);
        actions_.enqueue(action);

        emit newActionAdded();
    }

signals:
    void newActionAdded();

private:
    Dispatcher()
    {
        QObject::connect(this, &Dispatcher::newActionAdded, this, [this]() {
            this->onNewActionAdded();
        },
                         Qt::QueuedConnection);
    }

    Dispatcher(const Dispatcher &) = delete;
    Dispatcher(Dispatcher &&) = delete;
    Dispatcher &operator=(const Dispatcher &) = delete;
    Dispatcher &operator=(Dispatcher &&) = delete;
    ~Dispatcher() = default;

    void onNewActionAdded()
    {
        mutex_.lock();

        while (!actions_.empty())
        {
            auto action = actions_.dequeue();

            mutex_.unlock();

            for (const auto &middleware : middlewares_)
            {
                action = middleware->process(action);
            }

            for (const auto &store : stores_)
            {
                store->process(action);
            }

            mutex_.lock();
        }

        mutex_.unlock();
    }

    QVector<Middleware *> middlewares_;
    QVector<Store *> stores_;

    QQueue<QSharedPointer<Action>> actions_;
    QMutex mutex_;
};

} // namespace flux_qt

#endif
