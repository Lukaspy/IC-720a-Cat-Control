//Ic-720A to ft-817 cat control

//These are the control pins on the acc port of the ic-720
int DBC = 2;
int RC = 3;
int DV = 4;
int RT = 5;
int DB1 =  6, DB2 = 7, DB4 = 8, DB8 = 9;

void setup() {
  
  pinMode(DBC, OUTPUT);
  pinMode(RC, OUTPUT);
  pinMode(DV, INPUT);
  pinMode(RT, OUTPUT);
  pinMode(DB1, OUTPUT);
  pinMode(DB2, OUTPUT);
  pinMode(DB4, OUTPUT);
  pinMode(DB8, OUTPUT);  
}

void addrSequence() {
  //This addresses the IC-720a to initiate communication
  
  digitalWrite(DBC, HIGH);
  delay(50);
  digitalWrite(DBC, LOW);
  delay(10);
  
  //Trigger the RT pulse and put b1110 on the data lines
  digitalWrite(RT, HIGH);
  //write 1110 to data lines
  digitalWrite(DB1, LOW);
  digitalWrite(DB2, HIGH);
  digitalWrite(DB4, HIGH);
  digitalWrite(DB8, HIGH);
  delay(2);
  
  digitalWrite(RT, LOW);
  digitalWrite(DB1, LOW);
  digitalWrite(DB2, LOW);
  digitalWrite(DB4, LOW);
  digitalWrite(DB8, LOW);  
  
}


void triggerRadio() {
  //Pulse DBC and RT to make the radio change according to what is on the data lines
  digitalWrite(DBC, HIGH);
  digitalWrite(RT, HIGH);
  delay(1);
  digitalWrite(RT, LOW);
  delay(1);
  digitalWrite(DBC, LOW);
  
}


void setMode(int mode) {
  //Check what mode was passed and set the IC-720a to that mode

  switch(mode) {
    case 'USB':
      //Place 0000 on the data lines
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, LOW);
      triggerRadio();
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, LOW);
      break;
    case 'CW':
      //Place 0110 on data lines
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, HIGH);
      digitalWrite(DB4, HIGH);
      digitalWrite(DB8, LOW);
      triggerRadio();
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, LOW);
      break;
    case 'AM':
      //Place 1000 on the data lines
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, HIGH);
      triggerRadio();
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, LOW);
      break;
    case 'LSB':
      //Place 1011 on the data lines
      digitalWrite(DB1, HIGH);
      digitalWrite(DB2, HIGH);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, HIGH);
      triggerRadio();
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, LOW);
      break;
    case 'RTTY':
      //place 1100 on the data lines
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, HIGH);
      digitalWrite(DB8, HIGH);
      triggerRadio();
      break;
        
  }  
}
    
void loop() {

}
