#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

const char* ssid     = "VENUS";      // SSID de la red Wifi
const char* password = "05061531"; // Password de la red
float flat;
float flon;

WiFiClientSecure client;
TinyGPS gps;
SoftwareSerial ss(16,17);

void setup() {
 Serial.begin(115200);
 ss.begin(9600);
 delay(100);
}

void loop() {
 //la funcion envio se encargara de enviar los datos a la base de datos
envio();
}

void envio(){
Serial.print("Esperando conexion a wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Imprime un "." hasta conectarse
    delay(1000);
  }
  Serial.print("Conectado a ");
  Serial.println(ssid);

  
 if ((WiFi.status() == WL_CONNECTED)) {

   
    WiFiClientSecure client;  
    client.setInsecure(); //uso de conexion insegura para permitir el uso de http
    HTTPClient http;//Inicializacion del cliente http para el envio de datos a google sheets

    Serial.print("[HTTP] Iniciando ...\n");
    
   //Establecimiento de conexion a la base de datos en el puerto 443
    client.connect("https://sheet.best/api/sheets/85b1faa7-57e6-404f-80b7-7531a679eeef", 443); 

    http.begin(client, "https://sheet.best/api/sheets/85b1faa7-57e6-404f-80b7-7531a679eeef");  



    //La funcion coordenadas retorna un string con un formato que puede ser usado para solicitudes POST
     String datos_a_enviar =coordenadas();
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
     Serial.print("[HTTP] POST...\n");
     int httpCode = http.POST(datos_a_enviar);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)
    Serial.print("El codifo http es ");
        Serial.println(httpCode);
        //httpCode devolverá un numero de estado de la solicitud
    if (httpCode > 0) {
      //si es mayor que uno se ejecutará el envio de datos
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      Serial.println("Redirect location: " + http.getLocation());
      const String& payload = http.getString();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      Serial.println(">>");
    } 
    else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    //se cierra la solicitud http
    http.end();
  }
  delay(100000); 
 }

 //esta funcion usa la libreria TinyGPS para obtener los datos del NEO 6M
 void coordenadas(){
  bool newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    //SS representa el puerto serial a 9600 b que se declaró al principio del codigo
    while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)) 
        newData = true;
    }
  }
  if (newData)
  {
    //Se leen y procesan los datos para separar longitud y latitud
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    flat = TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    flon = TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
    Serial.print(flat);
    Serial.println("");
  }
  //se retorna una cadena en formato "urlencoded"  para ser usada despues
  return "Longitud=" + String(flon) + "&Latitud="+String(flat)+"&Hora="+"=AHORA()";
  }
