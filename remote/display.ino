void setupDisplay() {
  display.begin(0x3C, true); // Address 0x3C default
  display.clearDisplay();
  display.display();
  display.setRotation(1);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
}

void refreshDisplay() {
  display.clearDisplay();
  display.setCursor(0,0);

  if(Bluefruit.Central.connected()) {
    display.println("Connected");
  }
  else{
    display.println("Not Connected");
  }
  
  display.print("A:");
  if(buttonA) display.print("X "); else display.print("O ");
  display.print("B:");
  if(buttonB) display.print("X "); else display.print("O ");
  display.print("C:");
  if(buttonC) display.print("X "); else display.print("O ");
  display.print("L:");
  if(buttonL) display.print("X "); else display.print("O ");
  display.print("R:");
  if(buttonR) display.print("X "); else display.print("O ");
  display.println("");

  display.print("LX: "); if(lx<10) display.print(" "); if(lx<100) display.print(" "); display.print(lx); display.print("     ");
  display.print("RX: "); if(rx<10) display.print(" "); if(rx<100) display.print(" "); display.print(rx); display.println("");
  display.print("LY: "); if(ly<10) display.print(" "); if(ly<100) display.print(" "); display.print(ly); display.print("     ");
  display.print("RY: "); if(ry<10) display.print(" "); if(ry<100) display.print(" "); display.print(ry); display.println("");

  display.print("Batt "); display.print(constrain(remoteBatt, 0, 99)); //display.print("% ");
  //display.print("RBatt "); display.print(constrain(robotBatt, 0, 99)); 
  display.println("%");

  display.print("Mode: ");
  if(mode == 0) display.println("Stand");
  else if(mode == 1) display.println("Demo");
  else if(mode == 2) display.println("Static Walk");

  display.display();
}
