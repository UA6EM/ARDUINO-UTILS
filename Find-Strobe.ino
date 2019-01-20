// Пример использования Таймера 1 (шестнадцатибитный) (с) UA6EM 
// на основе заимствований на arduino.ru у DIMAX и ЕвгенийП
// процедура поиска переднего и заднего фронта сигнала
// #include "lgtx8p.h"  // Для платы WAVGAT 328p (nano v3.0)

int flag = 0;
int pin_strobe = 9;

enum Prescalers {
  PRESCALER_1 = 1,
  PRESCALER_8 = 2,
  PRESCALER_64 = 3,
  PRESCALER_256 = 4,
  PRESCALER_1024 = 5
};

void setup() {
  pinMode(13,OUTPUT);
   pinMode(1,OUTPUT);
  
  uint8_t prescaler = PRESCALER_1024;
  uint16_t topValue = 1562;
  pinMode(9, OUTPUT);
  TCCR1A = 0x40;               //  Инвертирование пина 9 по сравнению
  TCCR1B = 0x08 | prescaler;   // Установить СТС режим и делитель частоты
  OCR1A = topValue;            //  установить TOP равным topValue
}

boolean strobe_high(int pin){
 int result;
 if(digitalRead(pin)== HIGH && flag == 0){
 flag=1; result = 1;} else{ result = 0;}
 if(digitalRead(pin)==LOW){flag=0; result = 0;}
 return result;
}

boolean strobe_low(int pin){
 int result;
 if(digitalRead(pin)== LOW && flag == 0){
 flag=1; result = 1;} else{ result = 0;}
 if(digitalRead(pin)==HIGH){flag=0; result = 0;}
 return result;
}

void loop() {
  digitalWrite(13,digitalRead(9));
 if (strobe_high(pin_strobe)) digitalWrite(1,!digitalRead(1));
//if (strobe_low(pin_strobe)) digitalWrite(1,!digitalRead(1));
  
}
