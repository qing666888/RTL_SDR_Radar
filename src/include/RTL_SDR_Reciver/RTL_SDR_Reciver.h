#ifndef RTL_SDR_RECIVER_H
#define RTL_SDR_RECIVER_H

#include <QString>
#include <QSharedPointer>
#include <QVector>
#include <QDebug>
#include <QMutexLocker>

#include "RTL_SDR_Reciver/rtl_sdr_reciver_global.h"
#include "sdr_dev/include/rtl-sdr.h"
#include "sdr_dev/include/constant.h"

#include "interface/IReciverDevice.h"
#include "interface/ILogger.h"

class RTL_SDR_RECIVERSHARED_EXPORT RTL_SDR_Reciver : public IReciverDevice
{

    bool _isOpen = false;
    bool _isImit = false;
    char vendor[256], product[256], serial[256];

    int _dev_index = 0;
    int _gain = MODES_MAX_GAIN;
    int _enable_agc = 0;
    uint64_t _freq = MODES_DEFAULT_FREQ;

    QVector<uint8_t> _data;            /* Raw IQ samples buffer */
    rtlsdr_dev_t *_dev;
    QSharedPointer<ILogger> _loger;

    QMutex _mutex;
public:

    RTL_SDR_Reciver();
    ~RTL_SDR_Reciver() override;
    /*!
     * \brief открытие и инициализация устроства
     * \return  true - инициализация прошла удачно
     *          false - возникла ошибка
     */
    bool openDevice() override;
    bool isOpenDevice() override;
    void closeDevice() override;

    void setLogger(QSharedPointer<ILogger> log) override {_loger = log; }
    /*!
     * \brief перевод устроства в режим имитации,
     * если реально устроства нет
     * \return true - включен режим имитации,
     * false - работает реальное устроство
     */
    bool isImitMode() override { return _isImit; }
    /*!
     * \brief установка режима имитации
     * \param [in] state - включить или выключить имитацию
     * true - имитация включена, false - выключена
     */
    void setImitMode(bool state) override { _isImit = state; }

    QVector<uint8_t> getDataBlock(size_t size) override;
    const uint8_t *getDataBlockPtr(size_t size) override;
    bool readDataBlock(QVector<uint8_t> &vector, size_t size = MODES_DATA_LEN) override;
    void setFreq(uint32_t freq) override;
protected:
    bool initDevice() override;
};

#endif // RTL_SDR_RECIVER_H
