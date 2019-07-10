# What

Minigma will be a small replica of a 3-wheel enigma. While my idea is to build
is as accurate as possible, I'm very pragmatic and not planning to become
obsessed by details.

# Model

I will try to model the M4 version for variuous reasons. A lot of info can be found here:

https://www.cryptomuseum.com/crypto/enigma/m4/index.htm

alot of info here: http://enigmamuseum.com/em.htm#introx

# Original

# Parts

## Keyboard (input)

 - Using mini keys like 'Taktschalter Push Button DIP P4'
 - combining them like here: http://blog.komar.be/how-to-make-a-keyboard-the-matrix/

## Lamps (output)

 - Could potentially make the minigma significant easier by using 16-segment
 - display is stead of the normal 26 lamps (for each letter 1) Cool: Nixie with
 - lamps: small condensator to 'fade in fade out' effect

## letter dails

 - oled display?
 - 3 16-segment displays + 6 push buttons?
 - Rotary Switch Sections Wafers NOS 1P26T 1 Pole 26 positions Lot of 3 ?

## switch board

 - could be simple switches that come before the lamps
 - would consider this optional.
 - Worst case: could be done in software

## power supply

M4 could be switched between batttery ('hell' and 'dnk', dark). off and 'sammler 4v' In this mode
it operated on external power supply of 4 v


## crypto engine

 - ESP32 / ESP 8266 with IO/extenders over i2c
 - in LUA, nodeMCU

## IO requirements

 - 26 letters input (matrix, so probably 6+6 ? )
 - 26 letter outputs (again, 6 +6 )
 - 2 * 3 button for 3 wheels up/down

 = 30 IO ports = 4x8

## general

Maybe it makes sense to make 4 diffent boards: A keyboard, a letterboard, rotary
switches, and plug board

## images:

 - https://upload.wikimedia.org/wikipedia/commons/0/04/Enigma-IMG_0493-0498.jpg
