
 
void setup() {
         Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps  
 }
 
 
 
void loop() 
{
  int incomingByte = 0;   // for incoming serial data
  
  int i = 0;
   int red = 13;
   int green = 12;
   int blue = 11;
   int brightness = 0;
   int comma;
  int temp[3];
  int x,l,j;
  int pin[] = {red , green , blue};


        // send data only when you receive data:
         if (Serial.available() > 0) {
           
             //confirm that data received
           Serial.println("Processing");    
           comma = 0;
           
                     
           do{
             
             Serial.print("iteration");
             // read the incoming byte:
           incomingByte = Serial.read();
           
           incomingByte -= '0';          //get the number in int
                 
               
                                 
               //loop to read incoming byte and add it to a temp arrray
                   
               while(incomingByte != -4)  //while ib != comma
                   {
                     if((incomingByte>=0)&&(incomingByte<=9))
                     {
                       
                     temp[i] = incomingByte;
                      i++;                
                     }
                     incomingByte = Serial.read();
                     incomingByte -= '0';

                   }
                   
                   j = i;
                   i = 0;
                   comma++;             
                   brightness = 0;
                   
                   //convert array to one number
                   
                   for( x = 0,l = j; x<j; x++,l--)
                   {
                    brightness += temp[x]*pow(10,l-1);              
                 }
                 
                 brightness++;
                  analogWrite(pin[comma],brightness);
 
                 }while (comma <= 3);       
                 
         }
 }
 
