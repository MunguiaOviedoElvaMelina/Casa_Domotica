   #include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>      // incluye libreria especifica para MFRC522
#include <Servo.h>

#define RST_PIN  9      // constante para referenciar pin de reset
#define pinGarage 6
#define pinPuerta 5
//Para luz con movimiento
#define pir2 14
#define ledMov 15
int datosMov;

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo1;
Servo servo2;
byte LecturaUID[4]; // crea array para almacenar el UID leido

// UID de tarjeta leido en programa 1
byte Usuario1[4]= {0xCA, 0x18, 0x26, 0xB0} ;
byte Usuario2[4]= {0xDE, 0x73, 0x69, 0x4C} ;

#define pir 7
int datos;
#define pind 8

boolean aux_i=false;


void setup() {
  //Para luz con movimiento
  pinMode(ledMov, OUTPUT);
  pinMode(pir2, INPUT);
  
  pinMode(2,OUTPUT);
  //digitalWrite(2,HIGH);
  Serial.begin(9600);
  // para alarma
  pinMode(pir, INPUT);

  //para RFID
  SPI.begin();
  mfrc522.PCD_Init(); // inicializa modulo lector
  servo1.attach(4);      // asigna el pin para el Servo
  servo2.attach(3);
  Serial.println("Listo"); // Muestra texto Listo
  servo1.write(0);        // coloca el servo en la posicion cero 
  servo2.write(  0.022222222222);
}

void loop() {

alarma ();
fotorre();
luzMov();
delay(100);
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) // si no hay una tarjeta presente
    return;           // retorna al loop esperando por una tarjeta
  
  if ( ! mfrc522.PICC_ReadCardSerial()) // si no puede obtener datos de la tarjeta
    return; // retorna al loop esperando por otra tarjeta
    
  Serial.print("UID:"); // muestra texto UID:
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    if (mfrc522.uid.uidByte[i] < 0x10){ // si el byte leido es menor a 0x10
      Serial.print(" 0"); // imprime espacio en blanco y numero cero
    }
    else{           // sino
      Serial.print(" ");        // imprime un espacio en blanco
    }
      Serial.print(mfrc522.uid.uidByte[i], HEX);    // imprime el byte del UID leido en hexadecimal
      LecturaUID[i]=mfrc522.uid.uidByte[i];     // almacena en array el byte del UID leido      
  }
          
  Serial.print("\t");         // imprime un espacio de tabulacion             

  if(comparaUID(LecturaUID, Usuario1) && (aux_i == false)){      // llama a funcion comparaUID con Usuario1
      Serial.println("Abrir Puerta");
      digitalWrite(pinPuerta, HIGH);
      servo1.write(90);
      aux_i = true;
      delay(2000);
  }
  else if((comparaUID(LecturaUID, Usuario2)) && (aux_i == false)){ // llama a funcion comparaUID con Usuario2
      Serial.println("Abrir Garage");
      digitalWrite(pinGarage, HIGH);
      servo2.write(90);
      aux_i= true;
      delay(2000);
  } else if(comparaUID(LecturaUID, Usuario2) && (aux_i == true)){
      servo2.write(0);
      aux_i=false;
  } else if(comparaUID(LecturaUID, Usuario1) && (aux_i == true)){
    servo1.write(0);
    aux_i=false;
  }
  else  // si retorna falso
      Serial.println("No te conozco puto, ve por donde veniste");      // muestra texto equivalente a acceso denegado   
     
                  
  mfrc522.PICC_HaltA(); // detiene comunicacion con tarjeta                
}

boolean comparaUID(byte lectura[],byte usuario[]) // funcion comparaUID
{
  for (byte i=0; i < mfrc522.uid.size; i++){    // bucle recorre de a un byte por vez el UID
  if(lectura[i] != usuario[i])                  // si byte de UID leido es distinto a usuario
    return(false);                              // retorna falso
  }
  return(true);                                 // si los 4 bytes coinciden retorna verdadero
}


void alarma(){
  
  datos = digitalRead(pir);
  if (datos == HIGH)
    tone(pind, 10000,2000);
  }

  void fotorre(){
    Serial.println(analogRead(19));
    if(analogRead(19) > 450)
      digitalWrite(2, HIGH);
    else
      digitalWrite(2,LOW);
  }

void luzMov(){
  datosMov = digitalRead(pir2);
  if(datosMov == HIGH)
    digitalWrite(ledMov,HIGH);
  else
    digitalWrite(ledMov, LOW);
}
