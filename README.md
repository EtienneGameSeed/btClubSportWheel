<<<<<<< HEAD
# Node Blue Fanatec Module
ClubSportWheel USBRadio Controller

This [Node Blue](httpwww.nodeblue.orggui) module can convert any Fanatec CSW Steering Wheel to a standalone USB or Radio version, so you can use it with any other wheel base.
I recommend to use ElectroSeed [TBB_02 board](httpswww.electroseed.frshopproduct_info.phpproducts_id=139) for USB or Radio version, as it's plug and play (you'll only need to connect the jst cable to the rim).

## Supported Hardware
This firmware has been developed and tested on a Teensy 3.2 and Teensy LC but should work with any other compatible hardware.  
=======
# btClubSportWheel
ClubSportWheel USB Controller

This firmware can convert any Fanatec CSW Steering Wheel to a **standalone USB version**, so you can use it with any other wheel base, like an OpenSimWheel (OSW).

It'll also be possible to add a bluetooth module to go wireless and get rid of the USB cable (**deprecated**).

## Supported Hardware
This firmware has been developed and tested on a **Teensy 3.1** and **Teensy LC** but should work with any other compatible hardware.  
>>>>>>> v1.2-rc1
The only requirement so far, is at least 1 SPI connectivity available.

The Teensy-LC is a good choice for this project as it has a small size & price.

<<<<<<< HEAD
### Shopping List
#### USB version
[TBB_02 board](httpswww.electroseed.frshopproduct_info.phpproducts_id=139) 38.10€ inc. VAT (Including Teensy LC)

#### Radio upgrade
- [TBB_02 board](httpswww.electroseed.frshopproduct_info.phpproducts_id=139) from 43.70€ inc. VAT (Including Teensy LC)
- [LeoDongle](httpswww.electroseed.frshopproduct_info.phpproducts_id=58) 20.10€ inc. VAT
Powering  
- [Induction kit](httpswww.electroseed.frshopproduct_info.phpproducts_id=166) 32.30€ inc. VAT
Or
- [Adafruit PowerBoost 500 Charger](httpswww.adafruit.comproducts1944)  ~15$
- [LiPo Battery (=1000mA)](httpswww.adafruit.comcategories138)  ~10$

### Pinout & schematics
#### Fanatec Plug
![Fanatec Round Plug](httpi.imgur.comyLSG0Jsm.jpg)
=======
### Note on the Bluetooth version
I don't recommend the bluetooth version for now.  
It's still a work in progress, and there is a few issues with Fanaleds, occasionally inducing some input lags, and an incompatibility with Windows 10.

If you don't plan on using Fanaleds or want to try it anyway, then go ahead.

**update:** The bluetooth version is now deprecated as I was unable to find any reliable bluetooth module that suit my needs.  
You can still use it if you want, but no further development will be done on this side.

### Shopping List
#### USB version
- Fanatec CSW rim (obviously)
- [Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) : **~12$**

#### Bluetooth upgrade
- [Bluegiga WT12 module](http://www.jetney.com/wt12) : **~25$**
- [Adafruit PowerBoost 500 Charger](https://www.adafruit.com/products/1944) : **~15$**
- [LiPo Battery (>=1000mA)](https://www.adafruit.com/categories/138) : **~10$**

Total price for full BT conversion : **~60$**

If you don't want to salvage the existing connector in your rim, you'll need a **JST 2.0mm PH** Female Connector (12-Pin for the Universal Hub, 8-Pin for all other rims).

### Pinout & schematics
#### Fanatec Plug
![Fanatec Round Plug](http://i.imgur.com/yLSG0Jsm.jpg)
>>>>>>> v1.2-rc1

1. MISO
2. MOSI
3. GND
4. 5v
5. GND
6. SCK
7. 3v3
8. CS
<<<<<<< HEAD
9. USB charge 5v
10. -
11. DataPort1
12. USB charge GND
13. DataPort2

 These pin are only used on the Universal Hub and don't need to be connected for this conversion

#### Matching pin for Formula  BMW  Porsche ####
![Porsche plug pinout](httpi.imgur.comWazqNZlm.jpg)

#### Matching pin for Universal Hub  CSL P1 ####
![UNI Hub pinout](httpi.imgur.compC5L8Lum.jpg)

## Compatible Wheels
All CSW  are working with this conversion. That includes

- BMW M3 GT2
- Formula BlackCarbon
- Porsche 918 RSR
- McLaren GT3
- Universal Hub (both version) (not tested)
=======
9. USB charge 5v*
10. -
11. DataPort1*
12. USB charge GND*
13. DataPort2*

** These pin are only used on the Universal Hub and don't need to be connected for this conversion*

#### Matching pin for Formula / BMW / Porsche ####
![Porsche plug pinout](http://i.imgur.com/WazqNZlm.jpg)

#### Matching pin for Universal Hub / CSL P1 ####
![UNI Hub pinout](http://i.imgur.com/pC5L8Lum.jpg)

#### Wiring Schematics
![Wiring schematics](https://phunk.me/Y86946)
This is the same schematics for Bluetooth and USB version.  
Just forget about the Adafruit Power Boost (upper left) and the Bluegiga WT12 (bottom right) for the USB version.  
There is also room for 8 extra buttons on pin 2 to 9 (common ground) if you need more inputs.

#### Bluetooth WT12 specifics
Before flashing your Teensy, you'll need to configure the WT12 module by following this [howto](iwrap.md).

## Compatible Wheels
All CSW / CSL rims are working with this conversion. That includes:

- BMW M3 GT2
- Formula Black/Carbon
- Porsche 918 RSR
- Universal Hub (**both version**)
- CSL P1 (both version)
>>>>>>> v1.2-rc1

## Special note for the Universal Hub and Extra buttons ##
The Universal HUB brings you no more than 38 buttons (46 with the extra). The Windows Control Panel will only show you 32, but don't worry, every modern DirectX games can go up to 128.

<<<<<<< HEAD
If you need to test all of them, I suggest you to use [JoystickTest](httpwww.planetpointy.co.ukjoystick-test-application) as it can see them all, or [Node Blue](httpwww.nodeblue.orggui)

## SoftwareDriver Required
=======
If you need to test all of them, I suggest you to use [JoystickTest](http://www.planetpointy.co.uk/joystick-test-application/) as it can see them all.

## Software/Driver Required
>>>>>>> v1.2-rc1
This is detected has a HID device on Windows, so no specific drivers are required.  
It's is fully compatible with Fanaleds, which is required to get all feedback indicator working (LEDs, display and motors, if any).  
Alternatively, you can use SLIMax Manager Pro, which is free if used with any Fanatec wheel.

## Supported wheel features
Well... Everything.

<<<<<<< HEAD
## Contribution
There is a lot of room for improvement, so if you want to contribute, you're welcome to [fork](httpshelp.github.comarticlesfork-a-repo) this project, and send me a [pull request](httpshelp.github.comarticlesusing-pull-requests).

## Donation to Darknao 
If you like this project and want to support it, or just want to pay Darknao a beer or two ;)  
a href=httpswww.paypal.comcgi-binwebscrcmd=_s-xclick&hosted_button_id=89TWYN8U3P8QLimg src=httpswww.paypalobjects.comen_USibtnbtn_donate_SM.gif alt=[paypal] a
=======
## Precompiled firmware
You'll need the [Teensy Loader](https://www.pjrc.com/teensy/loader.html) to flash these firmwares.

**Teensy 3.1 & 3.2** : [`USB`](https://raw.githubusercontent.com/darknao/btClubSportWheel/master/firmware/csw.teensy31_USB.hex) | [`Bluetooth`](https://raw.githubusercontent.com/darknao/btClubSportWheel/master/firmware/csw.teensy31_BT.hex)  
**Teensy LC** : [`USB`](https://raw.githubusercontent.com/darknao/btClubSportWheel/master/firmware/csw.teensyLC_USB.hex) | [`Bluetooth`](https://raw.githubusercontent.com/darknao/btClubSportWheel/master/firmware/csw.teensyLC_BT.hex)

## Firmware Building Instruction
This code is based on Teensyduino framework and all required libraries are included in this repo.  
Modify the **TEENSY** and **TYPE** variables in `Makefile` to reflect your needs.  
Use `make` to build the HEX file, then use the Teensy loader to flash the firmware.

## Contribution
There is a lot of room for improvement, so if you want to contribute, you're welcome to [fork](https://help.github.com/articles/fork-a-repo/) this project, and send me a [pull request](https://help.github.com/articles/using-pull-requests/).

## Donation
If you like this project and want to support it, or just want to pay me a beer or two ;)  
<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=89TWYN8U3P8QL"><img src="https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif" alt="[paypal]" /></a>
>>>>>>> v1.2-rc1
