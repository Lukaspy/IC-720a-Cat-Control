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

/*
 * Write data to the radio
 * As specified by ICOM documentaion, data is placed on
 * bus, then DBC is pulsed for 50ms
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

}


/*
 * Set the radio mode 
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

}