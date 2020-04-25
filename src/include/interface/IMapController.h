#ifndef IMAPCONTROLLER
#define IMAPCONTROLLER

#include <QImage>
#include <QObject>


enum class FILTER_TYPE
{
    NO = 0,
    NIGHT,
    NIGHT_AND_CIRCLE,
    CIRCLE
};

class Position;
class PolarCoord;

class IMapController : public QObject
{
    Q_OBJECT
public:
    virtual ~IMapController(){}

    /*!
     * \brief getImageMap - получение картографической основы в растровом формате
     * \param size - размер изображения
     * \param center - центральная точка карты (широта и долгота)
     * \param radius - радиус круга для режима локатора, учитывается только при
     * FILTER_TYPE  - NIGHT_AND_CIRCLE, CIRCLE
     * \param type - тип изображения (цветоное или наложение фильтра)
     * \return растровое изображение карты
     */
    virtual QImage getImageMap( const QSizeF &size,
                                const Position &center,
                                double radius = 0,
                                FILTER_TYPE filterType = FILTER_TYPE::NO) = 0;

    /*!
     * \brief getCenterGeoPoint центральная точка в географических координатах
     * \return текущее значение
     */
    virtual Position getCenterGeoPoint() const = 0;
    /*!
     * \brief setCenterGeoPoint - установка текущего значения центральной точки
     *  в географических координатах
     * \param geoCenter - значение широты и долготы
     */
    virtual void setCenterGeoPoint(const Position &geoCenter) = 0;

    /*!
     * \brief screenToRealPolar перевод экранных координат
     * в значения пеленг-дальность c учетом масштаба
     * пеленг в градусах, дальность в метрах
     * \param xy - значение экранных координат
     * \return  пеленг - дальность
     */
    virtual PolarCoord screenToRealPolar(const QSizeF &size,
                                         const Position &centerCoord,
                                         const QPointF &xy) = 0;
    /*!
     * \brief realPolarToScreen - перевод значения пеленг - дальность
     * в экранные координаты
     * пеленг в градусах, дальностьв метрах
     * \param size - размер картографической основы в пикселя
     * \param centerCoord - центральная геокоордината
     * \param plr - значение пеленг-дальность
     * \return экранные координаты
     */
    virtual QPointF realPolarToScreen(const QSizeF &size,
                                      const Position &centerCoord,
                                      const PolarCoord &plr) = 0;
    /*!
     * \brief screenToGeoCoordinates перевод экранных координат в
     * географические (широта и долгота)
     * \param size - размер картографической основы в пикселя
     * \param centerCoord - центральная геокоордината
     * \param point - экранная точка
     * \return значение геоокординаты
     */
    virtual Position screenToGeoCoordinates(const QSizeF &size,
                                            const Position &centerCoord,
                                            const QPointF &point) = 0;
    /*!
     * \brief geoToScreenCoordinates - перевод географисеких координат в
     * экранные (широта и догота)
     * \param size - размер картографической основы в пикселях
     * \param centerCoord - центральная геоточка
     * \param position - геокоордината точки для перевода
     * \return значений экранной координаты в пикселях
     */
    virtual QPointF geoToScreenCoordinates(const QSizeF &size,
                                           const Position &centerCoord,
                                           const Position &position) = 0;
    /*!
     * \brief getDistanceRadarScale_KM - дистанция в километрах от края до края карты
     * в текущем масштабе
     * \return дистанция в километрах
     */
    virtual double getDistanceRadarScale_KM(const QSizeF &size,
                                            const Position &centerCoordinate,
                                            const QPointF mapBorderCordinate) = 0;
    /*!
     * \brief getDistanceRadarScale_M - дистанция в метрах от края до края карты
     * в текущем масштабе
     * \return дистанция в метрах
     */
    virtual double getDistanceRadarScale_M(const QSizeF &size,
                                           const Position &centerCoordinate,
                                           const QPointF mapBorderCordinate) = 0;

    //масштаб
    virtual int getScale() = 0;
    virtual void setScale(uint8_t scale) = 0;
    virtual int incScale() = 0;
    virtual int decScale() = 0;

    /*!
     * \brief isVisibleInCurrentScale
     *  проверка попадает ли точка в область видимости
     * \param dist - дистанци в метрах
     * \return true если точка попадает в зону видимости
     */
    virtual bool isVisibleInCurrentScale(double dist) = 0;
    /*!
     * \brief getDistanceObject_KM - рассчёт дистанции
     * между точками в километрах
     * \param centerCoord - начальная координата
     * \param dot - конечная координата
     * \return  дистанция в км
     */
    virtual double getDistanceObject_KM(const Position &centerCoord,
                                        const Position &dot) = 0;

    /*!
     * \brief getDistanceObject_M - рассчёт дистанции
     * между точками в метрах
     * \param centerCoord - начальная координата
     * \param dot - конечная координата
     * \return  дистанция в метрах
     */
    virtual double getDistanceObject_M(const Position &centerCoord,
                                       const Position &dot) = 0;
signals:

};
#endif // IMAPCONTROLLER

