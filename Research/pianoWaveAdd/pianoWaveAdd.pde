
final int LED_LEN = 300;
final int PIXEL_SIZE = 3;
final int BRIGHTNESS_MAX = 255;
final int KEY_NUM = 5;
final int INPUT_BUFFER_SIZE = 300;
final float LED_SPEED = 1;

int[][] LED_KEY_MAPPING = {  //brightness, len
  //{128, 20},
  //{-128, 16},
  //{128, 12},
  //{-128, 8},
  //{128, 4}
  {50, 20},
  {-50, 16},
  {50, 12},
  {-50, 8},
  {50, 4}
};

int[] ledColor = new int[LED_LEN];
float[] ledPosition = new float[INPUT_BUFFER_SIZE];
int[] ledKey = new int[INPUT_BUFFER_SIZE];
boolean[] ledDir = new boolean[INPUT_BUFFER_SIZE];
int ledBufferIndex = 0;

void setup(){
  size(900,200);
  noStroke();
  initLed();
}

void draw(){
  updateLed();
  drawLed();
}

void initLed(){
  for(int i=0;i<LED_LEN;i++){
    ledColor[i] = 0;
  }
  for(int i=0;i<INPUT_BUFFER_SIZE;i++){
    ledPosition[i] = -1;
    ledDir[i] = true;
  }
}

void updateLed(){
  //=============reset led =============
  for(int i=0;i<LED_LEN;i++){
    ledColor[i] = 0;
  }
  for(int i=0;i<INPUT_BUFFER_SIZE;i++){
    //=============move led=============
    if(ledPosition[i]>=0){
      if(ledDir[i]){
        ledPosition[i]+=LED_SPEED;
        if(ledPosition[i]>=LED_LEN){
          ledPosition[i] -= LED_SPEED;
          ledDir[i]=false;
        }
      }
      else{
        ledPosition[i]-=LED_SPEED;
        if(ledPosition[i]<0){
          ledPosition[i]+=LED_SPEED;
          ledDir[i]=true;
        }
      }
    }
    
    //=============fill led=============
    if(ledPosition[i]>=0){
      //println(i);
      for(int t=0;t<LED_KEY_MAPPING[ledKey[i]][1];t++){
        if(ledDir[i]){
          int target = int(ledPosition[i])-t;
          if(target<0)target = 0-target;
          if( target>=0 && target < LED_LEN){
            ledColor[target] += LED_KEY_MAPPING[ledKey[i]][0];
          }
        }
        else{
          int target = int(ledPosition[i])+t;
          if(target >= LED_LEN)target = 2*(LED_LEN -1) - target ;
          if( target>=0 && target < LED_LEN){
            ledColor[target] += LED_KEY_MAPPING[ledKey[i]][0];
          }
        }
      }
    }
  }
}

void drawLed(){
  for(int i=0;i<LED_LEN;i++){
    fill(constrain(abs(ledColor[i]),0,BRIGHTNESS_MAX));
    rect(i*PIXEL_SIZE,height/2,PIXEL_SIZE,20);
  }
}

void keyPressed(){
  int keyTarget = -1;
  if(key=='j')
    keyTarget=0;
  else if(key=='i')
    keyTarget=1;
  else if(key=='k')
    keyTarget=2;
  else if(key=='o')
    keyTarget=3;
  else if(key=='l')
    keyTarget=4;
  
  println(ledBufferIndex);
  if(keyTarget>=0){
    ledPosition[ledBufferIndex] = 0.1;
    ledDir[ledBufferIndex] = true;
    ledKey[ledBufferIndex]=keyTarget;
    ledBufferIndex= (ledBufferIndex+1)%INPUT_BUFFER_SIZE;
  }
  
}
