
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(40,41,42,43,44,45);
LiquidCrystal lcd2(36,37,42,43,44,45);
LiquidCrystal lcd3(38,39,42,43,44,45);
#define FlamePin A0
#define buzzer 22

int KIRMIZI=23;
int YESIL=24;
int SARI=25;
int SICAKLIK=A1;
int PIR7=2;
float temp;
float sicaklik=0.0;

 const byte SATIR=4;
 const byte SUTUN=3; 
char key[SATIR][SUTUN]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'} };
   byte SATIRLAR[SATIR]={14,15,16,17};
   byte SUTUNLAR[SUTUN]={18,19,20};
    Keypad keypad= Keypad(makeKeymap(key),SATIRLAR,SUTUNLAR,SATIR,SUTUN);
   char*password="0000";
   int konum=0;
    
void setup() {
   pinMode(FlamePin, INPUT_PULLUP);
   pinMode(SICAKLIK, INPUT_PULLUP);
   pinMode(PIR7, INPUT_PULLUP);
   pinMode(KIRMIZI, OUTPUT);
   pinMode(YESIL,OUTPUT);
   pinMode(SARI,OUTPUT);
   pinMode(buzzer, OUTPUT);


    lcd.begin(16, 2);
    lcd2.begin(16,2);
    lcd3.begin(16,2);
    lcd3.setCursor(0, 0);
    lcd3.print("BEGUM-ALIOSMAN");
    lcd3.setCursor(4, 1);
    lcd3.print("AKILLI EV");
    delay(1000);
    lcd3.clear();
    delay(100);

    
}

void loop() {



int Flame = digitalRead(FlamePin);
int Pir = digitalRead(PIR7);
temp=analogRead(SICAKLIK);
float mv=(temp/1024.0)*5000;
 sicaklik=mv/10;


if(Flame==HIGH)
{
  digitalWrite(buzzer, HIGH);
  lcd3.setCursor(5, 0);
  lcd3.print("YANDI");
  lcd3.setCursor(3, 1);
  lcd3.print("BURALAR");
  lcd.setCursor(0, 0);
  lcd.print("YUKSEK SICAKLIK!!");
  lcd.setCursor(3, 1);
  lcd.print("DIKKAT!!");
  delay(100);
  lcd3.clear();
  delay(100);
  
}
else
{
 digitalWrite(buzzer, LOW); 
}
 if(Pir==HIGH){
digitalWrite(buzzer, HIGH);
digitalWrite(SARI, HIGH);
lcd3.setCursor(5, 0);
lcd3.print("HATEKET");
lcd3.setCursor(3, 1);
lcd3.print("ALGILANDI");
 delay(100);
lcd3.clear();
  delay(100);
}
else{
   digitalWrite(buzzer, LOW); 
   digitalWrite(SARI, LOW);   
  }

  if(sicaklik >30){

lcd.setCursor(0, 0);
lcd.print("SICAKLIK YUKSEK ");
lcd.setCursor(3, 1);
lcd.print(sicaklik);
 lcd.print("     ");
    }
   else if (sicaklik<20){

lcd.setCursor(0, 0);
lcd.print("SICAKLIK AZALDI ");
lcd.setCursor(3, 1);
lcd.print(sicaklik);
lcd.print("     ");
   
    }
  else if (sicaklik>=20 && sicaklik<=30){

lcd.setCursor(0, 0);
lcd.print("SICAKLIK NORMAL ");
lcd.setCursor(3, 1);
lcd.print(sicaklik);
 lcd.print("     "); 
    }
    
if(konum==0){
gosterge();
  }

  char code=keypad.getKey();
  int i;
  if(code!=NO_KEY){
    
   lcd2.clear(); 
   lcd2.setCursor(0, 0);
   lcd2.print("SIFRE: ");
   lcd2.setCursor(7, 1);
   lcd2.print(" ");
   lcd2.setCursor(7, 1);

for(i=0;i<=konum;i++){
  lcd2.print("#");
  }
  if (code==password[konum]){
    ++konum;
    if (konum==4){
    girisdogru();
     konum=0; 
      
    }
    }
    
  else {
  girisyanlis();
    konum=0;
    }
    
    }
}

void girisdogru()
{
 
  digitalWrite(YESIL, HIGH);
  digitalWrite(KIRMIZI, LOW);
  
  lcd2.setCursor(0,0);
  lcd2.println(" ");
  lcd2.setCursor(1,0);
  lcd2.print("Giris Basarili!");
  lcd2.setCursor(4,1); 
  lcd2.println("Hosgeldiniz :)  ");
  delay(100);
  lcd2.clear();
  digitalWrite(YESIL, LOW);
  gosterge();
}

void  girisyanlis()
{
  delay(100);
lcd2.clear();
lcd2.setCursor(1,0);
lcd2.print("SIFRE HATALI");
digitalWrite(KIRMIZI,HIGH);
lcd2.setCursor(15,1);
lcd2.println(" ");
lcd2.setCursor(0,1);
lcd2.println("Tekrar Deneyin");
 
lcd2.setCursor(13,1);
lcd2.println(" ");
delay(100);
lcd2.clear();
digitalWrite(KIRMIZI,LOW);
gosterge();

}
void gosterge()
{
lcd2.setCursor(0,0);
lcd2.println("SIFREYI");
lcd2.setCursor(5 ,1);
lcd2.println("GIRINIZ");
}
