# Hardware and pinout

Target board: **LilyGO T-Display-S3** with the integrated 320 × 170 display.

| Function | GPIO / setting |
|---|---:|
| Backlight PWM | GPIO38 |
| Button 1 / next page | GPIO0, active low, internal pull-up |
| Button 2 / auto rotation | GPIO14, active low, internal pull-up |
| Octal SPI clock | GPIO8 |
| Octal SPI data | GPIO39, GPIO40, GPIO41, GPIO42, GPIO45, GPIO46, GPIO47, GPIO48 |
| Display model | `t-display-s3` |
| Display rotation | 270° |
| PSRAM | Octal, 80 MHz |
| Flash | 16 MB |

## Button controls

| Input | Action |
|---|---|
| Button 1 short | Next page |
| Button 1 long | Previous page |
| Button 2 short | Toggle auto rotation |
| Button 2 long | Acknowledge the automatic alarm page |

A button press temporarily wakes the display at daytime brightness when night mode is active.
