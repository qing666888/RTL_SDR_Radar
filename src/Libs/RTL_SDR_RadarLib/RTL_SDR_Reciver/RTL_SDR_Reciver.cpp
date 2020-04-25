
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#include "RTL_SDR_Reciver/RTL_SDR_Reciver.h"

RTL_SDR_Reciver::RTL_SDR_Reciver()
{
    qDebug()<<"create RTL_SDR_Reciver()";
}

RTL_SDR_Reciver::~RTL_SDR_Reciver()
{
    qDebug()<<"delete RTL_SDR_Reciver()";

    if(isOpenDevice())
        closeDevice();
}

bool RTL_SDR_Reciver::openDevice()
{
    QMutexLocker lock(&_mutex);
    _isOpen = initDevice();
    return _isOpen;
}

bool RTL_SDR_Reciver::isOpenDevice()
{
    QMutexLocker lock(&_mutex);
    return _isOpen;
}

void RTL_SDR_Reciver::closeDevice()
{
    if(!isOpenDevice())
        return;

    QString str = QString("%1: %2, %3, SN: %4 ").arg(_dev_index)
                                                .arg(vendor)
                                                .arg(product)
                                                .arg(serial);
    qDebug()<<"Close device: \n" <<str;

    if(!_loger.isNull())
        _loger->push("Close device: \n" + str);
    rtlsdr_cancel_async(_dev);
    rtlsdr_close(_dev);
    _isOpen = false;
}

QVector<uint8_t> RTL_SDR_Reciver::getDataBlock(size_t size)
{
    if(!isOpenDevice())
        QVector<uint8_t>();

    if ((size_t)_data.size() < size)
        _data.resize(size);

    int n_read = 0;
    rtlsdr_read_sync(_dev, _data.data(), size, &n_read);

    //qDebug()<<"getDataBlock() -> n_read = "<< n_read;
    return _data;
}

const uint8_t *RTL_SDR_Reciver::getDataBlockPtr(size_t size)
{
    if(!isOpenDevice())
        return nullptr;

    if ((size_t)_data.size() < size)
        _data.resize(size);

    int n_read = 0;
    rtlsdr_read_sync(_dev, _data.data(), size, &n_read);


    if(n_read != int(size))
    {
        qDebug()<<"need = " <<size <<"but read = "<<n_read;
        return nullptr;
    }

    return const_cast<const uint8_t *>(_data.data());
}

bool RTL_SDR_Reciver::readDataBlock(QVector<uint8_t> &vector, size_t size)
{
    if(!isOpenDevice())
        return false;

    if((size_t) vector.size() < size)
        vector.resize(size);

    int n_read = 0;
    int ret = rtlsdr_read_sync(_dev, vector.data(), int(size), &n_read);
    qDebug()<<"readDataBlock() -> n_read = "<< n_read;
    return (ret < 0) ? false : true;
}

void RTL_SDR_Reciver::setFreq(uint32_t freq)
{
    rtlsdr_set_center_freq(_dev,freq);
    qDebug()<<rtlsdr_get_center_freq(_dev);
}

bool RTL_SDR_Reciver::initDevice()
{
    int32_t device_count;
    int32_t ppm_error = 0;
    //    char vendor[256], product[256], serial[256];

    device_count = rtlsdr_get_device_count();
    if (!device_count)
    {
        qDebug()<<"No supported RTLSDR devices found";
        if(!_loger.isNull())
            _loger->push("No supported RTLSDR devices found");
        return false;
    }

    qDebug()<<"Found "<<device_count<<" device(s):";

    for (int32_t j = 0; j < device_count; j++)
    {
        rtlsdr_get_device_usb_strings(j, vendor, product, serial);

        QString str = QString("%1: %2, %3, SN: %4 ").arg(j).arg(vendor).arg(product).arg(serial);

        if(j == _dev_index)
            str.append("(currently selected)");

        qDebug()<<str;

        if(!_loger.isNull())
            _loger->push("Found "+ QString::number(device_count,10) + " device(s): \n" + str);

    }

    if (rtlsdr_open(&_dev, _dev_index) < 0)
    {
        qDebug()<<"Error opening the RTLSDR device: %s\n"
                 <<strerror(errno);

        return false;
    }

    /* Set gain, frequency, sample rate, and reset the device. */
    rtlsdr_set_tuner_gain_mode(_dev,
                               (_gain == MODES_AUTO_GAIN) ? 0 : 1);
    if (_gain != MODES_AUTO_GAIN)
    {
        if (_gain == MODES_MAX_GAIN)
        {
            /* Find the maximum gain available. */
            int numgains;
            int gains[100];

            numgains = rtlsdr_get_tuner_gains(_dev, gains);
            _gain = gains[numgains-1];
            qDebug()<<"Max available gain is: " << _gain / 10.0;
            qDebug()<<"Min available gain is: " << gains[0] / 10.0;
        }
        rtlsdr_set_tuner_gain(_dev, _gain);
        qDebug()<<"Setting gain to:" <<  _gain / 10.0;
    }
    else
        qDebug()<<"Using automatic gain control";

    rtlsdr_set_freq_correction(_dev, ppm_error);

    if (_enable_agc)
        rtlsdr_set_agc_mode(_dev, 1);

    rtlsdr_set_center_freq(_dev,_freq);
    qDebug()<<"Current freq is :"<< _freq / 1.0e6<< "MHz";

    rtlsdr_set_sample_rate(_dev, MODES_DEFAULT_RATE);

    qDebug()<<"Gain reported by device:" <<
        rtlsdr_get_tuner_gain(_dev) / 10.0;

    rtlsdr_reset_buffer(_dev);

    return true;
}


