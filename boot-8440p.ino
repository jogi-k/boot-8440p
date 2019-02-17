/* Update BIOS of BT-05 automatically with a Teensy-Stick, programmed with Teensy-Duino */

#define DEFAULT_DELAY 200 // 200 ms between keypresses

/* do it only once */
int done = 0;

void setup()
{
  Keyboard.begin();
}

/* Compatibility to plain C-Teensy programming , Start */

#define KEY_SHIFT  KEY_LEFT_SHIFT

void usb_keyboard_press( int character, int special )
{
   if (special != 0 )
   {
      Keyboard.press( special);
      delay( 10 );
   }
   Keyboard.press( character );
   delay( 50 );
   Keyboard.releaseAll();
}

void _delay_ms( int wait )
{
   delay( wait );
}

/* Compatibility to plain C-Teensy programming , End */


void usb_keyboard_press_and_delay( int character, int special )
{
    usb_keyboard_press( character, special );
    _delay_ms( DEFAULT_DELAY );
}

void loop()
{
    int i;
    if ( ! done )
    {
        // START copy between teensy and sketchbook

        // Enter BIOS via pressing 10 times DELETE
            for ( i = 0; i < 20; ++i )
        {
            usb_keyboard_press( KEY_ESC, 0 );
            _delay_ms(500);
        }

        // Go right into the menu
        usb_keyboard_press_and_delay( KEY_F9 , 0  );
        // Go down to USB-Boot
        for ( i = 0; i < 2; ++i )
        {
            usb_keyboard_press_and_delay( KEY_DOWN, 0 );
        }
        // and enable USB-Boot
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );
        done = 1;
    }
    delay(1000);
}

