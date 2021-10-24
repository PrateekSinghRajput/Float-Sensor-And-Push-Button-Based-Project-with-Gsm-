#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int redLed = 7;
int greenLed = 8;
const int buzzer = 9;

int FloatSensor = 10;
int led = 13;
int buttonState = 1; //reads pushbutton status

void setup()
{
  pinMode(FloatSensor, INPUT_PULLUP); //Arduino Internal Resistor 10K
  pinMode (led, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(greenLed, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("WelCome To");
  lcd.setCursor(0, 1);
  lcd.print("JustDoElectronics");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("WATER LEVEL");

}
void loop()
{
  buttonState = digitalRead(FloatSensor);
  if (buttonState == LOW)
  {
    digitalWrite(led, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLed, HIGH);
    Serial.println( "WATER LEVEL - Empty");
    lcd.setCursor(5, 1);
    lcd.print("Empty");

  }
  else
  {
    digitalWrite(led, HIGH);
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLed, LOW);
    Serial.println( "WATER LEVEL - Full" );
    lcd.setCursor(5, 1);
    lcd.print(".Full");

    Serial.println("AT+CMGF=1");        // Set the Sim900 SMS mode to text
    delay(400);
    Serial.println();
    Serial.print("AT+CMGS=");           // Insert SMS number
    Serial.print("\"+918830584864\"");  //Recepient Owner of house
    Serial.println();
    delay(100);
    Serial.print("WATER LEVEL - Full"); // Text message
    delay(100);
    Serial.println();
    //CTRL+Z commnad to end message body and send sms
    Serial.write(26);
  }
}
