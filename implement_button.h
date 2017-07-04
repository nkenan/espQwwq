bool button1pressed = false;
bool button2pressed = false;

void implement_button_setup() {
  pinMode(BUTTON1, INPUT);  
};

void implement_button_loop() {
// ##### BUTTON 1
  if (BUTTON1_INVERTED) {
    if(digitalRead(BUTTON1) == LOW) {
      button1pressed = true;
    } else {
      button1pressed = false;
    };
  } else {
    if(digitalRead(BUTTON1) == HIGH) {
      button1pressed = true;
    } else {
      button1pressed = false;
    };
  };
  if (button1pressed) {
    toggle(RELAY1, 1, 500);    
    button1pressed = false;
  };

// ##### BUTTON 1
  if (BUTTON2_INVERTED) {
    if(digitalRead(BUTTON2) == LOW) {
      button2pressed = true;
    } else {
      button2pressed = false;
    };
  } else {
    if(digitalRead(BUTTON2) == HIGH) {
      button2pressed = true;
    } else {
      button2pressed = false;
    };
  };
  if (button2pressed) {
    toggle(RELAY2, 1, 500);    
    button2pressed = false;
  };
};
