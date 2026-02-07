#include <Arduino.h>

#define RX_PIN 4
#define TX_PIN 5
#define LED_PIN 2 

const int MAX_DISTANCE = 100; 

String inputString = "";      
bool stringComplete = false;  
bool isSystemActive = true; 
unsigned long lastTimeSeen = 0;
bool isPresent = false; 
int currentDistance = 0;

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Go 'SLEEP' de tam dung, 'WAKE' de hoat dong lai");
}

void loop() 
{
  // Gửi tín hiệu cho ESP32
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    
    if (cmd == "SLEEP") {
      isSystemActive = false;
      digitalWrite(LED_PIN, LOW);
      Serial.println("He thong tam dung hoat dong");
    } 
    else if (cmd == "WAKE") {
      isSystemActive = true;
      Serial.println("He thong hoat dong lai");
    }
  }

  // Đọc cảm biến
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    if (inChar == '\n' || inChar == '\r') {
      if (inputString.length() > 0) stringComplete = true;
    } else {
      inputString += inChar;
    }
  }

  // xử lý
  if (stringComplete) {
    inputString.trim();
    // Chỉ xử lý nếu hệ thống đang hoạt động (Active) VÀ chuỗi có dữ liệu
    if (isSystemActive && inputString.length() > 0) {
      
      // Cập nhật khoảng cách
      int val = inputString.toInt();
      if (val > 0 && val < 1000) {
        currentDistance = val;
      }

      // Kiểm tra tín hiệu ON 
      if (inputString.indexOf("ON") >= 0) {
         // Kiểm tra khoảng cách
         if (currentDistance > 0 && currentDistance <= MAX_DISTANCE) {
             // Có tín hiệu ON và ở gần
             digitalWrite(LED_PIN, HIGH);
             isPresent = true;
             lastTimeSeen = millis(); 
             
             Serial.print("Phat hien nguoi gan (");
             Serial.print(currentDistance);
             Serial.println("cm) -> den bat");
         } 
         else {
             // Có tín hiệu ON nhưng ở xa
             Serial.print("Nguoi o qua xa (");
             Serial.print(currentDistance);
             Serial.println("cm) -> bo qua");
         }
      }
    }
    
    inputString = "";
    stringComplete = false;
  }
}