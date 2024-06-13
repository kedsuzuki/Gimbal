/*
@file: joystick_test
@updated: 2024/05/13
@brief: Outputs joystick vrx and vry readings to serial monitor
*/

const int VRX_PIN = A0;   //x-axis joystick sensing pin
const int VRY_PIN = A1;   //y-axis joystick sensing pin
const int SW_PIN = 2;     //joystick button pin

int vrx_val = 0;
int vry_val = 0;
int vrx_max = 0;
int vry_max = 0;

int calibrateJoystick(const int);

void setup() {
  Serial.begin(9600);
  while(!Serial);

  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);

  // Calibrating joystick
  Serial.println("\nPlease push joystick DOWN (v) in 3 seconds.");
  delay(250);
  vrx_max = calibrateJoystick(VRX_PIN);
  Serial.print("VRX MAX: "); Serial.println(vrx_max);
  
  Serial.println("\nPlease push joystick LEFT (<--) in 3 seconds.");
  delay(250);
  vry_max = calibrateJoystick(VRY_PIN);
  Serial.print("VRY MAX: "); Serial.println(vry_max);

  Serial.println("Ready to use Joystick");

}

void loop() {
  // put your main code here, to run repeatedly:
  vrx_val = analogRead(VRX_PIN);
  vry_val = analogRead(VRY_PIN);

  Serial.print("VRX: "); Serial.print(vrx_val);
  Serial.print("\t");
  Serial.print("VRY: "); Serial.println(vry_val);

  delay(200);
}

int calibrateJoystick(const int pin){
  /* Get extrema values for joystick VRX and VRY */
  int N = 20;               //number of data points to average
  int t_prep = 3;            //time for end user to prepare for calibration test [seconds]
  
  int sum = 0;
  int extrema = 0;
  
  for( int j=0; j<t_prep; j++){    //wait for end user to put joystick into position
    Serial.print(j+1);
    Serial.print(" ");
    delay(1000);
  }  
  Serial.println("NOW HOLD");
  for( int i=0; i<N; i++ ){       //calculate average extrema value at joystick position
    sum += analogRead(pin); 
    delay(100);                   //delay of 100ms for N cycles == 0.1*N seconds
  }
  extrema = int(sum / N);

  return extrema;
}
