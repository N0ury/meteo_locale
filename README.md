# meteo_locale
A simple weather station using esp8266

This app uses a small LIPO battery.
It sleeps 10 min, and then wakes up to retrieve temp from a DHT22.
Temp is then sent via wifi to a webserver. This one stores data in a sqlite database.
The server can the be asked by any mean to get the last temp stored.
