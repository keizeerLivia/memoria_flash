#include <Arduino.h>
#include <Bounce2.h>
#include <Preferences.h>

#define BUTTON_PIN 0
#define tempoBotaoPressionado 5000

Bounce botao = Bounce(); //*Cria o objeto botao
Preferences preferences; //*Cria o objeto Preferences

void incrementaContador();
void reset();

int contador = 0; //*Variavel para armazenar o contador 

void setup() 
{
  botao.attach(BUTTON_PIN, INPUT_PULLUP); //*Configura o pino do botão como INPUT_PULLUP
  Serial.begin(9600); //*Inicia a comunicação serial
  preferences.begin("config", false); //* Onde config é o nome do espaço de armazenamento e o 
                                      //* false indica que o acesso nao é somente leitura

  contador = preferences.getInt("contador", 0); //*Recupera o valor armazenado na memoria

  Serial.printf("Contagem inicia em: %d \n\r", contador); //*Exibe o contador no monitor serial
}

void loop()
{
  botao.update(); //*Atualiza o estado do botão

  if (botao.rose()) //*Se o botão foi solto
  {
    
     botao.previousDuration() < tempoBotaoPressionado ? contador = 0 : contador++; 
     preferences.putInt("contador", contador); //*Armazena o valor do contador na memoria
     Serial.printf("Contagem: %d \n\r", contador); //*Exibe o contador no monitor serial
  }
}

void incrementaContador()
{
  contador++; //*Incrementa o contador
}

void reset()
{
  contador = 0; //*Zera o contador
}