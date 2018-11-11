# Node Blue Fanatec Module
ClubSportWheel USBRadio Controller

This [Node Blue](httpwww.nodeblue.orggui) module can convert any Fanatec CSW Steering Wheel to a standalone USB or Radio version, so you can use it with any other wheel base.
I recommend to use ElectroSeed [TBB_02 board](httpswww.electroseed.frshopproduct_info.phpproducts_id=139) for USB or Radio version, as it's plug and play (you'll only need to connect the jst cable to the rim).

## Supported Hardware
This firmware has been developed and tested on a Teensy 3.2 and Teensy LC but should work with any other compatible hardware.  
The only requirement so far, is at least 1 SPI connectivity available.

The Teensy-LC is a good choice for this project as it has a small size & price.

### Shopping List
#### USB version
[TBB_02 board](httpswww.electroseed.frshopproduct_info.phpproducts_id=139) 38.10€ inc. VAT (Including Teensy LC)

#### Radio upgrade
- [TBB_02 board](httpswww.electroseed.frshopproduct_info.phpproducts_id=139) from 43.70€ inc. VAT (Including Teensy LC)
- [LeoDongle](httpswww.electroseed.frshopproduct_info.phpproducts_id=58) 20.10€ inc. VAT

##### Powering Radio Module with an Induction Kit
- [Induction kit](httpswww.electroseed.frshopproduct_info.phpproducts_id=166) 32.30€ inc. VAT
##### Powering Radio Module with a battery
- [Adafruit PowerBoost 500 Charger](httpswww.adafruit.comproducts1944)  ~15$
- [LiPo Battery (=1000mA)](httpswww.adafruit.comcategories138)  ~10$

### Pinout & schematics
#### Fanatec Plug
![Fanatec Round Plug](http://www.electroseed.fr/docs/TBB_02/fanatec_plug.jpg)

1. MISO
2. MOSI
3. GND
4. 5v
5. GND
6. SCK
7. 3v3
8. CS
9. USB charge 5v
10. -
11. DataPort1
12. USB charge GND
13. DataPort2

 These pin are only used on the Universal Hub and don't need to be connected for this conversion

#### Matching pin for Formula  BMW  Porsche ####
![Porsche plug pinout](http://www.electroseed.fr/docs/TBB_02/jst_8_pins.jpg)

#### Matching pin for Universal Hub  McLaren GT3 ####
![UNI Hub pinout](http://www.electroseed.fr/docs/TBB_02/jst_13_pins.jpg)

## Compatible Wheels
All CSW  are working with this conversion. That includes

- BMW M3 GT2
- Formula BlackCarbon
- Porsche 918 RSR
- McLaren GT3
- Universal Hub (both version) (not tested)

## Special note for the Universal Hub and Extra buttons ##
The Universal HUB brings you no more than 38 buttons (46 with the extra). The Windows Control Panel will only show you 32, but don't worry, every modern DirectX games can go up to 128.

If you need to test all of them, I suggest you to use [JoystickTest](httpwww.planetpointy.co.ukjoystick-test-application) as it can see them all, or [Node Blue](httpwww.nodeblue.orggui)

## SoftwareDriver Required
This is detected has a HID device on Windows, so no specific drivers are required.  
It's is fully compatible with Fanaleds, which is required to get all feedback indicator working (LEDs, display and motors, if any).  
Alternatively, you can use SLIMax Manager Pro, which is free if used with any Fanatec wheel.

## Supported wheel features
Well... Everything.

## Contribution
There is a lot of room for improvement, so if you want to contribute, you're welcome to [fork](httpshelp.github.comarticlesfork-a-repo) this project, and send me a [pull request](httpshelp.github.comarticlesusing-pull-requests).

## Donation to Darknao 
If you like this project and want to support it, or just want to pay Darknao a beer or two ;)  
<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=89TWYN8U3P8QL"><img src="https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif" alt="[paypal]" /></a>