void keyboard(){
  for (int i = 0 ; i < 9 ; i++){
    if (!digitalRead(allkeys[i])){
      if (charkeys[i] == '%')
        Keyboard.write(KEY_BACKSPACE);
      else
        Keyboard.write(charkeys[i]);
      delay(70);
      while (!digitalRead(2));
      delay(40);
    }
  }
}
