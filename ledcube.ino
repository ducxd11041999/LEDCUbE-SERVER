//byte DS=A1;
//byte STCP=A2;
//byte SHCP=A3;
//#include <SoftwareSerial.h>
byte DS = 2;//  4
byte STCP = 3;// 5
byte SHCP = 4;// 16
int Tangz[8] = {5 ,6,7,8,9,10,11,12};//  0,2,14,12,13,15,3,1
//int Tangz[8] = {1, 3,5,13,12,14,2,0};
void setup() {
 Serial.begin(9600);
    pinMode(DS, OUTPUT);//ds
    pinMode( SHCP, OUTPUT);//stcp
    pinMode( STCP, OUTPUT);//shcp
  for (int x = 0; x < 8; x++) {
    pinMode(Tangz[x], OUTPUT);
  }
//  while (!Serial) {
//    ;
//  }
//  if (!SD.begin(10)) {
//    //Serial.println("initialization failed!");
//    return;
//  }
  //Serial.println("initialization done.");
}
void dich74hc595(byte a){
    if (a==0) {
        digitalWrite(DS, LOW);
        digitalWrite(SHCP, HIGH);
        digitalWrite(SHCP, LOW);
    } else if(a==1) {
        digitalWrite(DS, HIGH);
        digitalWrite(SHCP, HIGH);
        digitalWrite(SHCP, LOW);
    }
}
void mo74hc595() {
    digitalWrite(STCP, HIGH);
    digitalWrite(STCP, LOW);
}
void reset() {
    for (byte t=0; t<64; t++) {
        dich74hc595(0);
    }
    mo74hc595();
}
void hienthi(byte mangba[8][8][8], byte Solan){
      for (byte t=0; t<Solan; t++) { // so 7 la thoi gian qua 1 tang
        //to chinh la toc do roi cua mua
        for (byte z=0; z<8; z++) {
          for (byte x=0; x<8; x++) {
            for (byte y=0; y<8; y++) {
              dich74hc595(mangba[x][y][z]);
            }
          }
          mo74hc595();
          digitalWrite(Tangz[z], HIGH);   
          reset();
          digitalWrite(Tangz[z], LOW);
        }
      }
}
void mua(int solanmua, byte Solan)
{
    byte mangba[8][8][8] = { 0 };
    for (byte s = 0; s < solanmua; s++)
    {
        byte n = random(1, 5); // cho?n ngâ~u nhiên sô´ ha?t mua roi
        for (byte h = 0; h < n; h++)
        {
            byte x = random(0, 8); // cho?n ngâ~u nhiên mô?t toa? dô? ha?t mua
            byte y = random(0, 8);
            mangba[x][y][7] = 1; // Cho ca´i ha?t mua do´ =1 dê? ca´i de`n do´ sa´ng lên
        }
        hienthi(mangba, Solan); // hiê?n thi?
        for (byte z = 0; z < 7; z++)
        { // do`i ca´c tâ`ng z xuô´ng mô?t tâ`ng
            for (byte x = 0; x < 8; x++)
            { // nhung pha?i giu~ nguyên toa? dô? theo x, y dê? mua roi tha?ng
                for (byte y = 0; y < 8; y++)
                {
                    mangba[x][y][z] = mangba[x][y][z + 1];
                }
            }
        }
        for (byte x = 0; x < 8; x++)
        {
            for (byte y = 0; y < 8; y++)
            {
                mangba[x][y][7] = 0; // tra? tâ`ng z=7 vê` 0
            }
        }
    }
}
void plane(char truc, byte Solan)
{
    byte mangba[8][8][8] = { 0 };
    for (byte i = 0; i < 8; i++)
    {
        for (byte z = 0; z < 8; z++)
        {
            for (byte x = 0; x < 8; x++)
            {
                for (byte y = 0; y < 8; y++)
                {
                    mangba[x][y][z] = 0;
                    if (truc == 'X')
                    {
                        mangba[i][y][z] = 1;
                    }
                    if (truc == 'Y')
                    {
                        mangba[x][i][z] = 1;
                    }
                    if (truc == 'Z')
                    {
                        mangba[x][y][i] = 1;
                    }
                }
            }
        }
        hienthi(mangba, Solan);
    }
    for (int i = 7; i >= 0; i--)
    {
        for (byte z = 0; z < 8; z++)
        {
            for (byte x = 0; x < 8; x++)
            {
                for (byte y = 0; y < 8; y++)
                {
                    mangba[7 - x][7 - y][7 - z] = 0;
                    if (truc == 'X')
                    {
                        mangba[i][7 - y][7 - z] = 1;
                    }
                    if (truc == 'Y')
                    {
                        mangba[7 - x][i][7 - z] = 1;
                    }
                    if (truc == 'Z')
                    {
                        mangba[7 - x][7 - y][i] = 1;
                    }
                }
            }
        }
        hienthi(mangba, Solan);
    }
}
void plane2(char truc, byte Solan)
{
    byte mangba[8][8][8] = { 0 };
    byte manghai[8][8] = { 0 }; //Ðây la` ma?ng du`ng dê? da´nh dâ´u la` de`n na`o da~ bi? bo? la?i
    for (byte x = 0; x < 8; x++)
    { // Ta?o ra mô?t ma?ng sa´ng truo´c khi do`i di
        for (byte y = 0; y < 8; y++)
        {
            if (truc == 'X')
            {
                mangba[0][x][y] = 1;
            }
            else if (truc == 'Y')
            {
                mangba[x][0][y] = 1;
            }
            else
            {
                mangba[x][y][0] = 1;
            }
        }
    }
    hienthi(mangba, Solan * 2);
    for (byte i = 1; i < 8; i++)
    { 
        byte u = 0;
        while (u < 8)
        { 
            byte x = random(8);
            byte y = random(8);
            if (manghai[x][y] == 0)
            {
                manghai[x][y] = 1;
                u = u + 1;
                hienthi(mangba, 1); 
            }
        }
        for (byte x = 0; x < 8; x++)
        { 
            for (byte y = 0; y < 8; y++)
            {
                if (manghai[x][y] == 0)
                {
                    if (truc == 'X')
                    {
                        mangba[i][x][y] = 1;
                        mangba[i - 1][x][y] = 0;
                    }
                    else if (truc == 'Y')
                    {
                        mangba[x][i][y] = 1;
                        mangba[x][i - 1][y] = 0;
                    }
                    else if (truc == 'Z')
                    {
                        mangba[x][y][i] = 1;
                        mangba[x][y][i - 1] = 0;
                    }
                }
            }
        }
    }
    hienthi(mangba, Solan);
    // nguo?c la?i
    for (byte z = 0; z < 8; z++)
    { 
        for (byte i = 1; i < 8 - z; i++)
        {
            for (byte x = 0; x < 8; x++)
            {
                for (byte y = 0; y < 8; y++)
                {
                    if (truc == 'X')
                    {
                        if (mangba[7 - i][x][y] == 1)
                        {
                            mangba[7 - i + 1][x][y] = 1;
                            mangba[7 - i][x][y] = 0;
                        }
                    }
                    else if (truc == 'Y')
                    {
                        if (mangba[x][7 - i][y] == 1)
                        {
                            mangba[x][7 - i + 1][y] = 1;
                            mangba[x][7 - i][y] = 0;
                        }
                    }
                    else
                    {
                        if (mangba[x][y][7 - i] == 1)
                        {
                            mangba[x][y][7 - i + 1] = 1;
                            mangba[x][y][7 - i] = 0;
                        }
                    }
                }
            }
        }
        hienthi(mangba, Solan + 4); 
    }
}
void clrArr(byte arr[8][8][8])
{
  arr[8][8][8] = {0};
  hienthi(arr,5);
  delay(20);
  }
void Love(int solan)
{ 
  byte  mangba[8][8][8] = {0};
  for(int i=0;i<solan;i++)
  {
   for(byte x=1;x<=6;x++)
    for(byte y=3;y<5;y++)
      {
        mangba[x][y][1]=1;
        mangba[x][y][6]=1;
        mangba[x][y][7]=1;
        hienthi(mangba,1);
      }
     
     for(byte x=3;x<=4;x++)
      for(byte y=3;y<5;y++)
        for(byte z=2;z<6;z++)
           {
             mangba[x][y][z]=1;
             mangba[x][y][z]=1;
             hienthi(mangba,1);
           }
 
   delay(500);
   byte mangba[8][8][8] = {0};
   hienthi(mangba,1);
   for(byte z = 1;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =0 ; x<8;x++)
          {
            if(z==1&&(x==3||x==4))
            {
              mangba[x][y][z]=1;
            }
            if(z==2&&(x==2||x==5))
            {
              mangba[x][y][z]=1;
            }
            if(z==3&&(x==1||x==6))
            {
              mangba[x][y][z]=1;
            }
            if(z==4&&(x==0||x==7))
            {
              mangba[x][y][z]=1;
            }
            if((z==5||z==6)&&(x==0||x==7||x==3||x==4))
            {
              mangba[x][y][z]=1;
            }
            if(z==7&&(x==1||x==6||x==2||x==5))
            {
              mangba[x][y][z]=1;
            }
           
          }
      }
       hienthi(mangba,5);   
   }
   delay(500);
   byte mangba_[8][8][8] = {0};
   hienthi(mangba_,2);
   for(byte z = 1;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =0 ; x<8;x++)
          {
            if(z==1&&(x>=2&&x<=5))
            {
              mangba_[x][y][z]=1;
            }
            if(z>=2&&(x==1||x==6))
            {
              mangba_[x][y][z]=1;
            }
           
          }
      }
       hienthi(mangba_,5);   
   }
   delay(500);
  }
}
//--------------------------chu a
void A()
{
  byte mangba[8][8][8] = {0};
   hienthi(mangba,2);
   for(byte z = 0;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =1 ; x<8;x++)
          {
            if((z<=5)&&(x==1||x==6))
            {
              mangba[x][y][z]=1;
            }
            if(z==4&&(x>=2&&x<=5))
            {
              mangba[x][y][z]=1;
            }
            if((z==6)&&(x==2||x==5))
            {
              mangba[x][y][z]=1;
            }
            if((z==7)&&(x==3||x==4))
            {
              mangba[x][y][z]=1;
            }
          }
      }
       hienthi(mangba,5);   
   }
   delay(500);
}
void B()
{
  byte mangba[8][8][8] = {0};
   hienthi(mangba,2);
   for(byte z = 0;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =1 ; x<=6;x++)
          {
            
            if((z==0||z==4||z==7)&&(x>=1&&x<=5))
            {
              mangba[x][y][z]=1;
            }
            if((z==1||z==2||z==3||z==4||z==6)&&(x==1||x==2||x==6))
            {
              mangba[x][y][z]=1;
            }
          }
      }
       hienthi(mangba,5);   
   }
   delay(500);
}
void M()
{
   byte mangba[8][8][8] = {0};
   hienthi(mangba,2);
   for(byte z = 1;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =0 ; x<=7;x++)
          {
            
            if((z>=1&&z<=6)&&(x==0||x==1||x==6||x==7))
            {
              mangba[x][y][z]=1;
            }
            if((z==4)&&(x==3||x==4))
            {
              mangba[x][y][z]=1;
            }
            if((z==5)&&(x==2||x==5))
            {
              mangba[x][y][z]=1;
            }
          }
      }
       hienthi(mangba,5);   
   }
   delay(500);
}
void E()
{
   byte mangba[8][8][8] = {0};
   hienthi(mangba,2);
   for(byte z = 0;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =0 ; x<=7;x++)
          {
            if((z<=7)&&(x==0||x==1||x==2))
            {
              mangba[x][y][z]=1;
            }
            if((z==0||z==7)&&(x>=3&&x<=6))
            {
              mangba[x][y][z]=1;
            }
            if((z==4)&&(x==3||x==5||x==4))
            {
              mangba[x][y][z]=1;
            }
          }
      }
       hienthi(mangba,5);   
   }
   delay(500);
}
void C()
{
   byte mangba[8][8][8] = {0};
   hienthi(mangba,2);
   for(byte z = 0;z<8;z++)
   {
      for(byte y = 2 ; y <=5;y++)
      {
        for(byte x =0 ; x<=7;x++)
          {
            if((z>=1&&z<=6)&&(x==1))
            {
              mangba[x][y][z]=1;
            }
            if((z==0||z==7)&&(x>=2&&x<=5))
            {
              mangba[x][y][z]=1;
            }
            if((z==1||z==6)&&(x==6))
            {
              mangba[x][y][z]=1;
            }
          }
      }
       hienthi(mangba,5);   
   }
   delay(500);
}

void Domino()
{
  byte mangba[8][8][8] = {0};
  for(byte z=0; z<8;z++)
     for(byte y=0;y<8;y++)
        for(byte x=0;x<8;x++)
        {
          mangba[x][y][z]=1;
          hienthi(mangba,1);
        }
}
void loop() {
    if(Serial.available()) // if data is coming
  { 
//     Serial.write(Serial.read());
     char databuffer={};
     databuffer = Serial.read();
     switch (databuffer)
     {
     case '1':
        mua(100, 7);
        break;
     case '2':
        Love(3);
        break;
     case '3':
        plane('X', 4);
        plane('Y', 4);
        plane('Z', 4);
        plane2('X', 4);
        plane2('Y', 4);
        plane2('Z', 4);
        break;
     case '4':
        Domino();
        break;
     case '5':
        C();
        E();
        E();
        C();
        break;
     default:
        A();
        B();
        C();
        break;
     }
     databuffer={};
  }
}
