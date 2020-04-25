#include <QDateTime>
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

#include "Aircraft.h"
#include "StructAircraft.h"

Aircraft::Aircraft(uint32_t icao, bool isImit) : BaseObject(icao,
                                                            QDateTime::currentDateTime(),
                                                            OBJECT_TYPE::air,
                                                            isImit,
                                                            Position())
{
    memset((char*)_flight, 0, SIZE_TEXT);
    _odd_cprlat = 0;
    _odd_cprlon = 0;
    _odd_cprtime = 0;
    _even_cprlat = 0;
    _even_cprlon = 0;
    _even_cprtime = 0;
    _messages = 1;
}

void Aircraft::setFlightInfo(char *val)
{
    if(val == nullptr)
        return;

    memcpy(_flight, val, sizeof(_flight));
    setObjectName(QString(_flight));
}

QString Aircraft::getFlightInfo() const
{
    return QString(_flight);
}

void Aircraft::setLongitude(double lon)
{
    _geoCoord.setLongitude(lon);
}

void Aircraft::setLatitude(double lat)
{
    _geoCoord.setLatitude(lat);
}

QString Aircraft::toString()
{
    QString str;
    str.append( QString("+++++++++++++++++++++++++++++++++++++\n"));
    str.append( QString("ICAO: %1\n").arg(getId(),6,16));
    str.append( QString("Flight number: %1\n").arg(QString(_flight)));
    str.append( QString("Altitude: %1\n").arg(_altitude));
    str.append( QString("Speed: %1\n").arg(_speed));
    str.append( QString("Course: %1\n").arg(_course));
    str.append( QString("Longitude: %1\n").arg(_geoCoord.longitude()));
    str.append( QString("Latitude: %1\n").arg(_geoCoord.latitude()));
    str.append( QString("Time last update: %1\n")
                .arg(getDateTimeStop().toString("hh:mm:ss.zzz")));
    str.append( QString("Number of Mode S messages received: %1\n").arg(_messages));
    str.append( QString("+++++++++++++++++++++++++++++++++++++\n"));

    return  str;
}

QByteArray Aircraft::serialize()
{
    QByteArray array;
    array.resize(sizeof (StructAircraft));

    StructAircraft a;
    a.icao = getICAO();

    memset((char*)a.flight, 0, sizeof (a.flight));
    memcpy((char*)a.flight, (char*)_flight, sizeof(a.flight));

    a.altitude = uint32_t(_altitude * VALUE_LSB);
    a.speed = uint32_t(_speed * VALUE_LSB);
    a.course = uint32_t(_course * VALUE_LSB);
    a.lon = int32_t(getLongitude() / LON_VALUE_LSB);
    a.lat = int32_t(getLatitude() / LAT_VALUE_LSB);
    a.seen = BaseObject::getMSecStop();
    a.messages = _messages;

    memcpy(array.data(), (char*)&a, sizeof (StructAircraft));

    return  array;
}

bool Aircraft::unserialize(QByteArray array)
{
    Q_UNUSED(array);
    return false;
}

uint32_t Aircraft::serializedFrameSize()
{
    return sizeof(StructAircraft);
}

void Aircraft::resetObjectData()
{
    BaseObject::resetObjectData();

    memset((char*)_flight, 0, SIZE_TEXT);
    _odd_cprlat = 0;
    _odd_cprlon = 0;
    _odd_cprtime = 0;
    _even_cprlat = 0;
    _even_cprlon = 0;
    _even_cprtime = 0;
    _messages = 0;
}

