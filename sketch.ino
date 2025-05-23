#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Keypad.h>
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
const byte ROW_NUM    = 4;  
const byte COLUMN_NUM = 4;  
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pin_rows[ROW_NUM] = {5, 4, 3, 2};
byte pin_column[COLUMN_NUM] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
int runs = 0;
int overs = 0;
int balls = 0;
int wickets = 0;
String matchStatus = "Not Started";
void updateDisplay() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Cricket Scoreboard");
  tft.setCursor(10, 40);
  tft.setTextSize(2);
  tft.print("Runs: ");
  tft.print(runs);
  tft.print(" - ");
  tft.print(wickets);
  tft.setCursor(10, 70);
  tft.setTextSize(2);
  tft.print("Overs: ");
  tft.print(overs);
  tft.setCursor(10, 100);
  tft.setTextSize(2);
  tft.print("Balls: ");
  tft.print(balls);
  tft.setCursor(10, 130);
  tft.setTextSize(2);
  tft.print("Status: ");
  tft.print(matchStatus);
}
void handleKeypadInput() {
  char key = keypad.getKey();
  if (key) {
    if (key == 'A') {  
      balls = 0;
      wickets = 0;
      runs = 0;
      overs = 0;
      matchStatus = "Not Started";
      updateDisplay();
    }
    else if (key == 'D') {    
      matchStatus = "In Progress";
      
      balls += 1;
      if (balls == 6) {
        overs += 1;
        balls = 0;  
      }
      wickets +=1;
      if (wickets >= 11) {
        matchStatus = "Match Ended";
        wickets = 11;
        
      }
      updateDisplay(); 
    }
    else if (key == 'B') {    
      matchStatus = "match stopped due to rain";
      updateDisplay();
    } 
    else if (key == 'C') {    
      matchStatus = "Match Ended";
      updateDisplay();
    } 
    else if (key >= '0' && key <= '6') {  
      matchStatus = "In Progress"; 
      int addedRuns = key - '0';  
      runs += addedRuns;
      balls += 1;
      if (balls == 6) {
        overs += 1;
        balls = 0;  
      }
      if (overs >= 20) {
        matchStatus = "Match Ended";
      }
      
      updateDisplay();
    }
  }
}
void setup() { 
  tft.begin();
  tft.setRotation(3);  
  tft.fillScreen(ILI9341_BLACK); 
  updateDisplay();
}
void loop() {  
  handleKeypadInput();
}

