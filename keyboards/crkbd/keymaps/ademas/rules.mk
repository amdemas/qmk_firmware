EXTRAFLAGS += -flto -DNO_DEBUG -DNO_PRINT

BOOTMAGIC_ENABLE           = lite  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE            = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE            = yes # Audio control and System control(+450)
CONSOLE_ENABLE             = no  # Console for debug(+400)
COMMAND_ENABLE             = no  # Commands for debug and configuration
NKRO_ENABLE                = yes  # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE                = no  # MIDI controls
AUDIO_ENABLE               = yes  # Audio output on port C6
UNICODE_ENABLE             = no  # Unicode
BLUETOOTH_ENABLE           = no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE            = no  # Enable WS2812 RGB underlight.
# SWAP_HANDS_ENABLE          = no  # Enable one-hand typing
RGB_MATRIX_ENABLE = WS2812

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

BOOTLOADER = qmk-dfu

HAPTIC_ENABLE = no

OLED_DRIVER_ENABLE = yes

# API_SYSEX_ENABLE = no
# VIRTSER_ENABLE     = no
# AUTO_SHIFT_ENABLE  = no
LINK_TIME_OPTIMIZATION_ENABLE = yes
