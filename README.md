# simplecountdownnodemcu_esp-12
For NodeMCU 0.9 or a ESP-12
#Requirements:
[This TM1637 Library](https://github.com/moeur/Arduino_ESP8266/)

NodeMCU v0.9 OR ESP8266(ESP-12)

#Setup
####Install the Library from above.
####Set up your Arduino IDE for use with the NodeMCU/ESP-12. You can look lower in the readme for info on setup.
####Grab the contents of the countdownWithControl.ino file and paste it into the editor.
####Save it somewhere and upload it to your board.

#Options
If you want to change the WebServer Port, go over to Line 14 where "WiFiServer server(80);" is and change 80 to what ever port number you want it to be on.

#Control
You have a couple requests you can do to the program to change it.
##IPADDR/check
  This is a simple status check. It can be used to test if the chip is up and running.
##IPADDR/toggle
 This will toggle the timer status. So if it is running, it will stop and vice versa.
##IPADDR/reset
 This will reset the time and stop the count down. The time will be what ever last value you set the time as.
##IPADDR/gettime
 This will return the current time left.
##IPADDR/time/<timeinseconds>
 This will set the timers time to what ever is in the place of <timeinseconds>.


#Android App
I was not too sure one how to create an app for android, thus I cheated. I used [MIT's App Inventor](http://ai2.appinventor.mit.edu/) to quickly throw together an app that would let me interact with this.

You can use the .aia file to create this on your own App Inventor Account or you can grab it from the github here. It is the APK.
It is also on the App Inventor Gallery [here](http://ai2.appinventor.mit.edu/#5793076348190720)


#Setup NodeMCU/ESP-12 For the Arduino IDE
####Click on File, then on Preferences
####Add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" to your Additional boards Manager
####Click OK
####Click Tools and hover over Board: and click on Boards Manager...
####Search esp8266 and add esp8266 by esp8266 community
