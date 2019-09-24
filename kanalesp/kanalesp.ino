#define ag_ismi "ILKER" 
#define ag_sifresi "ilkeraykut07"  

#include <IRremote.h>
IRsend gonderici;

String metin="";
void setup()
{
  Serial.begin(115200); 
               
  Serial.println("AT"); 
  pinMode(7,OUTPUT);
  
  delay(3000); 
 
  if(Serial.find("OK"))
  {         
     Serial.println("AT+CWMODE=1"); //Esp modülümüzün WiFi modunu STA şekline getiriyoruz ve wifiyi açıyoruz eğer=2 olursa wifiyi kapanır>>We bring STA the our wifi mode of Esp and open,if equal the 2,wifi is closed
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";

    Serial.println(baglantiKomutu);
     delay(5000);
 }
 
   Serial.print("AT+CIPMUX=1\r\n");//Çoklu bağlatıyı açıyoruz.>>We open multiple links.
   delay(200);
   Serial.print("AT+CIPSERVER=1,80\r\n");// Bağlantının açık olduğunu ve portunu söylüyoruz.>>We tell that connection is clear and port's value
   delay(1000);
}
void loop(){
  if(Serial.available()>0){
    if(Serial.find("+IPD,")){
      metin ="<style>.sinif1{text-align:center;font-family:sans-serif;font-size:20px;color:blue;}</style>";
      metin +="<br><div class='sinif1'><h1>KANAL DEĞİŞME ALANI</h1></div> ";
      metin +="<br><div class='sinif1'><a href=\"?pin=on\"><button   style='background-color:green;width:100 ; height:50' >KANAL +</button></a> ";
      metin += "<a href=\" ?pin=off\"><button  style='background-color:red;width:100;height:50'>KANAL -</button></a>";  
      
 
      String cipsend = "AT+CIPSEND=";
      cipsend +="0";
      cipsend +=",";
      cipsend += metin.length();
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(500);
      Serial.println(metin);
    
  String gelen ="";
 char serialdenokunan;
 while(Serial.available()>0){
 serialdenokunan = Serial.read();
 gelen +=serialdenokunan;
 
 }
 Serial.println(gelen);
 if((gelen.indexOf(":GET /?pin=on")>1)){  
  gonderici.sendNEC(0xA08F7,32);//Kanal +      
 }
  if((gelen.indexOf(":GET /?pin=off")>1)){ 
gonderici.sendNEC(0xAF007,32);//Kanal -
 }
Serial.println("AT+CIPCLOSE=0"); 
    }
  }

 }


  
 
