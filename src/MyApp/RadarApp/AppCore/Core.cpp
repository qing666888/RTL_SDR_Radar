#include "Core.h"
#include <QApplication>

#include "../MyLib/RTL_SDR_RadarLib/PoolObject/PoolObject.h"
#include "../MyLib/RTL_SDR_RadarLib/Logger/Logger.h"
#include "../MyLib/RTL_SDR_RadarLib/Carrier/Carrier.h"
#include "../MyLib/RTL_SDR_RadarLib/Carrier/ServiceLocator.h"
#include "../MyLib/RTL_SDR_RadarLib/DataController/DataController.h"
#include "../MyLib/RTL_SDR_RadarLib/RTL_SDR_Reciver/RTL_SDR_Reciver.h"
#include "../MyLib/RTL_SDR_RadarLib/Demodulator/Demodulator.h"
#include "../MyLib/RTL_SDR_RadarLib/GraphicsWidget/GraphicsWidget.h"
#include "publisher/Subject.h"

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
}

Core::~Core()
{
    _timer.stop();

    _dataController->stop();
    _dataController.clear();

    _device->closeDevice();
    _device.clear();

    _demodulator.clear();

    _subject->Deatach(_graphicsWidget);
    delete _graphicsWidget;
    _subject.clear();

    _poolObjects.clear();

    delete _mainWindow;
}

void Core::init()
{  
    _device = QSharedPointer<IReciverDevice>(new RTL_SDR_Reciver());
    _device->openDevice();

    ServiceLocator::provide(QSharedPointer<ICarrierClass>( new NullCarrier()) );

    _poolObjects = QSharedPointer<IPoolObject>(new PoolObject());
    _demodulator = QSharedPointer<IDemodulator>(new Demodulator(_poolObjects));

    _dataController = QSharedPointer<IDataController>(new DataController(_device,
                                                                         _demodulator));
    _dataController->run();

    _subject = QSharedPointer<ISubject>(new Subject());

    _mainWindow  = new MainWindow();
    _graphicsWidget = new GraphicsWidget(SIZE_WIDGET, _mainWindow);
    _graphicsWidget->subscribe(_subject);

    _mainWindow->addGraphicsWidget(_graphicsWidget);
    _mainWindow->adjustSize();
    _mainWindow->show();

    QObject::connect(&_timer, &QTimer::timeout, this, &Core::slotTimeout);
    _timer.start(TIMEOUT);
}

void Core::slotTimeout()
{
    if(_device && !_device->isOpenDevice())
        _device->openDevice();
}

