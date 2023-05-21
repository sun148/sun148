#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const int buttonYellow = 14; //GPIO14 is D5
const int buttonBlue = 12; //GPIO12 is D6
const int buttonGreen = 13; //GPIO2 is D4
const int buttonOrange = 2; //GPIO13 is D7
// variable for storing the pushbutton status
int buttonStateY = 0;
int buttonStateB = 0;
int buttonStateG = 0;
int buttonStateO = 0;

const int LED1 = 16; //GPIO16 is D0
const int LED2 = 5; //GPIO05 is D1
const int LED3 = 4; //GPIO04 is D2
const int LED4 = 0; //GPIO00 is D3

#define SSID "xxxx" // แก้ ชื่อ ssid ของ wifi 
#define PASSWORD "xxxxxx"//"ใส่ password wifi ตรงนี้" // แก้ รหัสผ่าน wifi
// #define LINE_TOKEN "XXXXXXXXXXXXXXXXXXXXXX"//"นำ Line TOKEN มาใส่ในเครื่องหมายคำพูด ซึ่งจะเป็นรหัสของ แต่ละ line Account"// แก้ Line Token // 


void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);   //ตั้งค่าใช้งาน serial ที่ baudrate 115200
  // initialize the pushbutton pin as an input
  pinMode(buttonYellow, INPUT);
  pinMode(buttonBlue, INPUT);  
  //pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);
  LINE.notify("เซนเซอร์ เริ่มทำงานแล้ว");
}



void loop() {
//if ((WiFiMulti.run() == WL_CONNECTED)) {

  // read the state of the pushbutton value
  buttonStateY = digitalRead(buttonYellow);
  buttonStateB = digitalRead(buttonBlue);
  buttonStateG = digitalRead(buttonGreen);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH

  Serial.println(buttonStateY);       //แสดงข้อมูลกดปุ่มสีเหลือง
  Serial.println(buttonStateB);       //แสดงข้อมูลกดปุ่มสีน้ำเงิน
  Serial.println(buttonStateG);       //แสดงข้อมูลกดปุ่มสีเขียว
  delay(100);

  if (buttonStateY == LOW) {
    // turn LED on

    show_LED_run(1000);
    Serial.println("กดปุ่มเหลืองอยู่ เลือกไฟกระพริบ");
    delay(1000);
      String myNode = "LRI-00-ABCD00X";
      String myColor = "YELLOW";
      String myButton = "start process";
      String url = "http://192.168.0.108:8088/ProjectOne/nodemcu/esp8266mysql/add.php?nodeid="+String('"')+String("LRI-00-ABCD00X")+String('"')+"&"+"color="+String('"')+String("YELLOW")+String('"')+"&"+"button="+String('"')+String("start%20process"+String('"'));
                  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ change ip address to your HOST computer ^^^^^^ and PAHT of PHP Web site 
      Serial.println(url);
      delay(1000);
      WiFiClient client;
      HTTPClient http;
      http.begin(client,url); //HTTP


      int httpCode = http.GET();
      if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      }
      } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();    
      //delay(60000);
  } 

  if (buttonStateB == LOW) {

    show_LED_run(1000);
    Serial.println("กดปุ่มน้ำเงินอยู่ เลือกไฟวิ่ง");
    node_data_record("LRI-00-ABCD000", "BLUE", "stop%20process");
    delay(1000);
  } 

  if (buttonStateG == LOW) {

    show_LED_run(1000);
    Serial.println("กดปุ่มเขียวอยู่ เลือกไฟวิ่ง");
    node_data_record("LRI-00-ABCD00A", "GREEN", "standby%20process");
    delay(1000);
    
  } else {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }

}


void node_data_record(String Node, String Color, String Button){

      String url = "http://192.168.0.108:8088/ProjectOne/nodemcu/esp8266mysql/add.php?nodeid="+String('"')+String(Node)+String('"')+"&"+"color="+String('"')+String(Color)+String('"')+"&"+"button="+String('"')+String(Button)+String('"');
                  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ change ip address to your HOST computer ^^^^^^ and PAHT of PHP Web site 
      Serial.println(url);
      delay(1000);
      WiFiClient client;
      HTTPClient http;
      http.begin(client,url); //HTTP


      int httpCode = http.GET();
      if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      }
      } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
}

void show_LED_blink(int ledon, int ledoff) {
  
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);    
      digitalWrite(LED4, LOW); 
      delay(ledon);
             
      
     // return();  
      digitalWrite(LED2, HIGH); 
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED1, HIGH);
      delay(ledoff);       
  
}

void show_LED_run(int run) {
      digitalWrite(LED4, LOW);
      delay(run);
      digitalWrite(LED3, LOW);
      delay(run);
      digitalWrite(LED2, LOW); 
      delay(run);
      digitalWrite(LED1, LOW);  
      delay(run);                      // Wait for a second
  //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
      digitalWrite(LED1, HIGH);
      delay(run);
      digitalWrite(LED2, HIGH);
      delay(run);
      digitalWrite(LED3, HIGH); 
      delay(run); 
      digitalWrite(LED4, HIGH);
      delay(run);                      // Wait for two seconds (to demonstrate the active low LED)
     // return();
}
