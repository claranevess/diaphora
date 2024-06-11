#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;
Servo myservo2;
int pos = 0;
const int btnVerdePin = 2;
const int btnVermelhoPin = 3;

const int rgb[] = { 4, 5, 6, 7, 8, 9 };

bool btnVerdeState;
bool btnVermelhoState;

int estado = 0;  // 0 = parado, 1 = rodando, 2 = pausado, 3 = reinicia
bool jaRodou = false;

int numPressVerde = 0;
int numPressVermelho = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
// Endereço I2c do LCD e tamanho (16 colunas x 2 linhas)

int horas = 0;
int minutos = 0;
int segundos = 0;
int decimas = 0;
long milisegundos = 0;
int inicio = 12;
bool inicioPressed = false;  // Variável para controlar o estado do botão inicio

void setup() {
  Serial.begin(9600);
  pinMode(btnVerdePin, INPUT_PULLUP);
  pinMode(btnVermelhoPin, INPUT_PULLUP);
  pinMode(inicio, INPUT_PULLUP);
  pinMode(pausa, INPUT_PULLUP);

  for (int i = 0; i < 6; i++) {
    pinMode(rgb[i], OUTPUT);
  }
  myservo.attach(11);
  myservo.write(180);
  myservo2.attach(10);
  myservo2.write(0);

  lcd.init();       // Inicializa o LCD
  lcd.backlight();  // Liga a luz de fundo do LCD

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("00:00:00:0");
}

void loop() {
  // Botão de início
  if (digitalRead(inicio) == LOW && !inicioPressed) {
    inicioPressed = true;  // Marca o botão como pressionado

    if (estado == 0) {
      estado = 1;
    } else if (estado == 1) {
      estado = 2;
    } else if (estado == 2) {
      estado = 3;
    } else if (estado == 3) {
      estado = 1;
    }
    delay(20);

  } else if (digitalRead(inicio) == HIGH && inicioPressed) {
    inicioPressed = false;  // Reseta a marcação do botão
    delay(20);
  }

  if (estado == 0 && jaRodou == false) {  // parado
    jaRodou = true;
    horas = 0;
    minutos = 0;
    segundos = 0;
    decimas = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("00:00:00:0");
    Serial.println("reinicia");


  } else if (estado == 1) {  // rodando
    jaRodou = false;
    milisegundos = millis();
    if (milisegundos % 100 == 0) {
      decimas++;
      if (decimas == 10) {
        decimas = 0;
        segundos++;
      }
      if (segundos == 60) {
        segundos = 0;
        minutos++;
      }
      if (minutos == 60) {
        minutos = 0;
        horas++;
      }

      lcd.setCursor(0, 0);
      if (horas < 10) {
        lcd.print("0");
      }
      lcd.print(horas);
      lcd.print(":");
      if (minutos < 10) {
        lcd.print("0");
      }
      lcd.print(minutos);
      lcd.print(":");
      if (segundos < 10) {
        lcd.print("0");
      }
      lcd.print(segundos);
      lcd.print(":");
      if (decimas < 10) {
        lcd.print("0");
      }
      lcd.print(decimas);
    }
  } else if (estado == 2) {  // pausa

  } else if (estado == 3) { //reinicia
    estado = 0;
  }


  btnVerdeState = digitalRead(btnVerdePin);
  btnVermelhoState = digitalRead(btnVermelhoPin);


  // Verifica se o botão verde foi pressionado
  if (btnVerdeState == LOW) {
    delay(200);  // Debounce
    while (digitalRead(btnVerdePin) == LOW)
      ;
    if (numPressVermelho == 1 && numPressVerde != 1) {
      digitalWrite(rgb[2], HIGH);
      numPressVerde++;
    } else if (numPressVermelho == 2 || (numPressVerde == 1 && numPressVermelho == 1)) {
      digitalWrite(rgb[4], HIGH);
      numPressVerde++;
    } else {
      numPressVerde++;
      if (numPressVerde == 1) {
        digitalWrite(rgb[0], HIGH);
      } else if (numPressVerde == 2) {
        digitalWrite(rgb[2], HIGH);
      } else if (numPressVerde == 3) {
        digitalWrite(rgb[4], HIGH);
      }
    }
  }

  // Verifica se o botão vermelho foi pressionado
  if (btnVermelhoState == LOW) {
    delay(200);  // Debounce
    while (digitalRead(btnVermelhoPin) == LOW)
      ;
    if (numPressVerde == 1 && numPressVermelho != 1) {
      digitalWrite(rgb[3], HIGH);
      numPressVermelho++;
    } else if (numPressVerde == 2 || (numPressVermelho == 1 && numPressVerde == 1)) {
      digitalWrite(rgb[5], HIGH);
      numPressVermelho++;
    } else {
      numPressVermelho++;
      if (numPressVermelho == 1) {
        digitalWrite(rgb[1], HIGH);
      } else if (numPressVermelho == 2) {
        digitalWrite(rgb[3], HIGH);
      } else if (numPressVermelho == 3) {
        digitalWrite(rgb[5], HIGH);
      }
    }
  }

  // Verifica se três LEDs verdes estão ligados
  if (numPressVerde >= 3) {
    delay(200);
    if (pos < 10) {
      int cont = 180;
      for (pos = 0; pos <= 90; pos++) {
        myservo2.write(pos);
        myservo.write(cont);
        cont--;
      }
    }

    for (int i = 0; i < 6; i++) {
      digitalWrite(rgb[i], LOW);
    }
    numPressVerde = 0;
    // Comentário: Servo abrindo
  }

  // Condição para caso não seja apertado três botões da mesma cor seguidos
  if (((numPressVerde + numPressVermelho) == 3) && (numPressVermelho != 3) && (numPressVerde != 3)) {
    delay(300);
    for (int i = 0; i < 6; i++) {
      digitalWrite(rgb[i], LOW);
    }
    numPressVerde = 0;
    numPressVermelho = 0;
  }

  // Verifica se três LEDs vermelhos estão ligados
  if (numPressVermelho >= 3) {
    delay(200);
    if (pos >= 90) {
      int cont = 90;
      for (pos = 90; pos >= 0; pos--) {
        myservo2.write(pos);
        myservo.write(cont);
        cont++;
      }
    }

    for (int i = 0; i < 6; i++) {
      digitalWrite(rgb[i], LOW);
    }
    numPressVermelho = 0;
    // Comentário: Servo fechando
  }
}