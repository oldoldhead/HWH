#define PATH_SECTION_NUM 14
#define MOVING_NUM 120
#define MOVING_SPEED 4
#define BEAT_TOLERANCE 120  //ms
#define BPM 200 //100*2 for falf beat

#define LED_TYPE    WS2811
#define COLOR_ORDER RGB

#define LED_PIN 2

#define LED_LEN 300

#define SENSOR_START_PIN 8
#define SENSOR_NUM 5

#define TIK_PIN 13
#define STRIP_LIGHT_LEN 10 //for ramp light

int buttonPushedNum = 0;
boolean isButtonPushed[SENSOR_NUM];
boolean isButtonPrePushed[SENSOR_NUM];
boolean isButtonTriggered[SENSOR_NUM];
int birdArray[MOVING_NUM];
int birdArrayIndex = 0 ;
int birdColor[MOVING_NUM];
boolean anyButtonPushed = false;

void setup() {
  delay(200);
  Serial.begin(9600);
  initLED();
  initSensors();
}

void loop() {
  readSensors();
  moveLED();
  showLed();
}
