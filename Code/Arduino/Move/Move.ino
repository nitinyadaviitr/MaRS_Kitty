#define motor1  6
#define motor2  4
#define motor1pwm  10
#define motor2pwm  11

float theta1c, theta2c;

volatile int temp1, counter1 = 0;
volatile int temp2 , counter2 = 0;
void setup() {
  Serial.begin(9600);

  //Pins for encoders
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  attachInterrupt(2, ai2, RISING);
  attachInterrupt(3, ai3, RISING);

  //Pins for Motors
  pinMode(motor1, OUTPUT);
  pinMode(motor1pwm, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor2pwm, OUTPUT);

}

void loop() {
  if (Serial.available())
  {
    int x = Serial.parseInt();
    if (x) {
      if (x < 3)
      {
        digitalWrite(motor1, x - 1 );
        analogWrite(motor1pwm , 60);
      }
      else if(x == 3){
        analogWrite(motor1pwm , 0);
        }
      else if(x>3 && x<6){
        digitalWrite(motor2, x - 4 );
        analogWrite(motor2pwm , 30);
        }
      else if(x == 6){
        analogWrite(motor2pwm , 0);
        }
    }
  }

  //Convert Encoder Output into angle
      if ( counter1 != temp1 ) {
        temp1 = counter1;
        if (counter1 > 1200) {
          counter1 = 0;
         }
        theta1c = (counter1 * 0.3);
        Serial.println (theta1c);
     }
      if ( counter2 != temp2 ) {
        temp2 = counter2;
        if (counter2 > 1200) {
          counter2 = 0;
        }
        theta2c = (counter2 * 0.3);
        Serial.println (theta2c);
      }
}

// Encoder1
void ai0() {
  if (digitalRead(3) == LOW) {
    counter1++;
  } else {
    counter1--;
  }
}

void ai1() {
  if (digitalRead(2) == LOW) {
    counter1--;
  } else {
    counter1++;
  }
}

////  Encoder2
void ai2() {
  if (digitalRead(20) == LOW) {
    counter2++;
  } else {
    counter2--;
  }
}

void ai3() {
  if (digitalRead(21) == LOW) {
    counter2--;
  } else {
    counter2++;
  }
}
