# Knob and LED

This sketch uses a knob and pixel modulino. It acts as a "volume" style.

One cool feature is the `Serial` functionality. You can open a serial port to dump data into.

```cpp
Serial.begin(9600);
```

Then print with some functions

```cpp
Serial.print("Some logs");
Serial.println("Some More logs!!!");
```

On my linux machine, I can view the logs with this command. `/dev/ttyACM0` is different on my Macbook.
```bash
screen /dev/ttyACM0 960
```

