#include <LiquidCrystal.h> // biblioteca pentru LCD
#include <SoftwareSerial.h> // biblioteca pentru Bluetooth

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // initializarea LCD
SoftwareSerial BTSerial(11, 10); // initializarea Bluetooth

int ledPin = 13; // pin-ul pentru LED
int buzzerPin = 8; // pin-ul pentru buzzer
int lockPin = A5; // pin-ul pentru releul de blocare electronică
unsigned long lastActivityTime = millis(); // ultimul timp de activitate
String password = ""; // variabila string pentru a stoca parola primita

void setup()
{
  pinMode(ledPin, OUTPUT); // setarea pin-ului LED ca ieșire
  lcd.begin(16, 2);
  pinMode(lockPin, OUTPUT); // setarea pin-ului releului ca ieșire
  digitalWrite(lockPin, LOW); // inițializarea stării de blocare electronică
  pinMode(buzzerPin, OUTPUT); // setarea pin-ului buzzer ca ieșire
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(3000);
}

void loop()
{
  if (millis() - lastActivityTime > 120000) { // 2 minute = 120000 milisecunde
    Serial.println("a");
    lcd.clear(); // ștergerea afișajului LCD
    lcd.setCursor(2,0);          
    lcd.print("Try again"); 
    lcd.setCursor(3,1);           
    lcd.print("later!");
    digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 500); // set the tone to 500 Hz
    delay(2000);
    noTone(buzzerPin); // stop the tone
    digitalWrite(buzzerPin, LOW);
    delay(15000);
  }
  if (BTSerial.available()) {
    password = BTSerial.readString(); // citirea parolei și stocarea acesteia în variabila password
    if (password == "1777") {
      digitalWrite(ledPin, HIGH);
      delay(500);
      lcd.clear();
      lcd.setCursor(2,0);          
      lcd.print("The locker"); 
      lcd.setCursor(2,1);           
      lcd.print("is opening!");
      digitalWrite(lockPin, HIGH); // deblocarea electronică 
      delay(5000); // asteptare 10 secunde dupa care se inchide locker-ul
      lcd.clear();
      lcd.setCursor(4,0);          
      lcd.print("This is"); 
      lcd.setCursor(2,1);    
      lcd.print("closing! BYE!");
      digitalWrite(ledPin, LOW);
      digitalWrite(lockPin, LOW); // blocarea electronică
      lastActivityTime = millis();
      delay(5000);
    } else {
      Serial.write("incorrect password");
      delay(500);
      lcd.clear();
      lcd.setCursor(2,0);          
      lcd.print("The password"); 
      lcd.setCursor(3,1);           
      lcd.print("is wrong!");
      digitalWrite(buzzerPin, HIGH); // activarea buzzer-ului
      tone(buzzerPin, 1000); // set the tone to 500 Hz
      delay(2000); // așteptare 2 secunde
      noTone(buzzerPin); // stop the tone
      digitalWrite(buzzerPin, LOW); // dezactivarea buzzer-ului
      lastActivityTime = millis();
    }
  }
}
