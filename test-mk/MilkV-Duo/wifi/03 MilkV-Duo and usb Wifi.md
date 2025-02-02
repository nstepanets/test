
фото milkv-duo and wifi
![photo](../jpg/milkv-duo%20and%20wifi.jpg)

фото milkv-duo 256m and wifi
![photo](../jpg/milkv-duo%20256m%20and%20wifi.jpg)




делал по статье, для WiFi читать с места "Build a new Milkv Duo image"
https://community.milkv.io/t/milkv-duo-mmdvm-wifi/1659


********************************************************************
~~~
Add LCD display and Wifi connection to MMDVM hotspot box controlled by Milkv Duo

The MMDVM box is a common device for global communication of digital radio stations
 when there is no local digital relay connected to the Internet or the local digital
 relay is far away.
MMDVM boxes usually use Raspberry Pi as the host computer to control
 the MMDVM single/duplex hotspot board. Compared with the MMDVM hotspot board,
 the Raspberry Pi is more expensive,
 so I tried to use the much cheaper Milkv Duo instead of the Raspberry Pi.

In the last article 2 (https://community.milkv.io/t/milkv-duo-mmdvm/1568),
 Milkv Duo cooperated with MMDVMHost to successfully control the MMDVM single/duplex hotspot board,
 but there are still some problems left:

no screen display
Official image RAM has too little free space
Can't connect via Wifi
This time, 1602 LCD is used for display, and RTL8188 series wireless network card is used to realize Wifi networking.

The LCD driver of MMDVMHost needs to be adapted.
 This article only provides the warehouse after the adaptation is completed.
 In addition, there may be open source agreement conflicts, and no guarantee is provided.

This article only gives the deployment process.
 The tool chain also uses the tool chain installed by RUYI package manager.
 Please refer to the previous article for the specific installation method.

**********************************************************************
Build wiringX

wiringX is used to drive GPIO.
 Milkv Duo's wiringX support has recently been merged into the mainline,
 and the documentation of the mainline branch and Milkv Duo will be slightly different,
 so wiringX needs to use the latest mainline.
 Please modify the DESTDIR variable according to the actual situation.


------------------------------------------begin------------------------------------------
$ git clone --depth=1 https://github.com/wiringx/wiringX.git
$ cd wiringX
$ mkdir build
$ cd build
$ cmake ..  -DCMAKE_C_COMPILER=riscv64-plct-linux-gnu-gcc
$ make -j4
$ make install DESTDIR=<ruyi_venv_dir>/venv-duo/wiringx
------------------------------------------end--------------------------------------------


*******************************************************************
Build MMDVMHost

MMDVMHost itself is designed to run on Raspberry Pi,
 so it uses wiringPi as the GPIO driver.
 In order to enable it to drive 1602 LCD on Milkv Duo,
 wiringX has been adapted here and is open sourced in the repository as shown below.

During the adaptation process, some wiringPi libraries were slightly modified and used,
 so there is a suspected source code protocol conflict, and we don’t know how to solve it yet.

------------------------------------------begin------------------------------------------
$ git clone https://github.com/weilinfox/MMDVMHost_Duo.git -b duo
$ cd MMDVMHost_Duo
------------------------------------------end--------------------------------------------

Modify the Makefile, tool chain name and location of dependent libraries according to the actual situation.
 Here is a patch as a description

------------------------------------------begin patch------------------------------------------
--- Makefile.Duo.HD44780        2024-03-24 23:38:17.995092253 +0800
+++ Makefile.Duo.HD44780.use    2024-03-20 23:18:25.395561053 +0800
@@ -1,9 +1,9 @@
 # This makefile is for use with the Raspberry Pi when using an HD44780 compatible display. The wiringpi library is needed.
 
-CC      = riscv64-unknown-linux-musl-gcc
-CXX     = riscv64-unknown-linux-musl-g++
-CFLAGS  = -g -O3 -Wall -std=c++0x -pthread -DHAVE_LOG_H -DHD44780 -I/usr/local/include/
-LIBS    = -lwiringx -lpthread -lutil -lsamplerate -L/usr/local/lib/
+CC      = riscv64-plct-linux-gnu-gcc
+CXX     = riscv64-plct-linux-gnu-g++
+CFLAGS  = -g -O3 -Wall -std=c++0x -pthread -DHAVE_LOG_H -DHD44780 -I/home/hachi/Documents/Working/ruyi-venv/venv-duo/libsamplerate/usr/local/include/ -I/home/hachi/Documents/Working/ruyi-venv/venv-duo/wiringx/usr/local/include/
+LIBS    = -lwiringx -lpthread -lutil -lsamplerate -L/home/hachi/Documents/Working/ruyi-venv/venv-duo/libsamplerate/usr/local/lib/ -L/home/hachi/Documents/Working/ruyi-venv/venv-duo/wiringx/usr/local/lib/
 LDFLAGS = -g -static
 
 OBJECTS = \
------------------------------------------end patch--------------------------------------------

Construct.

------------------------------------------begin------------------------------------------
make -f Makefile.Duo.HD44780 -j4
------------------------------------------end--------------------------------------------


********************************************
Install 1602 LCD

Since I don’t want to use the duo-pinmux command to manually modify the pin function,
 I selected the pin with the default GPIO function for connecting to the 1602 LCD.
 The measured 5V LCD can be driven normally.

First, the configuration related to 1602 in MMDVM.ini is given.

------------------------------------------begin------------------------------------------
[General]
Display=HD44780

[HD44780]
Rows=2
Columns=16
# rs, strb, d0, d1, d2, d3
Pins=16,17,18,19,20,21
------------------------------------------end--------------------------------------------

Hardware connections are shown in the table below.

------------------------------------------begin------------------------------------------
MilkvDuo 1602
GND      VSS
VBUS     VDD
-        VO
GP16     RS
GND      RW
GP17     E
-        D0
-        D1
-        D2
-        D3
GP18     D4
GP19     D5
GP20     D6
GP21     D7
VBUS     A
GND      K
------------------------------------------end--------------------------------------------

VO is the display bias voltage,
 which can be connected to GND with a potentiometer for adjustment;
 in addition, since MMDVMHost adopts a 4-wire connection scheme, D0-D3 are left floating.

MMDVMHost also provides PWM-based dynamic backlighting.
 Although wiringX does not appear to have PWM support, MMDVMHost also provides software-based PWM backlight control.
 However, these require auxiliary circuits to implement, and you can solve them yourself if necessary.


********************************************************************
Build a new Milkv Duo image
Создайте новый образ Milkv Duo.

The purpose of refactoring the image is to increase available RAM
 and kernel with RTL8188 wireless card driver.
Целью рефакторинга образа является увеличение доступной оперативной памяти
 + сборка ядра с драйвером беспроводной карты RTL8188.

Start by cloning the latest mainline branch.
Начните с клонирования последней основной ветки.


$ git clone https://github.com/milkv-duo/duo-buildroot-sdk.git
$ cd duo-buildroot-sdk

Note that the latest mainline branch requires building the image in the Ubuntu 22.04 LTS environment,
 which requires preparation by yourself.
Обратите внимание, что последняя основная ветка требует сборки образа в среде Ubuntu 22.04 LTS,
 что требует самостоятельной подготовки. (я собирал с помощью docker)

Here is a patch that turns on all Realtek USB wireless network card driver options available in the SDK
 and increases the root directory size to 2G.
Вот патч, который включает все параметры драйвера беспроводной сетевой карты Realtek USB, доступные в SDK,
 и увеличивает размер корневого каталога до 2G.

------------------------------------------begin patch------------------------------------------
diff --git a/build/boards/cv180x/cv1800b_milkv_duo_sd/linux/cvitek_cv1800b_milkv_duo_sd_defconfig b/build/boards/cv180x/cv1800b_milkv_duo_sd/linux/cvitek_cv1800b_milkv_duo_sd_defconfig
index 1f387e7cd..c16084651 100644
--- a/build/boards/cv180x/cv1800b_milkv_duo_sd/linux/cvitek_cv1800b_milkv_duo_sd_defconfig
+++ b/build/boards/cv180x/cv1800b_milkv_duo_sd/linux/cvitek_cv1800b_milkv_duo_sd_defconfig
@@ -346,3 +346,23 @@ CONFIG_EPOLL=y
 CONFIG_ELF_CORE=y
 CONFIG_COREDUMP=y
 CONFIG_PROC_SYSCTL=y
+
+# wifi
+CONFIG_CFG80211=y
+CONFIG_WIRELESS=y
+CONFIG_MAC80211=y
+CONFIG_MAC80211_LEDS=y
+CONFIG_RFKILL=y
+
+CONFIG_WLAN=y
+CONFIG_WLAN_VENDOR_REALTEK=y
+
+CONFIG_RTL8187=y
+
+CONFIG_RTLWIFI=y
+CONFIG_RTL8192C_COMMON=y
+CONFIG_RTL8192CU=y
+
+CONFIG_RTL8XXXU=y
+
+CONFIG_RTL8188FU=y
diff --git a/build/boards/cv180x/cv1800b_milkv_duo_sd/memmap.py b/build/boards/cv180x/cv1800b_milkv_duo_sd/memmap.py
index 84161267a..388895702 100644
--- a/build/boards/cv180x/cv1800b_milkv_duo_sd/memmap.py
+++ b/build/boards/cv180x/cv1800b_milkv_duo_sd/memmap.py
@@ -40,7 +40,7 @@ class MemoryMap:
     # =================
     # Multimedia buffer. Used by u-boot/kernel/FreeRTOS
     # =================
-    ION_SIZE = 26.80078125 * SIZE_1M
+    ION_SIZE = 0
     H26X_BITSTREAM_SIZE = 0 * SIZE_1M
     H26X_ENC_BUFF_SIZE = 0
     ISP_MEM_BASE_SIZE = 0 * SIZE_1M
diff --git a/device/milkv-duo/genimage.cfg b/device/milkv-duo/genimage.cfg
index 71938363b..943583bd3 100644
--- a/device/milkv-duo/genimage.cfg
+++ b/device/milkv-duo/genimage.cfg
@@ -13,7 +13,7 @@ image rootfs.ext4 {
        ext4 {
                label = "rootfs"
        }
-       size = 768M
+       size = 1700M
 }
 
 image milkv-duo.img {
------------------------------------------end patch-------------------------------------------

Note
 that although there is an RTL8188EU driver in the staging directory,
 it is broken, at least it cannot drive RTL8188EUS.
 The last section of this article gives the available out-of-tree drivers for RTL8188EUS.
Обратите внимание:
 хотя в промежуточном каталоге есть драйвер RTL8188EU,
 он сломан, по крайней мере, он не может управлять RTL8188EUS.
 В последнем разделе этой статьи представлены доступные внешние драйверы для RTL8188EUS. (я это не пробовал, у меня была RTL8188)

After testing,
 there are no problems with the RTL8188CU and RTL8188FTV modules.
 The onboard type-c interface and OTG adapter can also be directly plugged into the RTL8188CU USB network card.
После тестирования
 с модулями RTL8188CU и RTL8188FTV проблем не возникло.
 Встроенный интерфейс Type-C и адаптер OTG также можно напрямую подключить к сетевой USB-карте RTL8188CU. (с OTG и делал)

Start building the image.
 Note
 that if you use a normal user to build the image,
 you need to add /usr/sbin to the PATH environment variable.
Начните создание образа.
 Обратите внимание:
 если для создания образа вы используете обычного пользователя,
 вам необходимо добавить /usr/sbin в переменную среды PATH.

------------------------------------------begin------------------------------------------

$ export PATH=/usr/sbin:$PATH
$ ./build.sh milkv-duo

INFO: hdimage(milkv-duo.img): writing MBR
gnimage for milkv-duo success!
~/duo-buildroot-sdk/build
~/duo-buildroot-sdk
Create SD image successful: out/milkv-duo-20240327-1236.img

------------------------------------------end--------------------------------------------

Edit the image,
 enable host mode for USB,
 and put in scripts for Wifi connection and MMDVMHost startup.
Отредактируйте образ,
 включите режим хоста для USB
 и добавьте сценарии для подключения Wi-Fi и запуска MMDVMHost.

------------------------------------------begin------------------------------------------
$ sudo mkdir /mnt/sd
$ sudo mount -o loop,offset=134218240 ./duo-buildroot-sdk/out/milkv-duo-20240327-1236.img /mnt/sd
$ rm /mnt/sd/mnt/system/usb.sh
$ ln -sf /mnt/system/usb-host.sh /mnt/sd/mnt/system/usb.sh
$ cp ethtool /mnt/sd/usr/local/bin/
$ mkdir /mnt/sd/opt/MMDVMHost
$ cp MMDVMHost RemoteCommand /mnt/sd/opt/MMDVMHost/
$ mcedit /mnt/sd/opt/MMDVMHost/start_mmdvm
------------------------------------------end--------------------------------------------

The contents of the start_mmdvm script are given here.
 This time, the addition of mmdvm users is written into the script.
Здесь приведено содержимое скрипта start_mmdvm.
 На этот раз в скрипт прописано добавление пользователей mmdvm.


------------------------------------------begin start_mmdvm------------------------------------------
#/bin/sh

echo Check Internet Connection
while ! ping -c 1 bing.com 2>&1 > /dev/null; do
        sleep 5s
done

echo Check NTP time update
wt=1
while [ `date '+%Y'` = 1970 ]; do
        wt=`expr $wt + 1`
        if [ $wt -ge 30 ]; then
                echo Wait NTP timeout 30s
                break
        fi
        try $wt
        sleep 1s
done

if ! grep mmdvm /etc/shadow; then
        echo No mmdvm user and group found, add them
        addgroup mmdvm
        adduser -H -D -S -G mmdvm -s /bin/false mmdvm
fi

echo Start MMDVMHost
[ -d /var/log/mmdvm ] || mkdir /var/log/mmdvm
chown mmdvm:mmdvm /var/log/mmdvm /dev/ttyS4
/opt/MMDVMHost/MMDVMHost
------------------------------------------end start_mmdvm--------------------------------------------

Make it executable.
Сделайте его исполняемым.

------------------------------------------begin------------------------------------------
$ chmod +x /mnt/sd/opt/MMDVMHost/start_mmdvm
------------------------------------------end--------------------------------------------

Create a self-starting script.
Создайте самозапускающийся скрипт.

------------------------------------------begin------------------------------------------
$ mcedit /mnt/sd/etc/init.d/S99zuser
------------------------------------------end--------------------------------------------

The script content is given here,
 which mainly adds the function of Wifi connection.
Здесь приведено содержимое скрипта,
 который в основном добавляет функцию подключения Wi-Fi.

------------------------------------------begin script------------------------------------------
#!/bin/sh
${CVI_SHOPTS}
#
# Control eth0 speed and start wpa_supplicant
#

set_network() {
  if [ -f /mnt/system/ko/8188eu.ko ]; then
    echo Insmod 8188eu.ko
    insmod /mnt/system/ko/8188eu.ko
    sleep 1s
  fi
  if /sbin/ip link | grep eth0; then
    echo Set eth0 to 10Mbps
    ethtool -s eth0 speed 10
  fi
  if /sbin/ip link | grep wlan0; then
    echo Check wifi config
    [ -f /etc/wpa_supplicant/wpa_supplicant.conf ] && wpa_supplicant -B -Dnl80211 -iwlan0 -c/etc/wpa_supplicant/wpa_supplicant.conf
  fi
}

case "$1" in
  start)
        set_network 2>&1 > /var/log/mylog
        /opt/MMDVMHost/start_mmdvm >> /var/log/mylog &
        ;;
  stop)
        ;;
  restart|reload)
        ;;
  *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
esac

exit $?
------------------------------------------end script--------------------------------------------

Here, ethtool is used to limit the wired network to 10Mbps.
 This is mainly due to the unstable connection
 caused by unscientific routing of the homemade backplane.
 Not required if no issues are found at 100Mbps.
Здесь ethtool используется для ограничения проводной сети до 10 Мбит/с.
 В основном это связано с нестабильным соединением,
 вызванным ненаучной маршрутизацией самодельной объединительной платы.
 Не требуется, если при скорости 100 Мбит/с проблем не обнаружено.

Regarding Wifi configuration,
 although there is a configuration file in /etc/wpa_supplicant.conf by default,
 it is not intended to be used here.
 The script will start wpa_supplicant based on the configuration in /etc/wpa_supplicant/wpa_supplicant.conf.
Что касается конфигурации Wi-Fi,
 хотя по умолчанию в /etc/wpa_supplicant.conf есть файл конфигурации,
 он не предназначен для использования здесь.
 Сценарий запустит wpa_supplicant на основе конфигурации в /etc/wpa_supplicant/wpa_supplicant.conf.

Likewise, make it executable.
Аналогичным образом сделайте его исполняемым.

------------------------------------------begin------------------------------------------
$ chmod +x /mnt/sd/etc/init.d/S99zuser
------------------------------------------end--------------------------------------------

Now you can start the configuration of MMDVMHost and Wireless LAN Wifi.
 Of course, the specific content of MMDVM.ini is not involved here.
Теперь вы можете приступить к настройке MMDVMHost и беспроводной локальной сети Wi-Fi.
 Разумеется, конкретное содержимое MMDVM.ini здесь не задействовано.


------------------------------------------begin------------------------------------------
$ cp MMDVM.ini /mnt/sd/etc
$ mkdir /mnt/sd/etc/wpa_supplicant
$ mcedit /mnt/sd/etc/wpa_supplicant/wpa_supplicant.conf
------------------------------------------end--------------------------------------------

For wpa_supplicant.conf, you can refer to the following content.
Для wpa_supplicant.conf вы можете обратиться к следующему содержимому.

------------------------------------------begin wpa_supplicant.conf------------------------------------------
network={
    ssid="youmu46"
    psk="youmu464646."
}
------------------------------------------end wpa_supplicant.conf--------------------------------------------

Now that you are done, dd the image to the Micro SD card and start Milkv Duo.
Теперь, когда все готово, скопируйте образ на карту Micro SD и запустите Milkv Duo.

------------------------------------------begin------------------------------------------
$ sudo umount /mnt/sd
$ sudo sync
$ sudo sync
$ sudo sync
$ sudo dd if=./duo-buildroot-sdk/out/milkv-duo-20240327-1236.img of=/dev/mmcblk0 bs=4M status=progress
------------------------------------------end--------------------------------------------

Check whether the connection is normal in the management interface of the router.
 If not, connect to the wired network to check the situation.
Проверьте, нормально ли соединение в интерфейсе управления роутером.
 Если нет, подключитесь к проводной сети, чтобы проверить ситуацию.

Finally check the available RAM with MMDVMHost started.
Наконец, проверьте доступную оперативную память, запустив MMDVMHost.

------------------------------------------begin------------------------------------------
# free -m
              total        used        free      shared  buff/cache   available
Mem:             54          16          26           0          12          35
Swap:             0           0           0
------------------------------------------end--------------------------------------------

It can be seen that it is very abundant.
Видно, что его очень много.



*********************************************************************************************
RTL8188EU driver
Драйвер RTL8188EU

There are multiple driver repositories on GitHub,
 and one is confirmed to be available after testing.
На GitHub есть несколько репозиториев драйверов,
 и после тестирования было подтверждено, что один из них доступен.


------------------------------------------begin------------------------------------------
$ git clone https://github.com/ivanovborislav/rtl8188eu.git
$ cd rtl8188eu
------------------------------------------end--------------------------------------------

Note
 that since you are building the kernel module,
 you need to use the same tool chain as building the image.
 Here it is riscv64-unknown-linux-musl-gcc,
 and its download address can be obtained from the build script of duo-buildroot-sdk.
Обратите внимание:
 поскольку вы собираете модуль ядра,
 вам необходимо использовать ту же цепочку инструментов, что и для сборки образа.
 Здесь это riscv64-unknown-linux-musl-gcc,
 а его адрес загрузки можно получить из сценария сборки duo-. buildroot-sdk.

First edit the Makefile and throw a patch here.
Сначала отредактируйте Makefile и закиньте сюда патч.

------------------------------------------begin patch------------------------------------------
diff --git a/Makefile b/Makefile
index 3d08dac..1398980 100644
--- a/Makefile
+++ b/Makefile
@@ -142,7 +142,7 @@ CONFIG_LAYER2_ROAMING = y
 #bit0: ROAM_ON_EXPIRED, #bit1: ROAM_ON_RESUME, #bit2: ROAM_ACTIVE
 CONFIG_ROAMING_FLAG = 0x3
 ###################### Platform Related #######################
-CONFIG_PLATFORM_I386_PC = y
+CONFIG_PLATFORM_I386_PC = n
 CONFIG_PLATFORM_RPI_ARM = n
 CONFIG_PLATFORM_RPI_ARM64 = n
 CONFIG_PLATFORM_ANDROID_X86 = n
@@ -206,6 +206,7 @@ CONFIG_PLATFORM_NV_TK1_UBUNTU = n
 CONFIG_PLATFORM_RTL8197D = n
 CONFIG_PLATFORM_AML_S905 = n
 CONFIG_PLATFORM_ZTE_ZX296716 = n
+CONFIG_PLATFORM_MILKV_DUO = y
 ########### CUSTOMER ################################
 CONFIG_CUSTOMER_HUAWEI_GENERAL = n
 
@@ -2329,6 +2330,11 @@ endif
 
 endif
 
+ifeq ($(CONFIG_PLATFORM_MILKV_DUO), y)
+EXTRA_CFLAGS += -DCONFIG_LITTLE_ENDIAN
+EXTRA_CFLAGS += -DCONFIG_IOCTL_CFG80211 -DRTW_USE_CFG80211_STA_EVENT
+endif
+
 ########### CUSTOMER ################################
 ifeq ($(CONFIG_CUSTOMER_HUAWEI_GENERAL), y)
 CONFIG_CUSTOMER_HUAWEI = y
------------------------------------------end patch--------------------------------------------

Build it.
Собираем.

------------------------------------------begin------------------------------------------
$ KSRC=~/duo-buildroot-sdk/linux_5.10/build/cv1800b_milkv_duo_sd CROSS_COMPILE=~/duo-buildroot-sdk/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl- make -j4
------------------------------------------end--------------------------------------------

Finally,
 we get 8188eu.ko and install it in the /mnt/system/ko directory of the Milkv Duo image.
 The S99zuser script given above will automatically load the module when it is found to exist.
Наконец,
 мы получаем 8188eu.ko и устанавливаем его в каталог /mnt/system/ko образа Milkv Duo.
 Приведенный выше сценарий S99zuser автоматически загрузит модуль, когда обнаружит его существование.

**********************************************************

end

At this point,
 a complete and independent MMDVM box is completed.
 As an experimental version of hand rubbing,
 it has been running stably for two weeks.

.

~~~
