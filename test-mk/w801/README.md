платка 
HLK-W801-KIT-V1.1

фото 1 
<p><img src="https://github.com/nvv13/test/blob/main/test-mk/w801/jpg/HLK-W801-KIT-V1.1.jpg" alt="HLK-W801-KIT-V1.1" title="HLK-W801-KIT-V1.1" /></p>

фото2
<p><img src="https://github.com/nvv13/test/blob/main/test-mk/w801/jpg/HLK-W801-KIT-V1-1.jpg" alt="HLK-W801-KIT-V1-1" title="HLK-W801-KIT-V1-1" /></p>


делал по инструкциям из этого проекта ( у меня Linux Fedora 33 x86_64 )
https://github.com/droppingy/W801_SDK-linux

1) первое замечание, насчет конденсатора
 Board : HLK-W801-KIT-V1.0 (add a capacitor (4.7uF) between GND and RESET)
   про это есть обьяснение в статье
   https://www.cnblogs.com/milton/p/15621540.html
   
   поскольку у меня платка HLK-W801-KIT-V1.1 , я конденсатор не припаял, и .. работает

2) второе, установка :
 Toolchain: <a href="https://github.com/droppingy/hlk-w80x-toolchain" title="csky-elfabiv2-tools-x86_64-minilibc-20210423"></a>
   я его скачат как zip архив
   потом распаковал в директорию /opt 
   так чтобы в итоге получилось /opt/w80x-tools/bin
   это чтоб в menuconfig не переделывать, такой там путь по умолчанию

3) далее, из домашней директории
$ mkdir w800
$ cd w800
$ git clone https://github.com/droppingy/W801_SDK-linux.git
  тут все по умолчанию подошло ( порт подключённой платки оказалься /dev/ttyUSB0 )
$ make menuconfig
$ make
  даже кнопку boot не пришлось нажимать ( когда пробовал проект на Arduino, там потребовалось, это я про https://github.com/Hi-LinkDuino/w80x_arduino )
$ make flash

  далее подцепляемся к платке, для ипользования демо проекта (60 функций!!!)
$ picocom --echo -b 115200 /dev/ttyUSB0
  после подсоединения платка "висит", это из за сигнала RTS (про это есть обьяснение в статье https://www.cnblogs.com/milton/p/15621540.html)
  поэтому делаем CTRL + A + G   - это комманда picocom - RTS down, (нажимать надо достаточно быстро, (одновременно, но сначала CTRL))
  и пользуемся ...
          выход из picocom - CTRL + A + Q  (это выход без сброса порта (Skipping tty reset...))
  и еще, у меня не удавалось в терминале, просто набрать комманду,
  но, если выделить, и вставить комманду через буфер обмена (дополнив чем надо - иногда) все работает!

  можно прямо отсюда выделять-(подправлять)-копировать...
Sequence  Command             Description
------------------------------------------------------------------------------------
1         t-connect           Test connecting ap;t-connect("ssid","pwd"); For open ap, pwd should be empty
2         t-oneshot           Test Oneshot  configuration
3         t-webcfg            Test web server configuration
4         t-apsta             Test connecting with AP by apsta mode;
5         t-asskt             Test socket communication in apsta mode;
6         t-softap            Test softap create & station join monitor;
7         t-scan              Test wifi scan
8         t-uart              Test uart tx/rx; For example t-uart=(9600,0,0),baudrate 9600 ,parity none and 1 stop bit
9         t-gpioirq           Test gpio interrupt services
10        t-gpio              Test gpio read and write
11        t-flash             Test Read/Write Flash 
12        t-crypt             Test Encryption/Decryption API
13        t-rsa               Test RSA Encryption/Decryption API
14        t-rtc               Test rtc
15        t-timer             Test timer
16        t-pwm               Test PWM output, for example t-pwm=(0,20,99,1,0) to test ALLSYC mode.
17        t-pmuT0             Test power management unit with timer0
18        t-pmuT1             Test power management unit with timer1
19        t-i2c               Test I2C module, for example t-i2c to W&R AT24CXX.
20        t-i2sioinit         Initialize I2S IO.
21        t-i2s               Test I2S module, for example t-i2s=(0,1,44100,16,0,0) to send data.
22        t-mspi-s            Test SPI Master sending data(Note: need another module acts as a client device)
23        t-mspi-r            Test SPI Master receiving data(Note: need another module acts as a client device)
24        t-sspi              Test slave HSPI,t-sspi=(0),(Note: need another module support as a master device)
25        t-sdh               Test sdio host write & read sd card
26        t-adctemp           (ADC)Test chip temperature
27        t-adcvolt           (ADC)Test input voltage,0-PA1(chan0), 1-PA4(chan1),8-different
28        t-adcpower          (ADC)Sample power supply voltage
29        t-7816              Test 7816 tx/rx function
30        t-sockc             Test data stream as [STANDARD SOCKET] CLIENT(working after connecting with AP successfully)
31        t-skcsnd            Test socket client send data, len:send len, uart_trans: is or not use uart retransmission
32        t-socks             Test data stream as [STANDARD SOCKET] SERVER(working after connecting with AP successfully)
33        t-skssnd            Test socket server send data skt_no:socket num, len:send len, uart_trans: is or not use uart retransmission
34        t-client            Test socket client; t-client("ssid","pwd",port,"ip")
35        t-server            Test socket server; t-server("ssid","pwd",port,)
36        t-udp               Test data stream as UDP(working after connecting with AP successfully)
37        t-sndudp            Test udp send data
38        t-ntp               Test NTP
39        t-setntps           Set NTP server ip;For example:t-setntps("cn.ntp.org.cn", "ntp.sjtu.edu.cn", "192.168.1.101"),max server num is 3
40        t-queryntps         Query the NTP server domain
41        t-httpfwup          Test firmware update via HTTP, like this t-httpfwup=(http://192.168.1.100:8080/WM_W600_SEC.img)
42        t-httpget           Test HTTP get method, like this t-httpget
43        t-httppost          Test HTTP post method, like this t-httppost=(user=winnermicro)
44        t-httpput           Test HTTP put method, like this t-httpput=(user=winnermicro)
45        t-ssl-server        Test ssl server,remember to turn on TLS_CONFIG_SERVER_SIDE_SSL
46        t-websockets        websockets demo test
47        t-https             Test https request
48        t-mbedtls           Test mbedtls ssl
49        t-mqtt              Test mqtt
50        t-fatfs             Test fatfs on sd card
51        t-dsp               DSP demo:0-fir,1-matrix,2-rfft,3-sin,4-variance
52        t-bt-on             Test enable bt system
53        t-bt-off            Test destroy bt system
54        t-ble-server-on     Test enable ble server
55        t-ble-server-off    Test disable ble server
56        t-ble-client-on     Test enable ble client
57        t-ble-client-off    Test disable ble client
58        t-ble-adv           Test start connectable/unconnectable/stop ble advertisement,eg: t-ble-adv=(1/2/0)
59        t-ble-scan          Test start/stop ble scan,eg: t-ble-scan=(1/0)
60        t-touch             Test Touch sensor function,0:all, 1:touch sensor 1... 15:touch sensor 15
61        demohelp            Display Help information
------------------------------------------------------------------------------------

например , берём t-connect("ssid","pwd") в блокнот
подправляем t-connect("mywifi2","94510984")
и вставляем в терминал...


4) что дальше?
  например, изучаем пиложенный файлик
  ~/w800/W801_SDK-linux/doc.w800_apis.chm
  а еще исходники этой demo программы, очень неплохо

  