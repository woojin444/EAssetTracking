
#include <VirtualWire.h>
//Seven seg 
#define Segg 2 
#define Segf 3
#define Sega 4
#define Segb 5
#define Sege 6
#define Segd 7
#define Segc 8
#define Segp 9
//variables for later calculation
int RSS=0;
float distance=0;
double V;
int recieved_count=0;
float av_RSS=0;
unsigned long  lost_count=0;

void setup()
{
vw_set_ptt_inverted(true); // Required for DR3100
vw_set_rx_pin(12);
vw_setup(4000); // Bits per sec
pinMode(Segg, OUTPUT);
pinMode(Segf, OUTPUT);
pinMode(Sega, OUTPUT);
pinMode(Segb, OUTPUT);
pinMode(Sege, OUTPUT);
pinMode(Segd, OUTPUT);
pinMode(Segc, OUTPUT);
pinMode(Segp, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(13, OUTPUT);
pinMode(A0, INPUT);
Serial.begin(9600); 

vw_rx_start(); // Start the receiver PLL running
}
void loop()
{

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
char message;
 
if (lost_count>=480000) {
  message='B';
  sevenseg(message);  
}
else {
lost_count=lost_count+1;
}

if (recieved_count==10) {
  av_RSS=RSS/10;
//  Serial.print("Av: "); //can be uncomented for testing
//  Serial.println(av_RSS);    
  if (av_RSS<200){
  distance=-3.6*av_RSS+1355;// + 12.9;
  }
  else {
  distance=-3.6*av_RSS+1355;
  }
  V=distance/100;

  
//  Serial.print("V: "); can be uncomented for testing 
//  Serial.println(V);    
  if (V<1){
    message='0';
  }
  else if ((V>=1)&&(V<2)) {
    message='1';
  }
    else if ((V>=2)&&(V<3)) {
    message='2';
  }
    else if ((V>=3)&&(V<4)) {
    message='3';
  }
    else if ((V>=4)&&(V<5)) {
    message='4';
  }
    else if ((V>=5)&&(V<6)) {
    message='5';
  }
    else if ((V>=6)&&(V<7)) {
    message='6';
  }
  else if ((V>=7)&&(V<8)) {
    message='7';
  }
  else if ((V>=8)&&(V<9)) {
    message='8';
  }
  else if ((V>=9)&&(V<10)) {
    message='9';
  }
   else if (V>=10) {
    message='A';
  } 
  sevenseg(message);  
  recieved_count=0;  
  RSS=0;
}

else {
  
}
if (vw_get_message(buf, &buflen)) // Non-blocking
{ 
  RSS=RSS+analogRead(A0);
  recieved_count=recieved_count+1;
  lost_count=0;
  message=buf[0];
  if(message=='0'){ // no water sensor no acceleration 
  digitalWrite(11,HIGH);
  digitalWrite(10,HIGH);    
  digitalWrite(13,0);
  }
  else if(message=='1'){ // no water sensor acceleration
  digitalWrite(11,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(13,1);  
  }  
  else if(message=='2'){ // water sensor no acceleration
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(13,1);  
  }
  else if(message=='3'){ // water sensor acceleration
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(13,1);  
  }  

  }  
}


int sevenseg(char message) {    
  
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
      else if (message=='B') {
     digitalWrite(Segg,LOW); 
     digitalWrite(Segf,HIGH);
     digitalWrite(Sega,LOW);    
     digitalWrite(Segb,LOW);
     digitalWrite(Sege,HIGH);
     digitalWrite(Segd,HIGH);
     digitalWrite(Segc,LOW); 
     digitalWrite(Segp,HIGH);                              
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


