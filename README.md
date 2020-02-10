# RTL_SDR_Radar

СПО для приема и демодуляции самолетных ответчиков на частоте 1090 МГц. 
Полученная информация выводится на картографическую проекцию основанную на openStreetMaps.

# RadarApp
АРМ "Пост контроля воздушного движения". Отвечает за приём, обработку и вывод информации о движении воздушных судов на картографическую проекцию, а так же дублирование данной информации в табличном представлении.
  Источником данных может выступать :
  - Приемник RTL-SDR v3
  - Сервер сбора данных от raspberry pi с подключенными к ним приемниками RTL-SDR v3.
![ezgif com-video-to-gif(1)](https://user-images.githubusercontent.com/34423525/74163125-f6beda00-4c32-11ea-9c2c-b9f83a039ed6.gif)

# RaspberryApp
Легковесное терминальное приложение для raspberry pi. Осуществляет приём, демодуляцию данных. 
Выполняет роль "выносного датчика". Полученная информация о самолётах упаковывается в бинарный формат (согласно внутреннему протоколу информационного сопряжения) и передается на сервер, для последующей обработки.
![Peek 2019-06-15 00-24](https://user-images.githubusercontent.com/34423525/59540975-1e28a000-8f08-11e9-9c11-43b84cbe69cf.gif)

Для приема сигналов используется :
1. Приемник RTL-SDR v3 на базе Realtek RTL2832 
2. Антенна Харченко 

Информация для изучения:
http://sdr.osmocom.org/trac/wiki/rtl-sdr
