/*
 * Use arduino port "PORTD" (analog pins) for 4 bit data lines
 * Analog pins (2, 3, 4, 5)- > DB1, DB2, DB4, DB8
 * Digital pin 8 -> DBC| "Data Bus Control" when high causes radio to read from data bus
 * Digital pin 9 -> RC | "Remote control" When high, radio is put in remote control mode
 * Digital pin 10-> DV | "Data valid" Goes from high to low when entered data is valid
 * Digital pin 11-> RT | "Remote Trigger" Put high after DBC goes low
*/ 

#define DBC_HIGH B0010000
#define RC_HIGH  B0100000
#define RT_HIGH  B10000000



//Modes enum
enum modes {AM, LSB, USB, CW, RTTY};

//VFO A/B
enum vfos {VFOA, VFOB};

/*
 * Write data to the radio
 * As specified by ICOM documentaion, data is placed on
 * bus, then DBC is pulsed for 50ms
 * finally, RT is pulsed to trigger radio side data validation (not checked)
 */
void writeData(byte data) {
    /*PORTF (analog pins) layout
     A2 A3 ? ? A4 A5 -> 110011
     */
    
    //Shift data to match PORTF layout
    byte dataOut = ((data & B0011) | (data << 2)) & (B110011);
    //Write data to bus
    PORTF = dataOut;

    delay(1);

    //Set DBC high
    PORTB |= DBC_HIGH;

    delay(50);

    //Set DBC low
    PORTB ^= DBC_HIGH;

    delay(1);

    //Remove data from bus
    PORTF = B000000;

    delay(10);

    //Set RT high
    PORTB |= RT_HIGH;
    delay(10);

    PORTB ^= RT_HIGH; 

}


/*
 * Set the2 radio mode 
 */
void writeMode(modes mode) {
    switch (mode) {
        case USB: 
            writeData(0);
            break;
        case CW:
            writeData(6);
            break;
        case AM:
            writeData(8);
            break;
        case LSB:
            //0xB
            writeData(11);
            break;
        case RTTY:
            //0xC
            writeData(12);
            break;
    }
}

/*
 * Write the VFO Data & mode
 * freq: integer of desired frequency in hz
 */
void writeVFO(unsigned long freq, modes mode,  vfos vfo) {
    //0xE represents HF band (only option on IC-720a)
   writeData(0xE);

    delay(2);

    //Write mode data
    writeMode(mode);

    //Choose vfo a or b
    switch (vfo) {
        case VFOA:
            writeData(0xA);
            break;
        case VFOB:
            writeData(0xB);
            break;
    
    }
    
    //split frequency into digits: 1Mhz, 100k, 10k, 1k, 100
    //Digit is stored in array index 0-5 in descending order
    byte digits[5];
    digits[0] =  freq / 1000000; //EX 14,087,300 -> 14
    digits[1] =  (freq % 1000000) / 100000; // 14,087,300 -> 0
    digits[2] =  (freq % 100000) / 10000; // 14,087,300 -> 8
    digits[3] =  (freq % 10000) / 1000; // 14,087,300 -> 7
    digits[4] =  (freq % 1000) / 100; // 14,087,300 -> 3
    
    //digits[0] = freq >> 6 & 0xF;
    Serial.print("\nfreq value: ");
    Serial.println(freq, DEC);
    //Write freq data
    int i = 0;
    for (i = 0; i < 5; i++) {
        Serial.print("digit index ");
        Serial.println(i, DEC);
        Serial.println(digits[i], DEC);
        writeData(digits[i]);
        delay(25);
    }
}



void setup() {
    //Setup control pins (pins 8-11)
    //lowest to highest pin number: DBC, RC, DV, RT
    DDRB |= B1111000;

    // Set analog pins to output (Data Bus)
    DDRF |= B0110011; 



    //Serial Setup
    Serial.begin(115200);
    Serial.println("Ready");
    
}


void loop() {
    Serial.println("writing freq");
    writeVFO(14087300, USB, VFOA);
    delay(1000);
}