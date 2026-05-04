#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// ESP32 Hardware Serial setup
#define SIM800L_RX 16
#define SIM800L_TX 17
HardwareSerial sim800l(2);

#define relay 19
#define buzzer 18

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = {26, 25, 33, 32};
byte colPins[COLS] = {13, 12, 14, 27};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int otp;
String otpstring = "";

// Helper function to clear and print cleanly
void updateLCD(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void SendSMS() {
  Serial.println("Sending SMS...");
  sim800l.print("AT+CMGF=1\r");
  delay(200);
  sim800l.print("AT+CSMP=17,167,0,0\r");
  delay(500);
  sim800l.print("AT+CMGS=\"+9188305848xx\"\r");
  delay(500);
  sim800l.print("Your OTP is " + otpstring + ". Type OTP and unlock the door.");
  delay(500);
  sim800l.write(26); // Ctrl+Z
  delay(1000);
  Serial.println("Text Sent.");
}

void SendWrongOTP_SMS() {
  Serial.println("Sending Wrong OTP SMS...");
  sim800l.print("AT+CMGF=1\r");
  delay(200);
  sim800l.print("AT+CMGS=\"+9188305848xx\"\r");
  delay(500);
  sim800l.print("ALERT! Someone entered a wrong OTP for your door lock.");
  delay(500);
  sim800l.write(26); 
  delay(1000);
}

void getotp() {
  String y = "";
  updateLCD("Enter OTP:", ""); 
  
  while (y.length() < 4) {
    char customKey = customKeypad.getKey();
    if (customKey) {
      y = y + customKey;
      lcd.setCursor(y.length() - 1, 1); // Print characters side by side
      lcd.print(customKey);
    }
    yield(); // Prevent ESP32 WDT reset
  }
  
  Serial.print("Entered OTP: ");
  Serial.println(y);
  
  if (otpstring == y) {
    updateLCD("Access Granted", "Door Opening...");
    digitalWrite(relay, HIGH);
    delay(5000);
    digitalWrite(relay, LOW);
  } else {
    updateLCD("Access Failed", "Try Again !!!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      delay(300);
    }
    SendWrongOTP_SMS();
  }
  delay(2000);
  lcd.clear();
}

void setup() {
  Serial.begin(115200);
  sim800l.begin(9600, SERIAL_8N1, SIM800L_RX, SIM800L_TX); // Increased baud rate slightly for stability
  
  Wire.begin(); // Explicitly start I2C
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, LOW);
  digitalWrite(buzzer, LOW);
  
  updateLCD("System Ready", "Press D for OTP");
  
  sim800l.println("AT");
  delay(1000);
}

void loop() {
  // Static display without constant refreshing to prevent flickering/corruption
  static bool waiting = true;
  if(waiting){
    lcd.setCursor(0, 0);
    lcd.print("   OTP Based    ");
    lcd.setCursor(0, 1);
    lcd.print("   Door Lock    ");
    waiting = false;
  }

  char customKey = customKeypad.getKey();
  if (customKey == 'D') {
    otp = random(2000, 9999);
    otpstring = String(otp);
    
    updateLCD(" OTP Sent to", " Your Mobile");
    
    Serial.print("Generated OTP: ");
    Serial.println(otpstring);
    
    SendSMS();
    delay(1000);
    getotp();
    waiting = true; // Refresh home screen after process
  }
}
