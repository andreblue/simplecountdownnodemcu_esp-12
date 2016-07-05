#include <TM1637.h>

#include <Ticker.h>
#include <ESP8266WiFi.h>

//Timers
Ticker countDown;

//Wifi Connection INFO
const char* ssid = "BELL868_EXT";
const char* password = "EEE37D49";

//Wifi Server Start
WiFiServer server(80);

//Display
tm1637 display(14, 13);

//Some Vars
bool clientConnected = false;
bool doCountdown = false;
bool countDownDone = false;
int timeOrg = 600;
int timeLeft = timeOrg;

void setup() {
  Serial.begin(115200);
  delay(10);
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  //Timer
  countDown.attach(1, doCountDown);

  display.setBrightness(4);
  display.clear();

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    clientConnected = true;
  }
  
  // Wait until the client sends some data
  if (clientConnected){
    while(!client.available()){
      delay(1);
    }
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    
    if (request.indexOf("/check") != -1) {
      client.println("Up And Running");
    }else if (request.indexOf("/toggle") != -1) {
      if (doCountdown){
        doCountdown = false;
        client.println("Paused Countdown");
        Serial.println("Paused Countdown");
      }else{
        doCountdown = true;
        client.println("Started Countdown");
        Serial.println("Started Countdown");
      }
    }else if (request.indexOf("/reset") != -1) {
        if (doCountdown){
          doCountdown = false;
        }
        timeLeft = timeOrg;
        int minutes = timeLeft/60;
        int seconds = timeLeft%60;
        String minutesStr = String(minutes);
        String secondsStr = String(seconds);
        if(minutes < 10) {
          minutesStr = "0" + minutesStr;
        }
        if(seconds < 10) {
          secondsStr = "0" + secondsStr;
        }
        
        //Serial.println(minutesStr + ":" + secondsStr);
        client.println("Reset Countdown.<br> Time: " + minutesStr + ":" + secondsStr);
        //Serial.println("Reset Countdown");
    }else if (request.indexOf("/gettime") != -1) {
        int minutes = timeLeft/60;
        int seconds = timeLeft%60;
        String minutesStr = String(minutes);
        String secondsStr = String(seconds);
        if(minutes < 10) {
          minutesStr = "0" + minutesStr;
        }
        if(seconds < 10) {
          secondsStr = "0" + secondsStr;
        }
        
        //Serial.println(minutesStr + ":" + secondsStr);
        client.println("Time: " + minutesStr + ":" + secondsStr);
    }else if (request.indexOf("/time") != -1) {

      String timeAmountStr = request;
      // then perform the replacements:
      timeAmountStr.replace("GET /time/", "");
      timeAmountStr.replace(" HTTP/1.1", "");
      int timeAmount = timeAmountStr.toInt();
      timeOrg = timeAmount;
      timeLeft = timeOrg;
      int minutes = timeLeft/60;
      int seconds = timeLeft%60;
      String minutesStr = String(minutes);
      String secondsStr = String(seconds);
      if(minutes < 10) {
        minutesStr = "0" + minutesStr;
      }
      if(seconds < 10) {
        secondsStr = "0" + secondsStr;
      }
      client.println("Set Time: <br>" + minutesStr + ":" + secondsStr);
    }
    clientConnected = false;
  }
}

void doCountDown(){
  if (doCountdown){
    timeLeft = timeLeft -1;
    if (timeLeft == 0 ){
      countDownDone = true;
      doCountdown = false;
    }
    //Serial.println(timeLeft);
  }
  int minutes = timeLeft/60;
  int seconds = timeLeft%60;
  display.writeTime(minutes, seconds, true);
  
}


void countDownExpired(){
  Serial.println("KaBoom Bitch");
}
