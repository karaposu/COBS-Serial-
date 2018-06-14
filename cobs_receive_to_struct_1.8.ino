/*
 * This code extracts datas from serial packages and send them to strucure 
 * called  balance_robot
 */


typedef struct  {
    int16_t  angle;
    int16_t output_raw;
    int8_t output_pwm;
    int8_t  p_value;
    int8_t  i_value;
    int8_t  d_value;
}Balance_robot;

Balance_robot balance_robot;

void printArray(int *ptr, size_t length); 
void UnStuffData(const unsigned char *ptr, unsigned long length,unsigned char *dst) ;

unsigned char dest[8] ;
unsigned char paket[10];


void setup() {
Serial.begin(9600);



}

void loop() {

readpaket4();
UnStuffData(paket,11,dest) ;
make_real_data();

//Serial.write(balance_robot.angle) ;
//Serial.write(balance_robot.output_raw);
//Serial.write(balance_robot.output_pwm) ;
//Serial.write(balance_robot.p_value);
//Serial.write(balance_robot.i_value);
//Serial.write(balance_robot.d_value) ;



delay(10);

}




void make_real_data()
{
     int16_t balance_robot_values[6];
    balance_robot_values[0] =(dest[1] *256) + (dest[2] / 4);
    balance_robot_values[1]=(dest[3] *256) + (dest[4] / 4);
    balance_robot_values[2]=dest[5] ;
    balance_robot_values[3]=dest[6] ;
    balance_robot_values[4]=dest[7] ;
    balance_robot_values[5]=dest[8] ;
    
      for(int i=0;i<6;i++) {
                     if ((dest[0] >> i) & 1) {
                            balance_robot_values[i]=balance_robot_values[i]*-1;
                  
                    } else {
                         balance_robot_values[i]=balance_robot_values[i];
                     }
                   }
    
    balance_robot.angle =balance_robot_values[0];
    balance_robot.output_raw =balance_robot_values[1];
    balance_robot.output_pwm =balance_robot_values[2] ;
    balance_robot.p_value =balance_robot_values[3] ;
    balance_robot.i_value =balance_robot_values[4];
    balance_robot.d_value =balance_robot_values[5] ;
}













void readpaket4() 
{
  int counter=0;
  int v=1;
   while(v != 0){
      v=readByte();
       paket[counter]=v;
       counter++;
       
     }
     
}
   
 




int readByte() {
   while (true) {
     if (Serial.available() > 0) {
     return Serial.read();
   }
 }
}


       
void UnStuffData(const unsigned char *ptr, unsigned long length,unsigned char *dst) 
{ 
  const unsigned char *end = ptr + length; 
  while (ptr < end) 
  { 
  int i, code = *ptr++; for (i=1; i<code; i++) *dst++ = *ptr++; if (code < 0xFF) *dst++ = 0; } }






void printArray(char *ptr, size_t length)            
{         
    //for statement to print values using array             
    size_t i = 0;
    for( ; i < length; ++i )      
    Serial.write(ptr[i]);        
} 





