/********************** ETUDE 3 CART 360 2019 *******************************
   WELCOME!
   THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
   WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS).
   THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
   THERE ARE 5 POSSIBLE MODES
   0 ==  reset    ==   led off == also resets
   1 ==  live     ==   led BLUE
   2 ==  record   ==   led RED
   3 ==  play     ==   led GREEN
   4 ==  loopMODE ==   led PURPLE

   ADDITIONALLY - WHEN THE USER CHANGES MODE,
   THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

   PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
   DO NOT ADD ANY MORE FUNCTION DEFINITIONS
   ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
   THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
   PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
   GOOD LUCK!
*/
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES];
int mode = 0; // start at off
// check at which state the mode button is
int buttonState = 0;
// check the previous state of the mode button
int buttonStatePrev = 0;
/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_MODE_PIN, INPUT);

// declaring the buzzer and the notes button
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(NOTE_IN_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change the loop - it establishes the flow of the program
   We call here 3 functions repeatedly:
   1: chooseMode(): this function will determine the mode that your program is in
   based on if the button (linked to the BUTTON_MODE_PIN) was pressed
   2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
   3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Read the value from the Button (linked to the BUTTON_MODE_PIN) and
   if is being pressed then change the mode variable.
   REMEMBER:
   mode == 0 is reset
   mode == 1 is live
   mode == 2 is record
   mode == 3 is play
   mode == 4 is loopMode
   Every time the user presses the button, the program will go to the next mode,
   once it reaches 4, it should go back to mode == 0.
   (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode() {

// checking at which state the mode button is 
  buttonState = digitalRead(BUTTON_MODE_PIN);

// checking the button state 
  if (buttonState != buttonStatePrev) {
// if the button was pressed
    if (buttonState == HIGH) {
// changing the mode and make it goes back to the first one
    mode = (mode + 1) % 3;
    }
    buttonStatePrev = buttonState;

  }

}

/******************SETRGB(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Depending on the value of the mode variable:
   if the mode is 0 - RGB LED IS OFF
   if the mode is 1 - RGB LED IS BLUE
   if mode is 2 - RGB LED IS RED
   if mode is 3 - RGB LED IS GREEN
   if mode is 4 - RGB LED iS PURPLE
   YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{

// no light when it resets
  if (mode == 0) {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, LOW);
  }
  
// make the light be blue for the first mode
  else if (mode == 1) {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, HIGH);
  }
// make the light be red for the second mode
  else if (mode == 2) {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, LOW);
  }

// make the light be green for the third mode
  else if (mode == 3) {
    digitalWrite(LED_PIN_R, LOW);
    digitalWrite(LED_PIN_G, HIGH);
    digitalWrite(LED_PIN_B, LOW);
  }

// make the light be puruple for the fourth mode
  else if (mode == 4) {
    digitalWrite(LED_PIN_R, HIGH);
    digitalWrite(LED_PIN_G, LOW);
    digitalWrite(LED_PIN_B, HIGH);
  }
  
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
   There are 4 possibilities
   1: reset(): this function will reset any arrays etc, and will do nothing else
   2: live(): this function will play the corresponding notes
   to the user pressing the respective buttons.
   NOTE:: the notes played are NOT stored
   3: record(): this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   4: play(): this function will playback any notes stored in the array that were recorded
   in the previous mode
   5: loopMode(): this function will playback any notes stored in the array that were recorded,
   BUT unlike the previous mode, you can choose in which sequence the notes are played.
   REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if (mode == 0) {
    reset();
  }
  else if (mode == 1) {
    live();
  }
  else if (mode == 2) {
    record();
  }

  else if (mode == 3) {
    play();
  }

  else if (mode == 4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
// reseting the countNotes
  countNotes = 0;

}
/******************LIVE(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   NOTE:: the notes played are NOT stored
   SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
   THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
// instead of changing the resistors, I put a variable of frequency for each button
// if the first note button is pressed
  if (analogRead(NOTE_IN_PIN) >= 2 && analogRead(NOTE_IN_PIN) <= 6) {
    tone(BUZZER_PIN, 250, duration);
  }

// if the second note button is pressed
  if (analogRead(NOTE_IN_PIN) >= 7 && analogRead(NOTE_IN_PIN) <= 81) {
    tone(BUZZER_PIN, 1500, duration);
  }

// if the third note button is pressed
  if (analogRead(NOTE_IN_PIN) >= 82 && analogRead(NOTE_IN_PIN) <= 509) {
    tone(BUZZER_PIN, 500, duration);
  }

// if the fourth note button is pressed
  if (analogRead(NOTE_IN_PIN) >= 510 && analogRead(NOTE_IN_PIN) <= 1028) {
    tone(BUZZER_PIN, 1000, duration);
  }

// if the fifth note button is pressed
  if (analogRead(NOTE_IN_PIN) == 1020) {
    tone(BUZZER_PIN, 2000, duration);
  }

}


/******************RECORD(): IMPLEMENT **********************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
   AND - output the note to the buzzer using the tone() function
   THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{

// checking which button was pressed to match it with the right frequency otherwise 
// it was only playing the frequency of the last button pressed

  int valueNote = analogRead(NOTE_IN_PIN);

// what button was pressed to check which frequency to play
  if (valueNote > 0 && countNotes < MAX_NOTES) {

// if the first button was pressed
    if (valueNote >= 2 && valueNote <= 6) {
      notes[countNotes] = 250;
      tone(BUZZER_PIN, 250, duration);
      countNotes++;
    }

// if the second button was pressed
    else if (valueNote >= 7 && valueNote <= 81) {
      notes[countNotes] = 1500;
      tone(BUZZER_PIN, 1500, duration);
      countNotes++;
    }

// if the third button was pressed
    else if (valueNote >= 82 && valueNote <= 509) {
      notes[countNotes] = 500;
      tone(BUZZER_PIN, 500, duration);
      countNotes++;
    }

// if the fourth button was pressed
    else if (valueNote >= 510 && valueNote <= 1028) {
      notes[countNotes] = 1000;
      tone(BUZZER_PIN, 1000, duration);
      countNotes++;
    }


// if the fifth button was pressed
    else {
      notes[countNotes] = 2000;
      tone(BUZZER_PIN, 2000, duration);
      countNotes++;
    }

  }

// delaying each press otherwise the MAX_NOTES was reach to quickly
  delay(duration * 2);

}
/******************PLAY(): IMPLEMENT ************************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ each value IN ORDER
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{

// asking to the buzzer to play what was put in the array
  Serial.println(countNotes);
  for (int i = 0; i < countNotes; i++) {
    tone(BUZZER_PIN, notes[i], duration);
    Serial.println(notes[i]);
    delay(duration * 4);

// if the mode button is press, we need to stop the play mode
    if (digitalRead(BUTTON_MODE_PIN) == HIGH) {
      break;
    }
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode()
{

// looping the array in a random way 
  for (int i = 0; i < countNotes; i++) {
    
// initiating the variable to make the notes play in a random order
// making sure it goes throught all the array 
    int r = random(0, countNotes + i);
    tone(BUZZER_PIN, notes[r], duration);
    delay(duration);
    
// if the mode button is press, we need to stop the play mode
    if (digitalRead(BUTTON_MODE_PIN == HIGH)) {
      break;
    }
  }
}

/****************** Behavior of the resistor ladder *********************************
  The Arduino is going to give to our breadboard 5V, so in this case, we are going to have
  5V going throught our circuit. By pressing the mode button, there is nothing that going to
  affec the noise going out of the buzzer. When we press on one of the note buttons, the current
  is going to go throught the button and the resistors that follows after. Because of that, the
  level of voltage is going to be lower if we press the first button and vise versa. Resistors 
  produce noise and this noise is produce by the movements of electrons. In this state of mind,
  if the current goes throught many resistors before getting to the buzzer, the sound at the end 
  of the line is going to be as strong as the one that goes throught only one. Now that we have
  different resistors in our circuit, the sound is also going to be affected.
**************************************************************************/
