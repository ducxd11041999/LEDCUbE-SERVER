#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <ArduinoJson.h> 
#include <SerialCommand.h>  
//include thư viện để kiểm tra free RAM trên con esp8266
extern "C" {
  #include "user_interface.h"
}
 
 
const byte RX = RX;
const byte TX = TX;
 
//SoftwareSerial mySerial = SoftwareSerial(RX, TX, false, 256); 
 
SocketIOClient client;
const char* ssid = "UIT_Guest";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "1denmuoi1";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.
 
char host[] = "192.168.0.103";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 3000;                  //Cổng dịch vụ socket server do chúng ta tạo!
 
//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// mà chúng ta cần quan tâm đó là
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;
 
 
void setup()
{
    //Bật baudrate ở mức 57600 để giao tiếp với máy tính qua Serial
    Serial.begin(9600);
    //mySerial.begin(9600); //Bật software serial để giao tiếp với Arduino, nhớ để baudrate trùng với software serial trên mạch arduino
    delay(10);
 
    //Việc đầu tiên cần làm là kết nối vào mạng Wifi
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);
 
    //Kết nối vào mạng Wifi
    WiFi.begin(ssid, password);
 
    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
        delay(500);
        Serial.print('.');
    }
 
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());

    client.connect(host, port);
    if (!client.connect(host, port)) {
        Serial.println(F("Ket noi den socket server that bai!"));
        return;
    }
    else{
      Serial.print("ĐÃ KẾT NỐI VỚI SERVER!!!");
      }
      

}
void loop()
{
  //Khi bắt được bất kỳ sự kiện nào thì chúng ta có hai tham số:
    //  +RID: Tên sự kiện
    //  +RFull: Danh sách tham số được nén thành chuỗi JSON!
    if (client.monitor()) {
        //in ra serial cho Arduino
      StaticJsonDocument<200> doc;
      DeserializationError err = deserializeJson(doc, Rfull);
      int dataMode = (int)doc["AR"];
      if(!err)
       {
          Serial.write(dataMode+48);
          Rfull = {""};
       }
     //   Serial.print(dataMode);
        
    } 
    //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }
}
