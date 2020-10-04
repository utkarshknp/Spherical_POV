int datapin = 3;  int clockpin = 6;
int latchpin = 5;
byte data2 = 0;
int datapin2 = 10; 
int clockpin2 = 12;
int latchpin2 = 11;
int encoder_pin = 2;
volatile byte pulses;
long int newt=0 ,oldt=0;
long int interval;
int count = 0;  bool a[15][60]={
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}  ;             
   
   
void setup() {
  Serial.begin(9600);
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
  pinMode(datapin2, OUTPUT);
  pinMode(clockpin2, OUTPUT);  
  pinMode(latchpin2, OUTPUT);
  attachInterrupt(0, counter, FALLING);
  pulses = 0;
    for(int index = 0; index <= 7; index++)
      {
        bitWrite(data1,index,0);
        shiftOut(datapin, clockpin, MSBFIRST, data1);
        digitalWrite(latchpin, 1);
        digitalWrite(latchpin, 0);
      }
    for(int index = 0; index < 7; index++)
      {
       bitWrite(data2,index,0);
      shiftOut(datapin2, clockpin2, MSBFIRST, data2);
      digitalWrite(latchpin2, 1);
      digitalWrite(latchpin2, 0);
      }
}void counter()
{
   //Update count
   pulses++;
   oldt=newt;
   newt=micros();
   interval=(newt-oldt)/2;
   count=0;
}
void loop() {          
  pulses=pulses%60;
  attachInterrupt(0, counter, FALLING);
  for(int index = 0; index <= 7; index++)
  {
    if (micros()<(newt+interval)){
        bitWrite(data1,index,a[index][60-pulses]);
        shiftOut(datapin, clockpin, MSBFIRST, data1);
        digitalWrite(latchpin, 1);
        digitalWrite(latchpin, 0);}
//        delayMicroseconds(1);
      else{  bitWrite(data1,index,LOW);
        shiftOut(datapin, clockpin, MSBFIRST, data1);
        digitalWrite(latchpin, 1);
        digitalWrite(latchpin, 0);       
     }
   }
   for(int index = 0; index < 7; index++)
   {
      if (micros()<(newt+interval)){
         bitWrite(data2,index,a[index+8][60-pulses]);
         shiftOut(datapin2, clockpin2, MSBFIRST, data2);
         digitalWrite(latchpin2, 1);
         digitalWrite(latchpin2, 0);}
       else{  bitWrite(data2,index,LOW);
         shiftOut(datapin2, clockpin2, MSBFIRST, data2);
         digitalWrite(latchpin2, 1);
         digitalWrite(latchpin2, 0);
      }
   }
   if(micros()>=(newt+interval))
    {
      if(count==0)
      {pulses++;count++;}
      for(int index = 0; index <= 7; index++)
      {
          bitWrite(data1,index,a[index][60-pulses]);
          shiftOut(datapin, clockpin, MSBFIRST, data1);
          digitalWrite(latchpin, 1);
          digitalWrite(latchpin, 0);
          }
      for(int index = 0; index < 7; index++)
      {
          bitWrite(data2,index,a[index+8][60-pulses]);
          shiftOut(datapin2, clockpin2, MSBFIRST, data2);
          digitalWrite(latchpin2, 1);
          digitalWrite(latchpin2, 0);
       }
    }
      Serial.println(pulses);
}
