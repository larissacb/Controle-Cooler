#define COOLER 6
#define SENSOR 3
#define BOTAO 2
#define LED 12
#define POT A0
int pot=0, flag=0, estado=0, sensor=0, novo_valor, flagRot=0, flag1=0, valor;
volatile unsigned long tinicial=0, tfinal=0, t=0, cont=0;
//float t=0;
const byte interruptPin=3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicializando...");
  pinMode(COOLER, OUTPUT);
  pinMode(SENSOR, INPUT);
  pinMode(BOTAO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);
  attachInterrupt(0, desligaCooler, FALLING); //botao no circuito pull up
  attachInterrupt(digitalPinToInterrupt(3), velocidade, RISING);

}

void velocidade(){
  cont++;
  if(cont==1){
    tinicial=millis();
  }
  else{
    tfinal=millis();
    t=tfinal-tinicial;
    t=60000/t;
    Serial.println(t);
    cont=0;
  }
  
}
void desligaCooler(){ //interrupcao
  //Serial.println("Desligando cooler");
  if(estado==0){
    flag=1;       // flag 1 motor desligado
    estado=1;
  }
  else{
    flag=0;       // flag 0 ligado
    estado=0;
  }
}

void loop() {
  // put your main code here, to run repeatedly

  if(flag==1){ //se a interrupcao do botao ocorre
    digitalWrite(LED, LOW);
    pot = analogRead(POT);
    novo_valor=map(pot, 0, 1023, 0, 255);
    analogWrite(COOLER, novo_valor);
  }
  else {
    digitalWrite(LED, HIGH);
    if (Serial.available() > 0) {
    // lê do buffer o dado recebido:
    valor = Serial.readString().toInt();
    novo_valor=map(valor, 0, 2000, 0, 255);
    analogWrite(COOLER, novo_valor);
  }
    
  }
  
}
