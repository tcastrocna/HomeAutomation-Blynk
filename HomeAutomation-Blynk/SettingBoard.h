
// *** Configuração personalizada da placa (Configure as Entradas e Saídas abaixo, de acordo com a placa). ***
void setupInputOutpu();

#define BAUD_RATE  115200

#define WIFI_LED_PIN                16                   // Definir pino do LED - Estado de rede.
#define RESET_BUTTON_PIN            17                   // Definir o pino do botão de resetar a rede.

#define RELAY_PIN_1                 18                   //Relé da iluminação 1
#define RELAY_PIN_2                 19                   //Relé da iluminação 2
#define RELAY_PIN_3                 23                   //Relé do ventilador
#define RELAY_PIN_4                 05                   //Tomada Extra

#define BUTTON_PIN_1                13                   //Botão da iluminação 1
#define BUTTON_PIN_2                12                   //Botão da iluminação 2
#define BUTTON_PIN_3                14                   //Botão do ventilador

#define IR_RECEIVER                 25                   //Receptor Infravermelho.
#define DHT_SENSOR                  26                   //Sensor de Temperatura e Umidade
#define LDR_SENSOR                  35                   //Sensor de luminosidade na porta analógica. 

#define IR_BUTTON_1             0xEF106E01               //Botão 1 controle IR, Relé Iluminação 1.
#define IR_BUTTON_2             0xEE116E01               //Botão 2 controle IR, Relé Iluminação 2.
#define IR_BUTTON_3             0xED126E01               //Botão 3 controle IR, Relé Ventilador.
#define IR_BUTTON_4             0xEC136E01               //Botão 4 controle IR, Relé Tomada Extra
#define IR_BUTTON_5             0xFE016E01               //Botão OFF controle IR, Desliga todos.
#define IR_BUTTON_6             0xF6096E01               //Botão STORE, reseta a rede WiFi.

//Pinos virtuais da plataforma Blynk IoT Cloud 2.0.
#define VIRTUAL_PIN_1              V1                    //Pino virtual da iluminação 1
#define VIRTUAL_PIN_2              V2                    //Pino virtual da iluminação 2
#define VIRTUAL_PIN_3              V3                    //Pino virtual do ventilador
#define VIRTUAL_PIN_4              V4                    //Pino virtual da tomada extra
#define VIRTUAL_PIN_5              V5                    //Pino virtual do sensor temperatura
#define VIRTUAL_PIN_6              V6                    //Pino virtual do sensor umidade do ar
#define VIRTUAL_PIN_7              V7                    //Pino virtual do sensor de luminosidade
#define VIRTUAL_PIN_8              V8                    //Pino virtual do botão desligar todos

//Descomente o modelo de sensor a ser usando do sensor de temperatura DHT!
#define DHTTYPE DHT11                                    // DHT 11
//#define DHTTYPE DHT21                                  // DHT 21, AM2301
//#define DHTTYPE DHT22                                  // DHT 22, AM2302, AM2321
