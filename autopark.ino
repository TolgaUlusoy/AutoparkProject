#include <Servo.h>           // servo motor kutuphanesi
#include <LiquidCrystal.h>   // lcd ekran kutuphanesi
#include <SPI.h>             // kart okuyucu kutuphaneleri
#include <RFID.h>    


#define SDA_DIO 42                           //kart okuyucu pin girisleri
#define RESET_DIO 44

RFID RC522(SDA_DIO, RESET_DIO) ;             //kart okuyucu tanitimi

LiquidCrystal lcd(26, 32, 13, 8, 7, 2) ;     //lcd ekran baglantilari

const int trig  = 11 ;       //servo motor pin baglantilari
const int echo  = 12 ;
const int trig2 = 14 ;
const int echo2 = 15 ;

int buzzerPin   = 38 ;       //buzzer pini

int ledPinort1  = 18 ;       //orta alandaki ledler
int ledPinort2  = 19 ;
int ledPinort3  = 20 ;
int ledPinort4  = 17 ;

int ledPinA8    = 25 ;       //kirmizi dolu slot ledleri
int ledPinA9    = 3  ;
int ledPinA10   = 24 ;
int ledPinA12   = 5  ;
int ledPinA11   = 6  ;
int ledPinA13   = 4  ;

int ledPin31    = 31 ;        //yesil bos slot ledleri
int ledPin33    = 33 ; 
int ledPin35    = 35 ; 
int ledPin37    = 37 ; 
int ledPin39    = 39 ; 
int ledPin41    = 41 ; 


int oto1 = 0 ;             //normal arac slotlarini takip icin tutulan degiskenler
int oto2 = 0 ;
int oto3 = 0 ;
int oto4 = 0 ;

int oto5 = 0 ;             //vip arac slotlarini takip icin tutulan degiskenler
int oto6 = 0 ;

int ldrValueA4  = 0;       //slotlarin dolulugunu olcen ldr sensor degeri
int ldrValueA5  = 0;
int ldrValueA8  = 0;
int ldrValueA9  = 0;
int ldrValueA10 = 0;
int ldrValueA11 = 0;
int ldrValueA12 = 0;
int ldrValueA13 = 0;

int sure    = 0;
int sure2   = 0;

int mesafe  = 0;
int mesafe2 = 0;

Servo myservo;
Servo myservo2;

void setup() {

lcd.begin(20, 4) ;                //lcd ekranin boyutu

pinMode(ledPinA8  , OUTPUT) ;     //ledlerin cikis degeri oldugunu belirttik
pinMode(ledPinA9  , OUTPUT) ;
pinMode(ledPinA10 , OUTPUT) ;
pinMode(ledPinA11 , OUTPUT) ;
pinMode(ledPinA12 , OUTPUT) ;
pinMode(ledPinA13 , OUTPUT) ;

pinMode(ledPin31 , OUTPUT) ;
pinMode(ledPin33 , OUTPUT) ;
pinMode(ledPin35 , OUTPUT) ;
pinMode(ledPin37 , OUTPUT) ;
pinMode(ledPin39 , OUTPUT) ;
pinMode(ledPin41 , OUTPUT) ;

pinMode(ledPinort1 , OUTPUT) ;
pinMode(ledPinort2 , OUTPUT) ;
pinMode(ledPinort3 , OUTPUT) ;
pinMode(ledPinort4 , OUTPUT) ;


SPI.begin();            //kart okuyucuyu baslattik
RC522.init();

myservo.attach(9);      //servo  motor pini
myservo2.attach(22);    //servo2 motor pini

pinMode(trig , OUTPUT) ;   //servo  girisi ve cikisi
pinMode(echo , INPUT)  ;
pinMode(trig2, OUTPUT) ;   //servo2 girisi ve cikisi
pinMode(echo2, INPUT)  ;

Serial.begin(9600);
}

void loop() {

  digitalWrite(ledPinort1 , HIGH) ;    //orta ledler surekli yaniyor
  digitalWrite(ledPinort2 , HIGH) ;
  digitalWrite(ledPinort3 , HIGH) ;
  digitalWrite(ledPinort4 , HIGH) ;


int ldrValueA4  = analogRead(A4)  ;    //ldr den okunan analog degeri dijitale cevirdik
int ldrValueA5  = analogRead(A5)  ;
int ldrValueA8  = analogRead(A8)  ;
int ldrValueA9  = analogRead(A9)  ;
int ldrValueA10 = analogRead(A10) ;
int ldrValueA11 = analogRead(A11) ;
int ldrValueA12 = analogRead(A12) ;
int ldrValueA13 = analogRead(A13) ;

digitalWrite(trig , HIGH)  ;          //servolarin calisma calismamalarini tanittik
delayMicroseconds(1000)    ;
digitalWrite(trig , LOW)   ;

digitalWrite(trig2 , HIGH) ;
delayMicroseconds(1000)    ;
digitalWrite(trig2 , LOW)  ;

sure   = pulseIn(echo , HIGH) ;     //sureyi degerini ultrasonik sensorden aldik
mesafe = (sure/2) / 29.1      ;     //sureyi mesafeye cevirdik

sure2 = pulseIn(echo2 , HIGH) ;     //sureyi degerini ultrasonik sensorden aldik
mesafe2 = (sure2/2) / 29.1    ;     //sureyi mesafeye cevirdik


if(oto1 == 0 || oto2 == 0 || oto3 == 0 || oto4 == 0 ){     //normal arac slotlarinin biri bossa if'e giriyoruz

if(mesafe2 < 5 || ldrValueA5 < 300 )    //giris kapisinda arac mesafesi 5cm'den azsa veya cikis kapisinda arac varsa
{
  myservo.write(90);       //kapi aciliyor
  tone(buzzerPin, 500);    //acilis melodisi
  delay(150);
  tone(buzzerPin, 350);
  delay(150);
  noTone(buzzerPin);       //melodi bitiyor
}
else
{
  myservo.write(0);        //eger mesafe 5'ten az degilse veya slot bossa kapi kapaniyor
  
}
}  else{}       //eger bos slot yoksa kapi tepki vermiyor

                //bu kisim slotlarin dolulugunu kontrol ediyor
if(ldrValueA8 < 300){                     //slot doluysa    
  digitalWrite(ledPinA8,HIGH);            //slot doluysa kirmizi ledi yakiyoruz
  digitalWrite(ledPin31,LOW);             //yine ayni sekilde slot doluysa yesil led sonuyor
  oto4 = 1;                               //slot dolu oldugu icin bu degiskenimizi 1 yapiyoruz
  }
 else{                                    //slot bossa
  digitalWrite(ledPinA8,LOW);             //slot bossa kirmizi led sonuyor
  digitalWrite(ledPin31,HIGH);            //ardindan yesil led yaniyor
  oto4 = 0;                               //slot bos oldugu zaman bu degiskenimiz 0 oluyor
  }
if(ldrValueA9 < 300){                     //sirasiyla ayni islemleri tum slotlar icin tekrarliyoruz
  digitalWrite(ledPinA9,HIGH);
  digitalWrite(ledPin39,LOW);
  oto6 = 1;
  }
 else{
  digitalWrite(ledPinA9,LOW);
  digitalWrite(ledPin39,HIGH);
  oto6 = 0;
  }
if(ldrValueA10 < 300){
  digitalWrite(ledPinA10,HIGH);
  digitalWrite(ledPin33,LOW);
  oto3 = 1;
  }
 else{
  digitalWrite(ledPinA10,LOW);
  digitalWrite(ledPin33,HIGH);
  oto3 = 0;
  }
if(ldrValueA11 < 300){
  oto2 = 1;
  digitalWrite(ledPinA11,HIGH);
  digitalWrite(ledPin37,LOW);

  }
 else{
  digitalWrite(ledPinA11,LOW);
  digitalWrite(ledPin37,HIGH);

  oto2 = 0;
  }

if(ldrValueA12 < 300){
  digitalWrite(ledPin35,LOW);
  digitalWrite(ledPinA12,HIGH);
  oto1 = 1;
  }
 else{
  digitalWrite(ledPinA12,LOW);
  digitalWrite(ledPin35,HIGH);
  oto1 = 0;
  }
if(ldrValueA13 < 300){
  digitalWrite(ledPinA13,HIGH);
  digitalWrite(ledPin41,LOW);
  oto5 = 1;
  }
 else{
  digitalWrite(ledPinA13,LOW);
  digitalWrite(ledPin41,HIGH);
  oto5 = 0;
  }                         //tum slotlarin kontrolu saglandi
  
lcd.setCursor(5,0)       ;         //lcd yazdirma baslangic koordinati degisme
lcd.print("Hosgeldiniz") ;   
lcd.setCursor(4,1)       ;    
lcd.print("1")           ;          
lcd.print("2")           ;
lcd.print("3")           ;
lcd.print("4   ")        ;
lcd.print("V1 ")         ;
lcd.print("V2")          ;
  
lcd.setCursor(4,2)  ;      //lcd ekrana slotlar doluysa 1 bossa 0 yazdirma
lcd.print(oto1)     ; 
lcd.print(oto2)     ;
lcd.print(oto3)     ;
lcd.print(oto4)     ;
lcd.print("   ")    ;
lcd.print(oto5)     ;
lcd.print("  ")     ;
lcd.print(oto6)     ;
lcd.setCursor(1,3)  ;
lcd.print("7/24 acik otopark") ;

delay(1000);    //gecikme
lcd.clear();    //lcd bu temizleme islemi sayesinde yanip sonuyor


if (RC522.isCard() || ldrValueA4 < 300)       //kart okuyucu aktif olursa veya cikis kapisi dolu olursa if'e giriyoruz
   {
    RC522.readCardSerial();                   //kartin seri numarasini okuyoruz
    myservo2.write(0);                        //kapiyi aciyoruz
    tone(buzzerPin, 500);                     //buzzerdan melodi aliyoruz
    delay(150);
    tone(buzzerPin, 350);
    delay(150);
    noTone(buzzerPin);                        //melodi bitiyor
   } 
   else if(!RC522.isCard() && mesafe > 5 && ldrValueA4 > 300) //eger kart cekilmisse, giriste ve cikista arac yoksa if'e giriyoruz
   {
    myservo2.write(90);            //burada kapiyi servo motor sayesinde kapatiyoruz
a
   }

}
