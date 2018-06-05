//Ic-720A to ic-735 cat control

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
  addrSequence();
  delay(10);
  setVFO('b');  
}


void addrSequence() {
  //This addresses the IC-720a to initiate communication
  
  digitalWrite(DBC, HIGH);
  delay(50);
  digitalWrite(DBC, LOW);
  delay(10);
  
  digitalWrite(RT, HIGH);   //Trigger the RT pulse 
  //write 1110 to data lines
  digitalWrite(DB1, LOW);
  digitalWrite(DB2, HIGH);
  digitalWrite(DB4, HIGH);
  digitalWrite(DB8, HIGH);
  delay(2);
  
  digitalWrite(RT, LOW);
  delay(2);
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


void setMode(char mode[]) {
  //Check what mode was passed and set the IC-720a to that mode
  if (strcmp(mode, "USB") == 0) {
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
  }  
  else if (strcmp(mode, "CW") == 0) {
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
  }
  else if (strcmp(mode, "AM") == 0) {
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
  }
  else if (strcmp(mode, "LSB") == 0) {
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
  }
  else if (strcmp(mode, "RTTY") == 0) {
    //place 1100 on the data lines
    digitalWrite(DB1, LOW);
    digitalWrite(DB2, LOW);
    digitalWrite(DB4, HIGH);
    digitalWrite(DB8, HIGH);
    triggerRadio();
    digitalWrite(DB1, LOW);
    digitalWrite(DB2, LOW);
    digitalWrite(DB4, LOW);
    digitalWrite(DB8, LOW);  
  }  
}


void setVFO(char VFO){
  //Set VFO to either A or B

  switch (VFO){
    case 'a':
      //Set data lines to 1010
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, HIGH);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, HIGH);
      triggerRadio();
      digitalWrite(DB1, LOW);
      digitalWrite(DB2, LOW);
      digitalWrite(DB4, LOW);
      digitalWrite(DB8, LOW);
      break;
    case 'b':
      //Set data lines to 1011
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
  }
  
}


void loop() {

}
