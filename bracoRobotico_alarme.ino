/*****************************************************************************
Programa: Braço robótico com sistema de alarme * 
Autor: Danielle Andrade * 
Descrição: Braço robótico que executa funções repetitivas, monitorado por sistema de alarme 
- comunicação MQTT com o ESP8266  * 
******************************************************************************/

//bibliotecas
#include <Ultrasonic.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//mapeamento dos servos
Servo servoGarra, servoEsquerdo, servoDireito, servoBase;
int tmp = 1000; //delay para os servos

//mapeamento do sensor de distância e do buzzer
const int trigPin = D5; 
const int echoPin = D6; 
Ultrasonic ultrasonic(trigPin, echoPin);
int distancia;
const int pinoBuzzer = D7; 

//mapeamento do pisca alerta
int led = D8;

//Wi-fi e mqtt
#define MSG_BUFFER_SIZE (50) 
char msg[MSG_BUFFER_SIZE];         
const char* ssid = "******"; //nome da minha rede wi-fi                                                          
const char* password = "*******"; // senha da minha rede wi-fi                                                             
const char* mqtt_server = "broker.mqtt-dashboard.com";                                            
WiFiClient espClient;                                                                             
PubSubClient client(espClient);                                                                   
unsigned long lastMsg = 0;                                                                        
int value = 0;                                                                                    


void setup() {
  servoGarra.attach(D1);
  servoEsquerdo.attach(D2);
  servoDireito.attach(D3);
  servoBase.attach(D4);
  Serial.begin(115200); 

  pinMode(echoPin, INPUT); //Define o pino como entrada(recebe)
  pinMode(trigPin, OUTPUT); //Define o pino como saída(envia)
  pinMode(pinoBuzzer, OUTPUT); 
  pinMode(led, OUTPUT);

}


void loop() {
  p1();
  delayMicroseconds(tmp);
  p2();
  delayMicroseconds(tmp);
  p3();
  delayMicroseconds(tmp);
  p4();
  delayMicroseconds(tmp);
  p5();
  delayMicroseconds(tmp);
  p6();
  delayMicroseconds(tmp);
  p7();
  delayMicroseconds(tmp);

  calcula_distancia();
  ativa_alarme();
  publish_MQTT();

  setup_wifi();                                                                                   
  client.setServer(mqtt_server, 1883);                                                            
  client.setCallback(callback); 

     if (!client.connected()) {                                                                      
    reconnect();                                                                                  
  }
  client.loop();     
}
//Funções auxiliares
//Define posicoes repetitivas para o braço robótico
void p1() { 
  servoGarra.write(140);
  servoEsquerdo.write(167);
  servoDireito.write(74);
  servoBase.write(97);
  
}
void p2() { 
  servoGarra.write(53);
  servoEsquerdo.write(74);
  servoDireito.write(167);
  servoBase.write(97);
  
}
void p3() {
  servoGarra.write(53);
  servoEsquerdo.write(111);
  servoDireito.write(118);
  servoBase.write(97);
  
}
void p4() {
  servoGarra.write(140);
  servoEsquerdo.write(111);
  servoDireito.write(118);
  servoBase.write(97);
 
}
void p5() {
  servoGarra.write(140);
  servoEsquerdo.write(167);
  servoDireito.write(74);
  servoBase.write(178);
  
}
void p6() {
  servoGarra.write(140);
  servoEsquerdo.write(111);
  servoDireito.write(118);
  servoBase.write(178);
  
}
void p7() {
  servoGarra.write(53);
  servoEsquerdo.write(111);
  servoDireito.write(118);
  servoBase.write(178);
  
}

void calcula_distancia(){
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
//Faz a conversão do tempo de resposta do echo em centímetros e armazena na variável distância;
distancia = ultrasonic.distanceRead(CM); 
delayMicroseconds(500); 
}

void ativa_alarme() {
  if (distancia <= 30) { //Se a distância ente o objeto e o sensor ultrasonico for menor que 30cm, o buzzer é acionado
    tone(pinoBuzzer, 1500); 

  } else { //senão, o buzzer permanece desligado
    noTone(pinoBuzzer);
    
  }

}

void setup_wifi() {                                                                               

  delayMicroseconds(10);                                                                                      
  Serial.println("");                                                                             
  Serial.print("Conectando com ");                                                                
  Serial.println(ssid);                                                                           

  WiFi.begin(ssid, password);                                                                     

  while (WiFi.status() != WL_CONNECTED) {                                                         
    delayMicroseconds(500);                                                                                   
    Serial.print(".");                                    
  }                  

  Serial.println("");                                                                             
  Serial.println("WiFi conectado");                                                               
  Serial.println("IP: ");                                                                         
  Serial.println(WiFi.localIP());                                                                 
}

void callback(char* topic, byte* payload, unsigned int length) {                                  
  Serial.print("Mensagem recebida [");                                                            
  Serial.print(topic);                                                                            
  Serial.print("] ");                                                                             
  for (int i = 0; i < length; i++) {                                                              
    Serial.print((char)payload[i]);                                                               
  }
  Serial.println("");                                                                             
  if ((char)payload[0] == 'S') {                                                                  
    digitalWrite(led, HIGH);                                                                     
    snprintf (msg, MSG_BUFFER_SIZE, "A luz de alerta está ligada");                                 
    Serial.print("Publica mensagem: ");                                                           
    Serial.println(msg);                                                                          
    client.publish("imóvel/local1", msg);                                                             
  }
  Serial.println("");                                                                             
  if ((char)payload[0] == 'N') {                                                                  
    digitalWrite(led, LOW);                                                                      
    snprintf (msg, MSG_BUFFER_SIZE, "A luz de alerta está desligada");                              
    Serial.print("Publica mensagem: ");                                                           
    Serial.println(msg);                                                                          
    client.publish("imóvel/local1", msg);                                                             
  }
  
}

void reconnect() {                                                                                
  while (!client.connected()) {                                                                   
    Serial.print("Aguardando conexão MQTT...");                                                   
    String clientId = "ESP8266Client";                                       
    clientId += String(random(0xffff), HEX);                                                      
    if (client.connect(clientId.c_str())) {                                                       
      Serial.println("conectado");                                                                
      client.subscribe("imóvel/publisher");                                                         
    } else {                                                                                      
      Serial.print("falhou, rc=");                                                                
      Serial.print(client.state());                                                               
      Serial.println("tente novamente em 5s");                                                    
      delayMicroseconds(5000);                                                                                
    }
  }
}

//Função para publicar leituras no tópico MQTT
void publish_MQTT() {
  client.publish("topicoAlarmeAtivado", String((digitalRead(pinoBuzzer))).c_str(), true);
  client.publish("topicoDistancia", String(distancia).c_str(), true);
delayMicroseconds(1000);
}
