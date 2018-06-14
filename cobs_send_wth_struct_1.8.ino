/*This code takes values from structure and encode them with...
 * Consistent Overhead Byte Stuffing (COBS) algoritm
 * 
 * First code checks the negative values. Save which values...
 * have a negative sign. After that converts 10 bit values...
 * to 2 bit and 8 bit values and stores them in array called
 * "temp_array" . 
 * 
 * Since this process is in function we never .
 * use that array name on the loop.We use return value directly 
 * like this:
 *  "make_prepackage(balance_robot)"  where 'balance_robot' is..
 * the structure and 'make_prepackage' is the name of function.
 * 
 * After that we have a array which can be use as a input for 
 * encoding function:
 * StuffData()
 * 
 */


typedef struct  {
    int16_t  angle;
    int16_t output_raw;
    int8_t output_pwm;
    int8_t  p_value;
    int8_t  i_value;
    int8_t  d_value;
}Balance_robot;

unsigned char* make_prepackage( Balance_robot x);

Balance_robot balance_robot;

void printArray(int *ptr, size_t length);     
void StuffData(const unsigned char *ptr, unsigned long length, unsigned char *dst) ;
unsigned char dest[11] ;
char* target ;



void setup() {
Serial.begin(9600);


balance_robot.angle =35;
balance_robot.output_raw =42;
balance_robot.output_pwm =100;
balance_robot.p_value =0;
balance_robot.i_value =1;
balance_robot.d_value =-16;

}

void loop() {
//printArray(target,9);     
target=make_prepackage(balance_robot);//neccesary for allocation ?
StuffData(target,9,dest); 
   for(int i =0 ; i<11; i++)
  { Serial.write(dest[i]);}
  

delay(2000);
}





unsigned char* make_prepackage( Balance_robot x){
  
int8_t  lenght =9;

int16_t temporary[6] ;
int8_t  temp_array[lenght];
int8_t  temp_array2[lenght]={0,0,0,0,0,0,0,0,0};
int8_t n,n0,n1,n2,n3,n4,n5=0;

//  Serial.write( x.angle ) ;// temporary[0]
//  Serial.write( x.output_raw ) ;// temporary[0]
//  Serial.write( x.output_pwm ) ;// temporary[0]
//  Serial.write( x.p_value ) ;// temporary[0]
//  Serial.write( x.i_value ) ;// temporary[0]
//  Serial.write( x.d_value ) ;// temporary[0]

         if(x.angle<0){
                n0=1;
                temporary[0]=x.angle*-1;
                }
          else{  
                 n0=0;
                temporary[0]=(x.angle);}
                
  
                if(x.output_raw<0){
                n1=1;
                 temporary[1]=(x.output_raw)*-1;
                }else{
                    n1=0;
                temporary[1]=(x.output_raw);}
                
        if(x.output_pwm<0){
                n2=1;
                 temporary[2]=(x.output_pwm)*-1;
                }else{
                   n2=0;
                temporary[2]=(x.output_pwm);}
                
        if(x.p_value<0){
                n3=1;
                 temporary[3]=(x.p_value)*-1;
                }else{
                   n3=0;
                temporary[3]=(x.p_value);}
                
         if(x.i_value<0){
                n4=1;
                temporary[4]=(x.i_value)*-1;
                }else{
                   n4=0;
                temporary[4]=(x.i_value);}
                
         if(x.d_value<0){
                n5=1;
                 temporary[5]=(x.d_value)*-1;
                }else{
                   n5=0;
                temporary[5]=(x.d_value);}

//   for(int i =0 ; i<6; i++)
//  { 
//    Serial.write( temporary[i] ) ;//x.angle
//   }

   
n=n0*1+n1*2+n2*4+n3*8+n4*16+n5*32;
//Serial.write(  n ) ;//x.angle

temp_array[0]= n;

temp_array[1]= temporary[0] >> 8; // 256 ya böl
temp_array[2]= temporary[0]<< 2;  //  4 ile çarp
temp_array[3]= temporary[1] >> 8;
temp_array[4]= temporary[1] << 2;
temp_array[5]= temporary[2] ;
temp_array[6]= temporary[3] ;
temp_array[7]= temporary[4];
temp_array[8]= temporary[5];

// for(int i =0 ; i<3; i++)
//  { 
//   Serial.write( temp_array[i] ) ;//x.angle
//   }
  // Serial.write( 35 ) ;//x.angle

// for(int i =0 ; i<9; i++)
//  { 
//   temp_array2[i]=  temp_array[i]  ;//x.angle
//   // Serial.write( temp_array[3] ) ;
//   }
   
delay(1);
return  temp_array;
 
  
}



#define FinishBlock(X) (*code_ptr = (X),  code_ptr = dst++,   code = 0x01  )
void StuffData(const unsigned char *ptr, unsigned long length, unsigned char *dst) 
{


 unsigned char *zero=0;
 unsigned char *dst2;
 
  const unsigned char *end = ptr + length; //başlangıç adresi + uzunluk ile dizideki son degerin adresini belirle
  unsigned char *code_ptr = dst++;  // dst nin 1. elemanının adresini code_ptr ye at
  unsigned char code = 0x01; //counter for 255 adet data
while (ptr < end) // ptr dizisinin sonuna ulaşana dek...
{ 
   if (*ptr == 0) FinishBlock(code); 
  else { 
    *dst++ = *ptr;
    code++; 
     if (code == 0xFF)FinishBlock(code);
     } 
    
    ptr++; 
   // if (ptr - end==0)  *dst++ = zero;
  dst2  =dst;
  } 
   
FinishBlock(code);
dst=dst2;
 //*dst++ = zero; 
//  *dst++=*zero;
}











void printArray(char *ptr, size_t length)            
{         
    //for statement to print values using array             
    size_t i = 0;
    for( ; i < length; ++i )      
    Serial.write(ptr[i]);        
} 
