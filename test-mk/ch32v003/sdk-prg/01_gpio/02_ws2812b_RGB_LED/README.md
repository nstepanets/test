
Платка CH32V003 на МК CH32V003F4P6 + ws2812b (60 LED)


Видео

https://youtu.be/A2lj6L-nhH0


соединения

надо соединить по схеме:
~~~
компоненты

(1)
ws2812b лента 

(2)
CH32V003F4P6



connect to
v003     WCH-LinkE
-----    ------ 
PD5(TX)   RX    - это чтобы увидеть вывод программы
                 $ picocom --echo -b 115200 /dev/ttyACM0 -подключаемся к WCH-LinkE 
SWD(PD1)  SWDIO
V         5V      только ленту не запитывайте с WCH-LinkE, это только для прошивки
G         GND    
-----    ------ 



connect to
v003   ws2812b лента 
-----  ------ 
PC1    data
+5v    +5v
GND    GND
-----  ------ 




~~~


