//Definir as credenciais da plataforma Blynk Iot 2.0
#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"

#define BLYNK_PRINT Serial

#include "SettingBoard.h"

//Bibliotecas
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <IRremote.hpp>
#include <DHT.h>

//Estado de energia dos relés, devem iniciar desligados devido ao módulo !POWER_STATE_1.
bool POWER_STATE_1 = LOW;
bool POWER_STATE_2 = LOW;
bool POWER_STATE_3 = LOW;
bool POWER_STATE_4 = LOW;

bool FETCH_BLYNK_STATE = true;
char auth[] = BLYNK_AUTH_TOKEN;

DHT dht(DHT_SENSOR, DHTTYPE);
BlynkTimer timer;
int WiFi_Flag = 0;

// *** Função para controle através de botões touch, controle remoto IR e App. ***
void onOffDevices(int opc) {
  switch (opc) {
    //case 1,2,3,4 controle de iluminação, ventilador e desligar todos.
    //Iluminação 1
    case 1:
      if (POWER_STATE_1 == LOW) {
        digitalWrite(RELAY_PIN_1, LOW); POWER_STATE_1 = !POWER_STATE_1; Blynk.virtualWrite(VIRTUAL_PIN_1, POWER_STATE_1);
        Serial.println("Iluinação 1 Ligado");
      }
      else {
        digitalWrite(RELAY_PIN_1, HIGH); POWER_STATE_1 = !POWER_STATE_1; Blynk.virtualWrite(VIRTUAL_PIN_1, POWER_STATE_1);
        Serial.println("Iluminação 1 Desligado");
      }
      delay(100);
      break;

    //Iluminação 2
    case 2:
      if (POWER_STATE_2 == LOW) {
        digitalWrite(RELAY_PIN_2, LOW); POWER_STATE_2 = !POWER_STATE_2; Blynk.virtualWrite(VIRTUAL_PIN_2, POWER_STATE_2);
        Serial.println("Iluminação 2 Ligado");
      }
      else {
        digitalWrite(RELAY_PIN_2, HIGH); POWER_STATE_2 = !POWER_STATE_2; Blynk.virtualWrite(VIRTUAL_PIN_2, POWER_STATE_2);
        Serial.println("Iluminação 2 Desligado");
      }
      delay(100);
      break;

    //Ventilador
    case 3:
      if (POWER_STATE_3 == LOW) {
        digitalWrite(RELAY_PIN_3, LOW); POWER_STATE_3 = !POWER_STATE_3; Blynk.virtualWrite(VIRTUAL_PIN_3, POWER_STATE_3);
        Serial.println("Ventilador Ligado");
      }
      else {
        digitalWrite(RELAY_PIN_3, HIGH); POWER_STATE_3 = !POWER_STATE_3; Blynk.virtualWrite(VIRTUAL_PIN_3, POWER_STATE_3);
        Serial.println("Ventilador Desligado");
      }
      delay(100);
      break;

    //Tomada Extra
    case 4:
      if (POWER_STATE_4 == LOW) {
        digitalWrite(RELAY_PIN_4, LOW); POWER_STATE_4 = !POWER_STATE_4; Blynk.virtualWrite(VIRTUAL_PIN_4, POWER_STATE_4);
        Serial.println("Tomada extra Ligada");
      }
      else {
        digitalWrite(RELAY_PIN_4, HIGH); POWER_STATE_4 = !POWER_STATE_4; Blynk.virtualWrite(VIRTUAL_PIN_4, POWER_STATE_4);
        Serial.println("Tomada Extra Desligada");
      }
      delay(100);
      break;

    //Desligar Todos
    case 5:
      digitalWrite(RELAY_PIN_1, HIGH); POWER_STATE_1 = LOW; Blynk.virtualWrite(VIRTUAL_PIN_1, POWER_STATE_1); delay(100);
      digitalWrite(RELAY_PIN_2, HIGH); POWER_STATE_2 = LOW; Blynk.virtualWrite(VIRTUAL_PIN_2, POWER_STATE_2); delay(100);
      digitalWrite(RELAY_PIN_3, HIGH); POWER_STATE_3 = LOW; Blynk.virtualWrite(VIRTUAL_PIN_3, POWER_STATE_3); delay(100);
      digitalWrite(RELAY_PIN_4, HIGH); POWER_STATE_4 = LOW; Blynk.virtualWrite(VIRTUAL_PIN_4, POWER_STATE_4); delay(100);
      Serial.println("Todos os dispositivos Desligado");
      break;
    default: break;
  }
}

// *** Função para controle manual da iluminação através de botões touch ***
void manualControl() {
  int capacitanciaMaxima = 20; //valor que nos da a certeza de toque
  int mediaB1 = 0, mediaB2 = 0, mediaB3 = 0;

  //Serial.print("Valor Botão 1"); Serial.println(touchRead(BUTTON_PIN_1));
  //Serial.print("Valor Botão 2"); Serial.println(touchRead(BUTTON_PIN_2));
  //Serial.print("Valor Botão 3"); Serial.println(touchRead(BUTTON_PIN_3));

  //Faz 100 leituras de cada sensor touch e calcula a média do valor lido
  for (int i = 0; i < 100; i++) {
    mediaB1 += touchRead(BUTTON_PIN_1);
    mediaB2 += touchRead(BUTTON_PIN_2);
    mediaB3 += touchRead(BUTTON_PIN_3);
  }

  mediaB1 = mediaB1 / 100; mediaB2 = mediaB2 / 100; mediaB3 = mediaB3 / 100;

  //Iluminação 1
  if (mediaB1 < capacitanciaMaxima) {
    onOffDevices(1);
  }
  //Iluminação 2
  else if (mediaB2 < capacitanciaMaxima) {
    onOffDevices(2);
  }
  //Ventilador
  else if (mediaB3 < capacitanciaMaxima) {
    onOffDevices(3);
  }
  delay(100);
}

// ***  Função para controle através do controle remoto infravermelho. ***
void remoteControl() {
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case IR_BUTTON_1: onOffDevices(1);  break;      //Iluminação 1
      case IR_BUTTON_2: onOffDevices(2);  break;      //Iluminação 2
      case IR_BUTTON_3: onOffDevices(3);  break;      //Ventilador
      case IR_BUTTON_4: onOffDevices(4);  break;      //Tomada Extra
      case IR_BUTTON_5: onOffDevices(5);  break;      //Desligar Todos
      default: break;
    }
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
  }
}

// ***  Ações para controle através do app, controle de iluminação, ventilador e tomadas. ***
//Iluminação 1
BLYNK_WRITE(VIRTUAL_PIN_1) {
  onOffDevices(1);
}
//Iluminação 2
BLYNK_WRITE(VIRTUAL_PIN_2) {
  onOffDevices(2);
}
//Ventilador
BLYNK_WRITE(VIRTUAL_PIN_3) {
  onOffDevices(3);
}
//Tomada Extra
BLYNK_WRITE(VIRTUAL_PIN_4) {
  onOffDevices(4);
}
//Desligar Todos
BLYNK_WRITE(VIRTUAL_PIN_8) {
  onOffDevices(5);
}

// ***  Função para leitura e envio de temperatura e umidade ***
void sendSensor()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler do sensor DHT!");
    delay(100);
    return;
  }
  //Você pode enviar qualquer valor a qualquer momento.
  //Por favor, não envie mais que 10 valores por segundo.
  Blynk.virtualWrite(VIRTUAL_PIN_5, t);
  Blynk.virtualWrite(VIRTUAL_PIN_6, h);

}

// ***  Função para leitura do sensor de luminosidade LDR ***
void ldrSensor() {
  float Luminosidade;
  int Valor_Ldr = 0;
  Valor_Ldr = analogRead(LDR_SENSOR);
  Luminosidade = map(Valor_Ldr, 0, 4095, 0, 100);
  Blynk.virtualWrite(VIRTUAL_PIN_7, Luminosidade);
  Serial.print(Luminosidade); Serial.println("%");
  delay(100);
}

// ***  Chamado a cada 2 segundos pelo SimpleTimer ***
void checkBlynkStatus() {
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    WiFi_Flag = 1;
  }
  if (isconnected == true) {
    WiFi_Flag = 0;
    if (!FETCH_BLYNK_STATE) {
      Blynk.virtualWrite(VIRTUAL_PIN_1, POWER_STATE_1);
      Blynk.virtualWrite(VIRTUAL_PIN_2, POWER_STATE_2);
      Blynk.virtualWrite(VIRTUAL_PIN_3, POWER_STATE_3);
      Blynk.virtualWrite(VIRTUAL_PIN_4, POWER_STATE_4);
    }
  }
}
BLYNK_CONNECTED() {
  //Solicita o estado mais recente do servidor
  if (FETCH_BLYNK_STATE) {
    Blynk.syncVirtual(VIRTUAL_PIN_1);
    Blynk.syncVirtual(VIRTUAL_PIN_2);
    Blynk.syncVirtual(VIRTUAL_PIN_3);
    Blynk.syncVirtual(VIRTUAL_PIN_4);
  }
}

// ***  Função de configuração principal ***
void setup() {
  Serial.begin(BAUD_RATE);
  dht.begin();
  wifiConfigESP();
  Blynk.config(auth);
  timer.setInterval(2000L, checkBlynkStatus);
  timer.setInterval(1000L, sendSensor);
  IrReceiver.begin(IR_RECEIVER, ENABLE_LED_FEEDBACK);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);
  pinMode(WIFI_LED_PIN, OUTPUT);

  pinMode(LDR_SENSOR, INPUT);

  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  //Durante a partida todos os relés devem DESLIGAR
  digitalWrite(RELAY_PIN_1, !POWER_STATE_1);
  digitalWrite(RELAY_PIN_2, !POWER_STATE_2);
  digitalWrite(RELAY_PIN_3, !POWER_STATE_3);
  digitalWrite(RELAY_PIN_4, !POWER_STATE_4);
  digitalWrite(WIFI_LED_PIN, LOW);
}

// *** Função Principal do Loop ***
void loop() {
  resetNetwork();
  manualControl();
  remoteControl();
  ldrSensor();
  Blynk.run();
  timer.run();
}
