#define BLYNK_TEMPLATE_ID "TMPL6iA9k-_7x"
#define BLYNK_TEMPLATE_NAME "PH sensor"
#define BLYNK_AUTH_TOKEN "kUfeFBk4Yyu4Wn9URqY1gQrWyrZxCuEX"
#define BLYNK_PRINT Serial
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

// #define USE_NODE_MCU_BOARD
#include <ESP8266WiFi.h>
// #include <Arduino.h>
#include <BlynkSimpleEsp8266.h>



 float resolution;// pH Sensor                           
 int measurings;
 float voltage;
 float pHvalue;
 float b = 0.00;
 float m = 0.167;
 int sensorPin = A0; // Turbidity Sensor
 float volt;
 float ntu;


char auth[] = "BLYNK_AUTH_TOKEN";
char ssid[] = "Tugce";
char pass[] = "QIBER123";

 void setup()                                     
  {   
  Serial.begin(9600); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);                    
  resolution = 1024.0;                       
  // "blynk.cloud",80                                           
  delay(100);                                   
 }
 void loop()                                      
 {
   Blynk.run();
 }
  BLYNK_WRITE(V0){
   measurings=0;                                  
   for (int i = 0; i < 10; i++)                   
   {
     measurings = measurings + analogRead(A0);     
     delay(10);                                  
   }
     voltage = ((5 / resolution) * (measurings/10)); 
                                                   
     pHvalue = ((7 + ((2.5 - voltage) / m)))+ b;    
    
     Serial.print("pH= ");                          
     Serial.println(pHvalue);   
     Blynk.virtualWrite(V0, pHvalue);                       
     delay(1000); 
  }   
  BLYNK_WRITE(V1){
    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
  }
    
    Serial.print(volt);
    Serial.print(" V");

    Serial.println(ntu);
    Serial.println(" NTU");
    Blynk.virtualWrite(V1, ntu);       
    delay(1000);

}
 
    float round_to_dp( float in_value, int decimal_place )
{
    float multiplier = powf( 10.0f, decimal_place );
    in_value = roundf( in_value * multiplier ) / multiplier;
    return in_value;
}

 }

// void setup() 
// {
//  Serial.begin(9600);
// }


// void loop() 
// {
//  int sensorValue = analogRead(A0);
//  float voltage = sensorValue * (5.0 / 1024.0);
//  Serial.println(voltage);
//  delay(1000);
// }