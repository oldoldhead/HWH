#include <FastLED.h>

CLEDController *ledController;
CRGB leds[LED_LEN];
CRGB BG_COLOR = CHSV(200,0,40);
const int COLOR_TABLE_LEN = 4;
int COLOR_TABLE[COLOR_TABLE_LEN][3] = {
  {140,150,255}, //blue
  {190,150,255}, //purple
  {20,150,255}, //orange
  {40,150,255} //yellow
};

void initLED(){
  delay(1000); // power-up safety delay
  pinMode(LED_PIN,OUTPUT);
  ledController=&FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_LEN).setCorrection( TypicalLEDStrip );
} 

void moveLED(){
  if(anyButtonPushed){  
    birdArray[birdArrayIndex]=0;
    if(isButtonTriggered[0])
      birdColor[birdArrayIndex]=1;
    else if(isButtonTriggered[2])
      birdColor[birdArrayIndex]=2;
    else if(isButtonTriggered[4])
      birdColor[birdArrayIndex]=3;
    else if(isButtonTriggered[1] || isButtonTriggered[3])
      birdColor[birdArrayIndex]=0;
  }

  birdArrayIndex++;  
  if(birdArrayIndex==MOVING_NUM)
      birdArrayIndex=0; 

  fill_solid(leds,LED_LEN,BG_COLOR); 
  for(int i=0;i<MOVING_NUM;i++){
    if(birdArray[i] >= 0){
      birdArray[i]+=MOVING_SPEED;
      //Serial.println(String("")+"[Index:"+birdArray[i]+" isBirdOnBeat:"+isBirdOnBeat[i]+" PATH_SECTION_TABLE[3]:"+PATH_SECTION_TABLE[3]+" ]");

    if(birdArray[i]>=LED_LEN){
        birdArray[i] = -1;
      }
    }
    int targetLed;
    for(int led=0;led<STRIP_LIGHT_LEN;led++){
      targetLed = birdArray[i]-led;
      if(targetLed>=0){
        leds[targetLed] = CHSV(COLOR_TABLE[birdColor[i]][0],COLOR_TABLE[birdColor[i]][1],100);
      }
    }
  }
}


void showLed(){
  //FastLED.delay(1000/15); 
  //delay(1);
  

  ledController->showLeds();
}
