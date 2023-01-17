
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4);
#include <Wire.h>
#include "Define.h"
void count_pulse()
{
  if (digitalRead(encoderB) == LOW)
  {
    count++;
  }
  else
  {
    count--;
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(dir1, OUTPUT);
  pinMode(step1, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(up_btn, INPUT_PULLUP);
  pinMode(dwn_btn, INPUT_PULLUP);
  pinMode(ent_btn, INPUT_PULLUP);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  Serial.begin(9600);
  attachInterrupt(0,count_pulse,RISING);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Thiet ke mach");
  lcd.setCursor(0, 1);
  lcd.print("Nhom 12");
  lcd.setCursor(0, 2);
  lcd.print("De tai 3");
  lcd.setCursor(0, 3);
  lcd.print("May quan day");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(ent_btn)== LOW)
  {
    lcd_state=1; delay(200);
  }
  while(lcd_state == 1)
  {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hay Nhap So Vong ^^!");
    lcd.setCursor(0, 1);
    lcd.print(turn);
    lcd.setCursor(6, 1);
    lcd.print("vong");

    if (digitalRead(up_btn) == LOW)
    {
      if (hold_duration > 10000)
      {
        turn += 50;
      }
      else if (hold_duration > 5000)
      {
        turn += 10;
      }
      else
      {
        turn ++;
      }
      if (move_state_last != digitalRead(up_btn))
      {
        hold_start_time = millis();
      }
      hold_duration = millis() - hold_start_time;
    }
    if(digitalRead(dwn_btn) ==LOW)
    {
      if (hold_duration > 10000)
      {
        turn -= 50;
      }
      else if (hold_duration > 5000)
      {
        turn -= 10;
      }
      else
      {
        turn --;
      }
      if (move_state_last != digitalRead(dwn_btn))
      {
        hold_start_time = millis();
      }
      hold_duration = millis() - hold_start_time;
    }
    delay(1000);
    for ( i = 0; i < 20; i++)
    {
      lcd.setCursor(i, 2);
      lcd.print(".");
    }
    if (digitalRead(ent_btn) == 0)
    {
      lcd_state=2; delay(200);
    }

  }
  while (lcd_state == 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hay chon kich thuoc");
    lcd.setCursor(4, 1);
    lcd.print("day dong ^^!");
    lcd.setCursor(0, 2);
    lcd.print(wire_size_array[wire_size_col]);
    lcd.setCursor(5, 2);
    lcd.print("mm");

    if (digitalRead(up_btn)==LOW)
    {
      wire_size_col ++; delay(200);
    }
    if (digitalRead(dwn_btn)==LOW)
    {
      wire_size_col --;
    }
    delay(200);
    for (  i = 0; i < 20; i++)
    {
      lcd.setCursor(i, 3);
      lcd.print("-");
    }
    if (digitalRead(ent_btn)== 0)
    {
      lcd_state =3; delay(200);
    }
  }
  if (lcd_state == 3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Chieu dai ong day ");
    lcd.setCursor(0, 1);
    lcd.print(coil_lenght);
    lcd.setCursor(5, 1);
    lcd.print("mm");
    if (digitalRead(ent_btn) == 0)
    {
      lcd_state =4; delay(200);
    }
  }
  if (lcd_state == 4)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Winding......");
    lcd.setCursor(0, 0);
    lcd.print("SO VONG:");
    lcd.setCursor(12, 1);
    lcd.print(turn);
    lcd.setCursor(15, 1);
    lcd.print("vong");
    lcd.setCursor(0, 2);
    lcd.print("Kich thuoc:");
    lcd.setCursor(12, 2);
    lcd.print(wire_size_array[wire_size_col]);
    lcd.setCursor(15, 2);
    lcd.print("mm");
    lcd.setCursor(0, 3);
    lcd.print("Chieu dai:");
    lcd.setCursor(12, 3);
    lcd.print(coil_lenght);
    lcd.setCursor(15, 3);
    lcd.print("mm");
    if(digitalRead(limit_right) ==1 && digitalRead(limit_left)==1)
    {
      digitalWrite(dir1,LOW);
      analogWrite(step1,HIGH);
      delayMicroseconds(100);
      analogWrite(step1,LOW);
      delayMicroseconds(100);
    }
    if (digitalRead(ent_btn) == 0)
    {
      lcd_state =5; delay(200);
    }

  }
  if (lcd_state == 5)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Widing.....");
    lcd.setCursor(0, 1);
    lcd.print("process");
    lcd.setCursor(0, 2);
    lcd.print(turn_count);
    lcd.setCursor(6, 2);
    lcd.print("vong");
    for (i = 0; i < 16; i++)
    {
      lcd.setCursor(i, 3);
      lcd.print(".");

    }
    lcd.setCursor(17, 3);
    lcd.print("^^!");
    if (digitalRead(ent_btn) == 0)
    {
      lcd_state =6; delay(200);
    }

  }
  if (lcd_state == 6) // hoat dong 2 left 1 right
  {    
    if(digitalRead(limit_left) ==0)
    {
      digitalWrite(dir1,HIGH);
    }
    if(digitalRead(limit_right)==0)
    {
      digitalWrite(dir1,LOW);
    }
    if(count%11==0)
    {
      count_sv ++;
    }
    if(count_sv <turn)
    {
      for(int j=0;j<200;j++)
      {
   step1_pulse++;
      if(step1_pulse == wire_size_array[wire_size_col])
      {
        analogWrite(en1,70);
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(step1,HIGH);
        delayMicroseconds(5);
        digitalWrite(step1,LOW);
        delayMicroseconds(5);
        step1_pulse =1;
      }
      else
      {
        analogWrite(en1,70);
        digitalWrite(in1,HIGH);
       digitalWrite(in2,LOW);
      }
      
    }
    turn_count++;
      
      Serial.println(turn_count);
    }
    
    else
    {
      analogWrite(en1,0);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Widing........");
      lcd.setCursor(0,1);
      lcd.print("---Complete---");
    }
    if(digitalRead(ent_btn)==0)
    {
      lcd_state==1;delay(200);
    } 
  }
}
