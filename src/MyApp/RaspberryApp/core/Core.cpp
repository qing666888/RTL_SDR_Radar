#include <QApplication>
#include <QDebug>
#include "Core.h"
#include <QFile>

#include "../MyLib/RTL_SDR_RadarLib/PoolObject/PoolObject.h"
#include "../MyLib/RTL_SDR_RadarLib/Logger/Logger.h"
#include "../MyLib/RTL_SDR_RadarLib/Carrier/Carrier.h"
#include "../MyLib/RTL_SDR_RadarLib/Carrier/ServiceLocator.h"
#include "../MyLib/RTL_SDR_RadarLib/DataController/DataController.h"
#include "../MyLib/RTL_SDR_RadarLib/RTL_SDR_Reciver/RTL_SDR_Reciver.h"
#include "../MyLib/RTL_SDR_RadarLib/Demodulator/Demodulator.h"

Core::Core(QObject *parent) : QObject(parent)
{
    QFile File(QApplication::applicationDirPath()+"/../../../import/style.qss");
    if(File.open(QFile::ReadOnly))
    {
        QString StyleSheet = QLatin1String(File.readAll());
        qApp->setStyleSheet(StyleSheet);
    }
    else
        qDebug()<<"error load QSS file.Need filepath"
                 <<QApplication::applicationDirPath()+"/import/style.qss";

    _logger = QSharedPointer<ILogger>(new Logger(sizeLog));

    ServiceLocator::provide(QSharedPointer<ICarrierClass>( new NullCarrier()) );

    _device = QSharedPointer<IReciverDevice>(new RTL_SDR_Reciver());
    _device->setLogger(_logger);

    //пулл объектов для хранения объектов типа самолет
    _poolObjects = QSharedPointer<IPoolObject>(new PoolObject(OBJECT_TYPE::air));

    //демодулятор входного сигнала
    _demodulator = QSharedPointer<IDemodulator>(new Demodulator(_poolObjects,true));

    _demodulator->setLogger(_logger);

    _mainWindow.setLogger(_logger);
    _mainWindow.show();

    QObject::connect(&_timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    _timer.start(TIMEOUT);

}

Core::~Core()
{
    _timer.stop();
    _dataController->stop();

    _poolObjects.clear();
    _dataController.clear();
    _demodulator.clear();
    _device->closeDevice();
    _device.clear();
    _logger.clear();
}

void Core::init(const QString &ip, uint16_t port)
{

    _dataController = QSharedPointer<IDataController>(new DataController(_device,
                                                                         _demodulator,
                                                                         ip,
                                                                         port));
}


void Core::init()
{
    _dataController = QSharedPointer<IDataController>(new DataController(_device,
                                                                         _demodulator));
}

void Core::slotTimeout()
{
    if(_device && !_device->isOpenDevice())
    {
        if(_device->openDevice())
            _dataController->run();

    }
    _mainWindow.setOpenDevState((_device != nullptr) ? _device->isOpenDevice() : false);
}


