/*
02/02/21
Controllo attuatore attraverso il battito di mani (3 battiti), con riconoscimento rumori esterni.
*/


#define LED 6
#define Sensor 7

bool stato = 0;

unsigned long long t = 0;
unsigned long long tempobattito = 150;

int a = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Sensor, INPUT);
  Serial.begin(9600);
  delay(250);
}

void loop() {
  if(digitalRead(Sensor) == 1 && a == 0){     //PRIMO BATTITO
    a = 1;
    delay(60);        //DELAY ATTESA
    t = millis();
  }
  if(a == 1){
    if((millis() - t) <= tempobattito){       //Se ci sono Rumori, Non considera valido il primo battito
      if(digitalRead(Sensor) == 1){
        a = 0;
      }
    }
    else{
      a = 2;
    }
  }

  
  if(a == 2){  
    if((millis() - t) <= tempobattito + 400){         //SECONDO BATTITO
      if(digitalRead(Sensor) == 1){
        a = 3;
        delay(60);      //DELAY ATTESA
        t = millis();
      }
    }
    else{
      a = 0;
    }
  }
  if(a == 3){
    if((millis() - t) <= tempobattito){       //Se ci sono Rumori, Non considera valido il secondo battito
      if(digitalRead(Sensor) == 1){
        a = 0;
      }
    }
    else{
      a = 4;
    }
  }

  
  if(a == 4){  
    if((millis() - t) <= tempobattito + 400){         //TERZO BATTITO
      if(digitalRead(Sensor) == 1){
        a = 5;
        delay(60);      //DELAY ATTESA
        t = millis();
      }
    }
    else{
      a = 0;
    }
  }
  if(a == 5){
    if((millis() - t) <= tempobattito){       //Se ci sono Rumori, Non considera valido il terzo battito
      if(digitalRead(Sensor) == 1){
        a = 0;
      }
    }
    else{
      cambiostato();
      a = 0;
    }
  }
}



void cambiostato(void){
  stato =! stato;
  digitalWrite(LED, stato); 
}
