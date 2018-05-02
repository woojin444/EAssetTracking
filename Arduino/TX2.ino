#include <VirtualWire.h>

#define Segg 2
#define Segf 3
#define Sega 4
#define Segb 5
#define Sege 6
#define Segd 7
#define Segc 8
#define Segp 9

int mode=2; //set to 1 for mode 1 

int x_axis=0;
int y_axis=0;
int z_axis=0;
int prev_x=0;
int prev_y=0;
int prev_z=0;
int threshold=50;
int water_level;
float z_scale; 

char *controller; 
char message=0;
void setup() {
pinMode(Segg, OUTPUT);
pinMode(Segf, OUTPUT);
pinMode(Sega, OUTPUT);
pinMode(Segb, OUTPUT);
pinMode(Sege, OUTPUT);
pinMode(Segd, OUTPUT);
pinMode(Segc, OUTPUT);
pinMode(Segp, OUTPUT);  
pinMode (A0, INPUT);
pinMode (A1, INPUT);
pinMode (A2, INPUT); 
pinMode (A3, INPUT);
pinMode(13,OUTPUT);
vw_set_ptt_inverted(true); //
vw_set_tx_pin(12);
vw_setup(4000);// speed of data transfer Kbps
controller="0";
Serial.begin(9600); 
}

void loop(){
if (mode==1){

message=*controller;
vw_send((uint8_t *)controller, strlen(controller)); //using virtual wire library http://www.airspayce.com/mikem/arduino/VirtualWire/
vw_wait_tx(); // Wait until the whole message is gone
digitalWrite(13,1);
sevenseg(message);
delay(500); 
  if (controller=="0"){
    controller="1";
  }
  else if (controller=="1"){
    controller="2";
  }
  else if (controller=="2"){
    controller="3";
  }
  else if (controller=="3"){
    controller="4";
  }
  else if (controller=="4"){
    controller="5";
  }
  else if (controller=="5"){
    controller="6";
  }
  else if (controller=="6"){
    controller="7";
  }
  else if (controller=="7"){
    controller="8";
  }
  else if (controller=="8"){
    controller="0";
  }
}

  
else if (mode==2){
  x_axis=analogRead(A2);
  y_axis=analogRead(A1);
  z_axis=analogRead(A0);
  water_level=analogRead(A3);
  //Serial.print("x: ");
  //Serial.println(x_axis);
  //Serial.print("y: ");
  //Serial.println(y_axis);
//  Serial.print("water_level: ");
//  Serial.println(water_level);
  
  if (((abs(prev_z-z_axis))<=threshold)&&((abs(prev_x-x_axis))<=threshold)&&((abs(prev_y-y_axis))<=threshold)){
    if (water_level>300){
   controller="2" ;     
    }
    else {
  controller="0" ;
    }
  message=*controller;
  
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,1);
  
  }
  
  else if (((abs(prev_z-z_axis))>=threshold)||((abs(prev_x-x_axis))>=threshold)||((abs(prev_y-y_axis))>=threshold)){
    if (water_level>300){
   controller="3" ;     
    }
    else {
  controller="1" ;
    }
  message=*controller;
  
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,1);
  
  }
  Serial.print("message: ");
  Serial.println(message);
  prev_x=x_axis;
  prev_y=y_axis;
  prev_z=z_axis;
  
  delay(100); 
}
}

int sevenseg( char message) {    
  
  if (message=='0') {
     digitalWrite(Segg,LOW); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,HIGH);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                               
  }
    else if (message=='1') {
     digitalWrite(Segg,LOW); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,LOW);    
     digitalWrite(Segb,LOW);
     digitalWrite(Sege,HIGH);
     digitalWrite(Segd,LOW);
     digitalWrite(Segc,LOW); 
     digitalWrite(Segp,LOW);                               
  }
    else if (message=='2') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,LOW);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,HIGH);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,LOW); 
     digitalWrite(Segp,LOW);                               
  } 
    else if (message=='3') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,LOW);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,LOW);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                               
  }   
    else if (message=='4') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,LOW);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,LOW);
     digitalWrite(Segd,LOW);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                               
  }     
    else if (message=='5') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,LOW);
     digitalWrite(Sege,LOW);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                               
  } 
    else if (message=='6') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,LOW);
     digitalWrite(Sege,HIGH);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                               
  }             

      else if (message=='7') {
     digitalWrite(Segg,LOW); 
     digitalWrite(Segf,LOW);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,LOW);
     digitalWrite(Segd,LOW);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                               
  } 
      else if (message=='8') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,HIGH);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                              
  }   
      else if (message=='9') {
     digitalWrite(Segg,HIGH); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,HIGH);    
     digitalWrite(Segb,HIGH);
     digitalWrite(Sege,LOW);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,HIGH); 
     digitalWrite(Segp,LOW);                              
  }   
  else {
     digitalWrite(Segg,LOW); 
     digitalWrite(Segf,LOW);
     digitalWrite(Sega,LOW);    
     digitalWrite(Segb,LOW);
     digitalWrite(Sege,LOW);
     digitalWrite(Segd,LOW);
     digitalWrite(Segc,LOW); 
     digitalWrite(Segp,HIGH);       
  }
}

