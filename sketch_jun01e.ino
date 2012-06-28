/*
 * rgb values are sent to the arduino board and as a comma seperated list of decimal codes of 0-255
 * for example rgb could look like this 213,89,46. 
 * This program accepts these codes form serial comm port and seperates rgb values using (,) comma as the seperator
 * and sends them to the leds
*/

// global variable declarations

int incomingByte = 0;   // to hold incoming serial data

// pin number to connect red green and blue leds
int red = 9;          
int green = 10; 
int blue = 11;

int brightness = 0;    //default brightness level of leds
int comma;             //to keep a track of which led to process
int pin[] = {red , green , blue};    //the list of pins used for red, green and blue

int i = 0;  
int x,l,j;
int temp[3];

void setup() {
  
         Serial.begin(9600);     // opens serial port, sets data rate to 9600 bits per second 
         pinMode(red,OUTPUT);
         pinMode(blue,OUTPUT);
         pinMode(green,OUTPUT);
 }
 
 
void loop() 
{
    //wait for transmission of output serial data to complete
      Serial.flush();    
  
    // send data only when you receive data:
      if (Serial.available() > 0) 
        {
          //confirm that data received
          Serial.println("processing");
            delay(100);
            comma = 0;          
                                
            do
              {
                // read the incoming byte:
                  incomingByte = Serial.read();
                    //the byte received would be processed as ascii code and so as to process it as integer subtract ascii code of 0 (48) from it
                      incomingByte -= '0';          //get the number as integer 
                        //As all characters have been subtracted by the ascii code of 0
                        // ,(comma) ie 44 becomes -4
                        
                          //loop to read the comma seperated incoming byte and add it to a temporary arrray
                            while(incomingByte != -4)  //while incomingByte != comma
                              {
                                if((incomingByte>=0)&&(incomingByte<=9))\
                                  {
                                    temp[i] = incomingByte;
                                    i++;                
                                   }  //end if
                                   
                                   incomingByte = Serial.read();
                                   incomingByte -= '0';
                              
                            }//end while
                            
                            j = i;
                            i = 0;
                            
                            brightness = 0;
                            
                            //only a number can be sent to a pin and not an array so temp array must be changed to one number
                              for( x = 0,l = j; x<j; x++,l--)        //convert the array to a single number
                                {
                                  brightness = brightness + temp[x]*pow(10,l-1);              
                                }//end for
                                
                              brightness++;
                              analogWrite(pin[comma],brightness);
                            
                            //use this to debug code
                            //  Serial.print("brightness  ");
                            //  Serial.print(brightness);
                            //  Serial.print(" pin  ");
                            //  Serial.println(pin[comma]);
                           
                            comma++;  
                            
                            }while (comma < 3);       
                                                                       
         }//end if
 }//end loop
 
