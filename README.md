# Wifi Solar

WIP!! This are just designs for now.

I wanted to build a solar powered base station that powers an access point and camera, as well as monitors temp/humidity.

## Schematic

The solar panel charges a battery, which powers an ESP8266.  This chip controls the power flow to the access point and the camera.

Having the ESP8266 as the brain allows me to turn on and off both the AP and camera depending on what I want (schedules and usage times), and the power available.

![schematic](./docs/Wifi-Solar.svg)

If you are ever using an esp8266 (node mcdu or otherwise), this article is super useful in determining which pins to use, which need to stay low/high at boot, etc.

https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

### Measuring battery voltage

To measure the battery voltage (percentage), I use a voltage divider.  However the nodemcu chip already contains a voltage divider on the built in ADC (see below diagram).  So I just need an additional resistor on the input to make sure the upper limit of the batter voltage (`Vmax`) would equate to 1v max on the ESP8266 ADC.  The equation to calculate this resister comes out to `Vmax=R/100k + 3.2`.

It's hard to find, but it seems the voltage range of the SLA battery is ~`10.8v-14v`.

The voltage divider resistor I chose was 1.14Mohm. This makes the analog reading range of `0-1024` to correspond to voltages `0v-14.6v`.  So in terms of battery voltage, 0% - 100% corresponds to analog values ~`740-959`

![nodemcu](./docs/nodemcu.png)

## PoE

I used power over ethernet to power the [Unifi AC Mesh access point][unifiap].

We can see from the [AP datasheet](https://dl.ubnt.com/datasheets/unifi/UniFi_AC_Mesh_DS.pdf), it can use 24v passive PoE.

![poe](./docs/ap-poe.png)

According to [wikipedia](https://en.wikipedia.org/wiki/Power_over_Ethernet#Passive) and their own documentation, this means putting +24v on pins 4 and 5, and ground on 7 and 8.

We get 24v by running the battery through a voltage booster (see schematic).

You can see the ADC in the below NodeMCU diagram.

## Driving the Mosftes

Because we set the ESP8266 to deep sleep, this means the GPIO pins will go offline. This means we need a separate chip to hold the GPIO pin values.

For this I use the [74HC595N](https://www.diodes.com/assets/Datasheets/74HC595.pdf) shift register.

## Mosfets

I needed to use mosfets to programetically turn on and off the power to the access point and the camera.  This was just a design choice that I wanted to be able to control both of them to set them on schedules, and turn them off if I'm not going to use them for a bit.

The mosfet I used is the [IRLZ34NPBF][mosfet-datasheet].  It has a `Vgs(th)` of 1-2 volts.  This means it can easily be turned on by 3.3v logic.

Looking at the relationship between `Vgs` and `Id` (drain to source current), we can see that at 3.3v we can deliver about 10A of current, which would be plenty for my application.

![vgs](docs/mosfet-vgs.png)

## Code

The code is in this repo.  I put the ESP8266 in deep sleep to save power over time, having it occationally wake up, check if it needs to turn something on or off, send the temp / humidity data, and go back to sleep.

### Signing binaries

To remote upload a new binary, you must used a signed binary.

First generate your keys

```sh
mkdir keys
openssl genrsa -out keys/private.key 2048
openssl rsa -in keys/private.key -outform PEM -pubout -out keys/public.key
```

Then add this to `update_creds.h`

```cpp
#define PUBLIC_KEY "Your public key here"
```

Then sign the binary

```sh
./sign.sh
```

[unifiap]: https://store.ui.com/collections/unifi-network-access-points/products/unifi-ac-mesh-ap
[mosfet-datasheet]: https://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720
[mosfet]: https://www.amazon.com/gp/product/B083TL6Q5X