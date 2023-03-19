//Abdulsamet Alkan

/*Bu projenin amaci alkollu mekanlara arabalariyla gidip arabalarini orda birakarak eve taksiyle donen insanlari kendi
arabalariyla evlerine birakan bir servis sağlamak. Projenin arduino kisminda bir alkolmetre yer aliyor.  */

//PIN MAP
#define CLK 8
#define DIN 9
#define DO 10
#define CE 11 
#define rST 12 //R'yi buyuk yazinca hata veriyor. Nedenini anlamadigimdan kucuk yazdim.

enum ProgessBarX{baslangicX=2, bitisX=81};
enum ProgessBarY{baslangicY=38, bitisY=47};

#include <LCD5110_Graph.h> //LCD kutuphanesi
LCD5110 myGLCD(CLK,DIN,DO,CE,rST); //LCD pinlerinin arduino uzerinde hangi pinlere baglandıgını LCD kutuphanemize veriyoruz.
//Soldan saga sirasiyla LCD  uzerinde 8-CLK, 9-DIN, 10-DO, 11-CE, 12-RST pinlerine baglidir.

extern unsigned char TinyFont[]; //Yazi tipleri
extern uint8_t BigNumbers[];

int maxval=0; //MQ3 tarafindan okunacak en buyuk degeri tutar.
int birasayisi=0; //Okunan degerin kac biraya denk geldigini gosteren bir sayac.

void setup() {
  myGLCD.InitLCD(); //LCD baslatilir.
  pinMode(A2,INPUT); //MQ3 sensor modulunun bagli oldugu Analog input
}

void loop() {
  int alkol=analogRead(A2); //Sensorden okunan anlık degerler alkol degiskeninde kayit edilip ekrana yazdırilir.
  int alkol_grafik= map(alkol,0,1023,baslangicX,bitisX); //Okunan alkol degerini progressbar ile göstermek icin okunan degerler 2 ile 81 arasina cekilir.
  //Burada 2(baslangic) ve 81(bitis) LCD ekrandaki progressbarin x ekseninde baslangıc ve bitis konumlaridir aslinda.

  myGLCD.clrScr(); //Ekran buffer'i temizlenir.
  myGLCD.setFont(BigNumbers); //A2'den alinan alkol degiskeni ekrana yazdirilir ve fontu ayarlanir.
  myGLCD.printNumI(alkol,10,10);

  myGLCD.setFont(TinyFont); //Ekranin en üst merkezine baslik atilir
  myGLCD.print("ALCOOTEST", CENTER, 0);

  cerceve(); //Progressbar icin yazdigimiz fonksiyonu cagirirarak bir cerceve olusturuyoruz.
  yuzde_dolum(alkol_grafik); //2-81 araligina cektigimiz input degeri progressbari doldurmak icin bu fonksiyona verilir.

  if(alkol>maxval){ //Alkolmetrede okunan deger maxval degiskeninde tutulur.
    maxval=alkol;
  }
  //Bu if bloklari analog pinden okunan degerlerin araliklarina göre kullanicinin tukettigi alkol miktarinin kac biraya denk geldigini birasayisi degiskenine atar.
  //Sayilar rastgeledir.
  
  if(maxval<=150){ 
    birasayisi=0;
  }
  if(maxval>150 && maxval <=210){
    birasayisi=1;
  }
  if(maxval>210 && maxval <=270){
    birasayisi=2;
  }
  if(maxval>270 && maxval <330){
    birasayisi=3;
  }
  else birasayisi=4;

  myGLCD.print("MAX: ",55,15); //Print icinde yazilan sayilar sirasiyle x ve y eksenindeki konumlari belirtir.
  myGLCD.print("BIERE: ",55,25);
  myGLCD.printNumI(birasayisi,78,25);
  myGLCD.printNumI(maxval,72,15);
  myGLCD.update();
  delay(100);
}


void cerceve(){ //Koordinat uzerinde x icin 2-81, y icin 38-47 aralıgında progressbar cercevesi olusturulur.
  myGLCD.drawRect(baslangicX, baslangicY, bitisX, bitisY);
  myGLCD.update();
  }
void yuzde_dolum(int yuzde){ //2-81 araligina cektigimiz input degeri(x degeri) progressbari yatay cizgilerle doldurmak icin kullanilir.
  myGLCD.drawLine(baslangicX,39,yuzde,39);
  myGLCD.drawLine(baslangicX,40,yuzde,40);
  myGLCD.drawLine(baslangicX,41,yuzde,41);
  myGLCD.drawLine(baslangicX,42,yuzde,42);
  myGLCD.drawLine(baslangicX,43,yuzde,43);
  myGLCD.drawLine(baslangicX,44,yuzde,44);
  myGLCD.drawLine(baslangicX,45,yuzde,45);
  myGLCD.drawLine(baslangicX,46,yuzde,46);
  
  }
