/*
 * Use arduino port "PORTD" (analog pins) for 4 bit data lines
 * Analog pins- > DB1, DB2, DB4, DB8
 * Digital pin 2 -> DBC| "Data Bus Control" when high causes radio to read from data bus
 * Digital pin 3 -> RC | "Remote control" When high, radio is put in remote control mode
 * Digital pin 4 -> DV | "Data valid" Goes from high to low when entered data is valid
 * Digital pin 5 -> RT | "Remote Trigger" Put high after DBC goes low
*/

//Modes enum
enum modes {AM, LSB, USB, CW, RTTY};


// Function to convert binary to decimal
char binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
 
    return dec_value;
}

/*
 * Write data to the radio
 */
void writeData(unsigned char data) {
    //Write data to bus
    PORTC = data;

    //Set DBC high
    PORTB = B1000;

    delay(50);

    PORTB = B0000;

    PORTC = B0000;

}


/*
 * Set the radio mode 
 */
void writeMode(modes mode) {
    switch(mode) {
        case USB: 
            writeData(0);
        case CW:
            writeData(6);
        case AM:
            writeData(8);
        case LSB:
            //0xB
            writeData(11);
        case RTTY:
            //0xC
            writeData(12);
    }
}


void setup() {
    //Setup control pins (pins 8-12)
    //lowest to highest pin number: DBC, RC, DV, RT
    DDRB = B001011

    // Set analog pins to output (Data Bus)
    DDRC = B1111111; 
    
}


void loop() {

}