const int ledPadre = 9;
const int ledIzquierdo = 10;
const int ledDerecho = 11;

const int btnSecuencia1 = 2;
const int btnSecuencia2 = 3;
const int btnSecuencia3 = 4;
const int potenciometroPin = A3; // Pin analógico para el potenciómetro

bool secuenciaPendiente = false;
int secuencia = 0;

void setup() {
  pinMode(ledPadre, OUTPUT);
  pinMode(ledIzquierdo, OUTPUT);
  pinMode(ledDerecho, OUTPUT);

  pinMode(btnSecuencia1, INPUT_PULLUP);
  pinMode(btnSecuencia2, INPUT_PULLUP);
  pinMode(btnSecuencia3, INPUT_PULLUP);

  // Iniciar comunicación serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // Lee el estado de los botones y ejecuta la secuencia correspondiente
  if (digitalRead(btnSecuencia1) == LOW) {
    enviarSecuencia(100);
  }

  if (digitalRead(btnSecuencia2) == LOW) {
    enviarSecuencia(200);
  }

  if (digitalRead(btnSecuencia3) == LOW) {
    enviarSecuencia(300);
  }

  // Verifica si hay datos disponibles en el puerto serial
  while (Serial.available() > 0) {
    int numero = Serial.parseInt(); // Lee el número enviado desde Python
    if (numero != 0) { // Si se recibió un número válido
      enviarSecuencia(numero); // Ejecuta la secuencia correspondiente
    }
  }

  // Verifica si hay una secuencia pendiente por ejecutar
  if (secuenciaPendiente) {
    encenderSecuencia(secuencia);
    secuenciaPendiente = false;
  }

  // Lee el valor del potenciómetro
  float analogVal = analogRead(potenciometroPin);
  float valorPotenciometro = (5.0 * analogVal) / 1023.0;
  
  // Envia el valor del potenciómetro a través de la comunicación serial
  Serial.println(valorPotenciometro);

  // Agrega una pequeña pausa para evitar lecturas muy rápidas
  delay(500);
}

void enviarSecuencia(int valor) {
  secuenciaPendiente = true;
  secuencia = valor;
}

void encenderSecuencia(int secuencia) {
  // Enciende los LEDs en la secuencia correspondiente
  switch (secuencia) {
    case 100:
      digitalWrite(ledPadre, HIGH);
      Serial.println("10");
      delay(1000);
      digitalWrite(ledIzquierdo, HIGH);
      Serial.println("20");
      delay(1000);
      digitalWrite(ledDerecho, HIGH);
      Serial.println("30"); 
      delay(1000);
      break;
    case 200:
      digitalWrite(ledIzquierdo, HIGH);
      Serial.println("20");
      delay(1000);
      digitalWrite(ledPadre, HIGH);
      Serial.println("10");
      delay(1000);
      digitalWrite(ledDerecho, HIGH);
      Serial.println("30");
      delay(1000);
      break;
    case 300:
      digitalWrite(ledDerecho, HIGH);
      Serial.println("30");
      delay(1000);
      digitalWrite(ledIzquierdo, HIGH);
      Serial.println("20");
      delay(1000);
      digitalWrite(ledPadre, HIGH);
      Serial.println("10");
      delay(1000);
      break;
  }
  
  // Apaga todos los LEDs
  digitalWrite(ledPadre, LOW);
  digitalWrite(ledIzquierdo, LOW);
  digitalWrite(ledDerecho, LOW);

  if (digitalRead(ledPadre) == LOW && digitalRead(ledIzquierdo) == LOW && digitalRead(ledDerecho) == LOW) {
    // Si todos los LEDs están apagados, enviar 'D' al monitor serial
    Serial.println("40");
  }
}

 





