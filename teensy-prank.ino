// tested on teensy 3.1, but will probably work with others as well

// delay beetween the keys
int ds = 20;

// used to signify when LED is pressed
#define LED_PIN 13

void setup()
{
  // give us a little time to connect up
  delay(1000);

  // allow controlling LED
  pinMode(LED_PIN, OUTPUT);

  // turn the LED on while we're pwning
  digitalWrite(LED_PIN, HIGH);


  // now open Terminal
  openapp("Terminal");

  // wait for terminal to start
  delay(500);

  // open new terminal window (if user has Terminal open already, we don't want to destroy it)
  cmd(KEY_N);

  // download beautiful image of pink pony
  // and set it as wallpaper
  setWallpaper();

  // wait for download to complete...
  delay(2000);

  // quit the terminal
  cmd(KEY_Q);
  delay(200);
  k(KEY_ESC);

  // we're done!
}


// type a string (pressing enter at the end)
// we have extra delays so we can see what's happening
void typeln(String chars)
{
  Keyboard.print(chars);
  delay(ds);
  Keyboard.println("");
  delay(ds * 4);
}

// open an application on OS X via spotlight/alfred
void openapp(String app)
{
  // open spotlight (or alfred/qs), then the app
  cmd(KEY_SPACE);
  typeln(app);
}

void setWallpaper() {
   typeln("curl -s -o $HOME/.ponies.jpg http://i.imgur.com/ZHNScON.png?1 && osascript -e \"tell application \\\"Finder\\\" to set desktop picture to POSIX file \\\"$HOME/.ponies.jpg\\\"\" && exit");
}

void k(int key)
{
  Keyboard.set_key1(key);
  Keyboard.send_now();
  delay(100);

  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(100);
}


void mod(int mod, int key)
{
  Keyboard.set_modifier(mod);
  Keyboard.send_now();
  Keyboard.set_key1(key);
  Keyboard.send_now();
  delay(200);

  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(200);
}

void ctrl(int key)
{
  mod(MODIFIERKEY_CTRL, key);
}

void cmd(int key)
{
  mod(MODIFIERKEY_GUI, key);
}

void shift(int key)
{
  mod(MODIFIERKEY_SHIFT, key);
}

void loop()
{
  // blink quickly so we know we're done
  digitalWrite(LED_PIN, HIGH);
  delay(400);
  digitalWrite(LED_PIN, LOW);
  delay(400);
}

