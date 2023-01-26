# Cat_Sprayer
Arduino Project to Keep Cat Away from Dog Door

# Project Title
Spray the cat if on scale in front of dog door

## Description

A weight dependant water squirting sytem

## Required hardware

* Qty 1 - Arduino Starter Kit or 1pcs UNO Controller Board, 1pcs LCD1602 Module, 
* Qty 1 - Water Pump - https://www.robotshop.com/products/dc-diaphragm-pumps-for-arduino-automatic-smart-plant-watering-kit
* Qty 2 - 50kg Human Scale Load Cell Weighing Sensor Resistance Strain Half-Bridge Sensor + HX711 A/D Amplifier
*         https://www.amazon.com/gp/product/B097T3SX6W/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
* Qty 1 - 1 Channel DC 5V Relay Module

### Dependencies

HX711_Arduino_Library-0.7.5 <br>

## Version History

* WetTheCatv1.0.ino
    * Initial Release
* v2.0 The Relay will be turned on when the cats weight has been detected
* v3.0 Added Zero on Positive Value two pounds less than low weight
* v4.0 Changed Weight Sensors added ADC
