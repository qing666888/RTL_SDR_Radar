#проект будет состоять из набора модулей-подпроектов
TEMPLATE = subdirs

SUBDIRS += \
    src/MyLib/RTL_SDR_RadarLib \
    #src/MyApp/RadarApp \
    src/MyApp/RaspberryApp \
    #tests/TestServer
    #tests/PoolObjectsTest \
    #src/MyApp/ImitObjectsTest

CONFIG += ordered
