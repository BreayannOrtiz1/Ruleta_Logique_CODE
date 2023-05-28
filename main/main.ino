#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 120 
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

// Group LEDS by
#define NUM_GROUPS_LEDS 2
#define NUM_SECCION 12  // Cantidad de secciones
#define MAX_LAPS  5 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int times_Vel_INIT[]  = {500, 500, 400, 300, 200, 200, 180, 170, 150, 120, 100, 80, 60, 50};
int times_Vel_END[]  = {50, 80, 100, 150, 180, 200, 350, 400, 500, 1000};


void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600);
}

void Encender_Seccion(int SEC, int Br, char color){
  if(color == 'R'){
    for(int i=0; i<NUM_GROUPS_LEDS; i++){
    pixels.setPixelColor((SEC*NUM_GROUPS_LEDS+i)%119, pixels.Color(Br, 0, 0));
    }
  }

  if(color == 'G'){
    for(int i=0; i<NUM_GROUPS_LEDS; i++){
    pixels.setPixelColor((SEC*NUM_GROUPS_LEDS+i)%119, pixels.Color(0, Br, 0));
    }
  }

  if(color == 'B'){
    for(int i=0; i<NUM_GROUPS_LEDS; i++){
    pixels.setPixelColor((SEC*NUM_GROUPS_LEDS+i)%119, pixels.Color(0, 0, Br));
    }
  }
  if(color == 'W'){
    for(int i=0; i<NUM_GROUPS_LEDS; i++){
    pixels.setPixelColor((SEC*NUM_GROUPS_LEDS+i)%119, pixels.Color(Br, Br, Br));
    }
  }
  
  pixels.show();
}

void loop(){

  pixels.clear();
  int P_btn = 1;

  if(P_btn){
    
    int random_laps = random(2,MAX_LAPS);
    int random_secc = random(0,NUM_SECCION);
    int random_total_secc = (random_laps*12)+random_secc;
  
    Serial.print("Numero total de secciones: ");
    Serial.println(random_total_secc);
    int delay_main = 450; 
    int i=0;

    for(i=0; i<(random_total_secc); i++){
    
      Encender_Seccion(i, 255, 'B');

      if(i < 14){  //Primer cuarto
        delay_main = times_Vel_INIT[i];
      }
      if(i > (random_total_secc-5)){
        delay_main = delay_main + 150;
      }
      Serial.println(delay_main);
      delay(delay_main);
      pixels.clear();
    }
    Encender_Seccion(i, 255, 'W');
    delay(delay_main+2000);
  }
}    
