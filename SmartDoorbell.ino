#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {10, 9, 8, 7};
byte pin_column[COLUMN_NUM] = {6, 5, 4, 3};

const String password = "1234"; 
String input_password;

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
int cursorColumn=0;

void setup()  {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(D3,INPUT_PULLUP);
  timer.setInterval(100L,notify); 
  
  int flagged=0;
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);    
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.print("Press * to");
  lcd.setCursor(0, 1);
  lcd.print("Enter Password");
  input_password.reserve(32);
}

int count=0;


void loop() {
char key = keypad.getKey();
if(count==2){
  lcd.clear();
  lcd.setCursor(0,0);
  digitalWrite(12,HIGH);
  lcd.setCursor(0,1);
  for(int i=30;i>0;i--){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Try Again After");
    lcd.setCursor(0,1);
    lcd.print(i);
    
    if(i==1){
      lcd.print(" Minute");
    }else{
      lcd.print(" Minutes");
    }
     delay(60000);
    }
              
    lcd.setCursor(0,0);
    digitalWrite(12,LOW);
    lcd.clear();
    count=0;
    lcd.print("Press * to");
    lcd.setCursor(0, 1);
    lcd.print("Enter Password"); 
     
}
else if (key ){ 
 
if(key == '*') {

            input_password = "";
          lcd.clear(); 
            lcd.print("Password: ");

} else if(key == '#') {
      
  if(password == input_password) {
    Serial.println("password is correct");
    lcd.clear();
    lcd.print("Correct Password");
    lcd.setCursor(0, 1);
    lcd.print(“Access Granted”);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
    delay(2000);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
    delay(200)   
    count=0;          
    }else {
      count++;
      Serial.println("password is incorrect, try again");
      lcd.clear();
      lcd.print("Please Try Again");
      for(int i=0;i<5;i++){
        delay(400);
        digitalWrite(13, LOW);
        delay(400);
        digitalWrite(13, HIGH);
      }    
    delay(100);
     }
     lcd.clear();
     lcd.print("Press * to");
     lcd.setCursor(0, 1);
     lcd.print("Enter Password");
     Input_password = ""; // clear input password
     cursorColumn=0;
      
}else {
     lcd.setCursor(cursorColumn, 1);
     lcd.print(key);
     delay(300);
     cursorColumn++;
     input_password += key; 
        }
   }
}
