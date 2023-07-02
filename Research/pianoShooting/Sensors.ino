void initSensors(){
  for(int s=0;s<SENSOR_NUM;s++){
    pinMode(SENSOR_START_PIN+s,INPUT_PULLUP);
    isButtonPrePushed[s]=false;
    isButtonPushed[s]=false;
  }
}

void readSensors(){
  anyButtonPushed=false;
  for(int s=0;s<SENSOR_NUM;s++){
    isButtonPushed[s] = false;
    if(digitalRead(SENSOR_START_PIN+s)==LOW){
      isButtonPushed[s]=true;
    }
    if(isButtonPushed[s] && !isButtonPrePushed[s]){
      isButtonTriggered[s] = true;
      anyButtonPushed=true;
    }
    else
      isButtonTriggered[s] = false;
      
    isButtonPrePushed[s] = isButtonPushed[s];
  }
}
