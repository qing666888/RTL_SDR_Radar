#include "BaseObject.h"

BaseObject::BaseObject(uint64_t id,
                       QDateTime tstart,
                       double azimuth,
                       double elevation,
                       OBJECT_TYPE type,
                       bool isImit):
    _id(id),
    _typeObject(type),
    _isImitate(isImit),
    _ms_tstart(tstart.toUTC().toMSecsSinceEpoch()),
    _tstart(tstart),
    _ms_tstop(tstart.toUTC().toMSecsSinceEpoch()),
    _tstop(tstart),
    _azimuth(azimuth),
    _elevation(elevation)
{
    _uuid = QUuid::createUuid();
}

BaseObject::BaseObject(uint64_t id,
                       QDateTime tstart,
                       OBJECT_TYPE type,
                       bool isImit,
                       Position geoPosition) :
    _id(id),
    _typeObject(type),
    _isImitate(isImit),
    _ms_tstart(tstart.toUTC().toMSecsSinceEpoch()),
    _tstart(tstart),
    _ms_tstop(tstart.toUTC().toMSecsSinceEpoch()),
    _tstop(tstart),
    _geoCoord(geoPosition)
{
    _uuid = QUuid::createUuid();
}

BaseObject::~BaseObject()
{
}

QUuid BaseObject::getUuid()
{
    return  _uuid;
}

void BaseObject::setId(uint64_t id)
{
    _id = id;
}

uint64_t BaseObject::getId() const
{
    return _id;
}

void BaseObject::setDateTimeStart(const QDateTime &dt)
{
    _tstart = dt;
    _ms_tstart = _tstart.toUTC().toMSecsSinceEpoch();
}

QDateTime BaseObject::getDateTimeStart() const
{
    return _tstart;
}

void BaseObject::setDateTimeStop(const QDateTime &dt)
{
    _tstop = dt;
    _ms_tstop = _tstop.toUTC().toMSecsSinceEpoch();
}

QDateTime BaseObject::getDateTimeStop() const
{
    return _tstop;
}

void BaseObject::setMSecStart(const qint64 dt)
{
    _ms_tstart = dt;
    _tstart = QDateTime::fromMSecsSinceEpoch(dt).toUTC();
}

qint64 BaseObject::getMSecStart() const
{
    return _ms_tstart;
}

void BaseObject::setMSecStop(const qint64 dt)
{
    _ms_tstop = dt;
    _tstop = QDateTime::fromMSecsSinceEpoch(dt).toUTC();
}

qint64 BaseObject::getMSecStop() const
{
    return _ms_tstop;
}

void BaseObject::setObjectState(OBJECT_STATE state)
{
    _state = state;

    if((state == OBJECT_STATE::UPDATE_OBJECT) ||
            (state == OBJECT_STATE::NEW_OBJECT))
        setInUse(true);

    if(state == OBJECT_STATE::DELETE_OBJECT)
        setInUse(false);
}

OBJECT_STATE BaseObject::getObjectState()
{
    return _state;
}

void BaseObject::setObjectName(const QString &str)
{
    _nameObject = str;
}

QString BaseObject::getObjectName()
{
    return _nameObject;
}

void BaseObject::setAzimuth(double azim)
{
    _azimuth = azim;
}

double BaseObject::getAzimuth() const
{
    return _azimuth;
}

void BaseObject::setElevation(double elev)
{
    _elevation = elev;
}

double BaseObject::getElevation() const
{
    return _elevation;
}

void BaseObject::setDistance_M(double dist)
{
    _distance = dist;
}

double BaseObject::getDistance_M() const
{
    return _distance;
}

void BaseObject::setDistance_KM(double dist)
{
    _distance = dist * 1.0e3;
}

double BaseObject::getDistance_KM()
{
    return _distance / 1.0e3;
}

void BaseObject::setGeoCoord(const Position &gp)
{
    _geoCoord = gp;
}

Position BaseObject::getGeoCoord() const
{
    return _geoCoord;
}

bool BaseObject::isValidGeoCoord()
{
    return ((_geoCoord.latitude() > -90.0 && _geoCoord.latitude() < 90.0) &&
            (_geoCoord.longitude() > -180.0 && _geoCoord.longitude() < 180.0));
}

void BaseObject::setSpeed(float value)
{
    _speed = value;
}

float BaseObject::getSpeed() const
{
    return _speed;
}

void BaseObject::setCourse(float crs)
{
    _course = crs;
}

float BaseObject::getCourse()
{
    return _course;
}


void BaseObject::setInUse(bool value)
{
    _inUse = value;
}

bool BaseObject::getInUse()
{
    return _inUse;
}

void BaseObject::resetObjectData()
{
    _id = 0;
    _nameObject = QString("--");
    _state = OBJECT_STATE::DELETE_OBJECT;
    _inUse = false;
    _tstart = QDateTime();
    _tstop = QDateTime();
    _ms_tstart = 0;
    _ms_tstop = 0;

    _geoCoord = Position(-200.0,-200.0);
    _speed = 0.0;
    _course = 0.0;
    _azimuth = 0.0;
    _elevation = 0.0;
    _distance = 0.0;
    _altitude = 0.0;
    _isImitate = false;
}

float BaseObject::getAltitude() const
{
    return _altitude;
}

void BaseObject::setAltitude(float altitude)
{
    _altitude = altitude;
}

bool BaseObject::isImitated()
{
    return _isImitate;
}

OBJECT_TYPE BaseObject::getTypeObject()
{
    return  _typeObject;
}
