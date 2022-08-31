bool keysSit[] = {false,false,false,false,false,false,false,false,false};
bool lastKeysSit[] = {false,false,false,false,false,false,false,false,false};

void keyboard(){
  for (int i = 0 ; i < 9 ; i++){
    lastKeysSit[i] = keysSit[i];
    keysSit[i] = !digitalRead(allkeys[i]);
  }
}


void keysOperate(){
  Keyboard.releaseAll();

  for (int i = 0 ; i < 9 ; i++){
    if (keysSit[i]){
      if (charkeys[i] == 0){
        if (funckeys[i] < 16){
          if (funckeys[i] % 2 == 1)
            Keyboard.press(KEY_LEFT_GUI);
          if (funckeys[i] >= 8)
            Keyboard.press(KEY_LEFT_SHIFT);
          if ( ((funckeys[i] >= 4) && (funckeys[i] <= 7)) || ((funckeys[i] >= 12) && (funckeys[i] <= 15)) )
            Keyboard.press(KEY_LEFT_ALT);
          if ( (funckeys[i] == 2) && (funckeys[i] == 3) && (funckeys[i] == 6) && (funckeys[i] == 7) && (funckeys[i] == 10) && (funckeys[i] == 11) && (funckeys[i] == 14) && (funckeys[i] == 15) )
            Keyboard.press(KEY_LEFT_CTRL);
        }
      }
    }
  }
  
  for (int i = 0 ; i < 9 ; i++){
    if (keysSit[i]){
      if (!lastKeysSit[i]){
        
        if (funckeys[i] < 16){
          if (funckeys[i] % 2 == 1)
            Keyboard.press(KEY_LEFT_GUI);
          if (funckeys[i] >= 8)
            Keyboard.press(KEY_LEFT_SHIFT);
          if ( ((funckeys[i] >= 4) && (funckeys[i] <= 7)) || ((funckeys[i] >= 12) && (funckeys[i] <= 15)) )
            Keyboard.press(KEY_LEFT_ALT);
          if ( (funckeys[i] == 2) && (funckeys[i] == 3) && (funckeys[i] == 6) && (funckeys[i] == 7) && (funckeys[i] == 10) && (funckeys[i] == 11) && (funckeys[i] == 14) && (funckeys[i] == 15) )
            Keyboard.press(KEY_LEFT_CTRL);
        }

        if (charkeys[i] == 0)
          ;
        else if (charkeys[i] == 1)
          Keyboard.write(KEY_TAB);
        else if (charkeys[i] == 2)
          Keyboard.write(KEY_CAPS_LOCK);
        else if (charkeys[i] == 3)
          Keyboard.write(KEY_BACKSPACE);
        else if (charkeys[i] == 4)
          Keyboard.write(KEY_RETURN);
        else if (charkeys[i] == 5)
          Keyboard.write(KEY_PAGE_UP);
        else if (charkeys[i] == 6)
          Keyboard.write(KEY_PAGE_DOWN);
        else if (charkeys[i] == 7)
          Keyboard.write(KEY_UP_ARROW);
        else if (charkeys[i] == 8)
          Keyboard.write(KEY_DOWN_ARROW);
        else if (charkeys[i] == 9)
          Keyboard.write(KEY_LEFT_ARROW);
        else if (charkeys[i] == 10)
          Keyboard.write(KEY_RIGHT_ARROW);
        else if (charkeys[i] == 11)
          Keyboard.write(KEY_ESC);
        else if (charkeys[i] == 12)
          Keyboard.write(' ');
        else if (charkeys[i] == 13)
          Keyboard.write(KEY_F1);
        else if (charkeys[i] == 14)
          Keyboard.write(KEY_F2);
        else if (charkeys[i] == 15)
          Keyboard.write(KEY_F3);
        else if (charkeys[i] == 16)
          Keyboard.write(KEY_F4);
        else if (charkeys[i] == 17)
          Keyboard.write(KEY_F5);
        else if (charkeys[i] == 18)
          Keyboard.write(KEY_F6);
        else if (charkeys[i] == 19)
          Keyboard.write(KEY_F7);
        else if (charkeys[i] == 20)
          Keyboard.write(KEY_F8);
        else if (charkeys[i] == 21)
          Keyboard.write(KEY_F9);
        else if (charkeys[i] == 22)
          Keyboard.write(KEY_F10);
        else if (charkeys[i] == 23)
          Keyboard.write(KEY_F11);
        else if (charkeys[i] == 24)
          Keyboard.write(KEY_F12);
        else
          Keyboard.write((char)(charkeys[i]+8));
      }
    }
  }

  
}
