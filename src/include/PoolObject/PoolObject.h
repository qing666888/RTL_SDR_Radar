#ifndef POOLOBJECT_H
#define POOLOBJECT_H

#include "poolobject_global.h"

#include <QSharedPointer>
#include <QDateTime>
#include <QMutex>

#include "interface/IPoolObject.h"
#include "factory/FactoryObjects.h"

class Position;

class POOLOBJECTSHARED_EXPORT PoolObject : public IPoolObject
{
    pHash _container;
    QMutex _mutex;
    FactoryObjects _factory;
    OBJECT_TYPE _type = OBJECT_TYPE::base;
public:
    explicit PoolObject(OBJECT_TYPE type);
    ~PoolObject() override;

    QSharedPointer<IObject> createNewObject(uint64_t id,
                                            QDateTime reg_time,
                                            Position geoPosition,
                                            bool isImit) override;

    QList<QSharedPointer<IObject> > values() override;

    QList<QSharedPointer<IObject> > allValues() override;

    int getObjectsCount()  override;

    bool isExistsObject(uint64_t id) override;
    QSharedPointer<IObject> getObjectByID(uint64_t id) override;

    void prepareAllObjectToDelete() override;
    void deleteMarkedObjects() override;
    void deleteObject(uint64_t id) override;

    void lockPool() override { _mutex.lock(); }
    bool tryLockPool() override { return _mutex.tryLock(5);}
    void unlockPool() override { _mutex.unlock(); }
};

#endif // POOLOBJECT_H
