Mixing up units of measurement (milliseconds vs microseconds), or different quantities to begin with (e.g., time vs temperature vs voltage), can lead to very frustrating and hard-to-find bugs. This library aims to make your life as a programmer a little bit safer, by making it much harder to make such mistakes. It represents physical quantities as strongly-typed, salf-aware wrappers.

The library is meant for physical quantities that are measured by your micro-controller, such as: temperature, elapsed time, voltage, current, capacitance, velocity, work, pressure, etc. Internally, it represents a measured quantity as a float, using a default unit of measure (generally, base SI unit). It provides functions to convert between various units of measure easily, and to print out quantities in a human-friendly format, with the automatically chosen unit of measure. For example:

```cpp
  // Random temperature between -15.0C and +35.0C.
  Temperature temp = TemperatureDegCelcius(rand() % 500 / 10.0 - 15.0f);
  Serial.printf("Temperature: %s\n", temp.asArduinoString().c_str());
  Serial.println("In Celsius: " + String(temp.degCelcius()));
  Serial.println("In Kelvin: " + String(temp.degKelvin()));
  Serial.println("In Fahrenheit: " + String(temp.degFahrenheit()));
```

Output:
```
Temperature: 20.1°C
In Celsius: 20.10
In Kelvin: 293.25
In Fahrenheit: 68.18
```

You can perform basic transformations directly on the quantities, treating them as numbers, as long as it makes physical sense. Let's look at an example that uses the Ohm's law, and formula for electric power:

```cpp
  // Random voltage between 0 and 5V.
  Voltage u = VoltageInVolts(rand() % 500 / 100.0f);
  Serial.println("Voltage: " + u.asArduinoString());

  // Random current between 0 and 50 mA.
  Current i = CurrentInMilliAmperes(rand() % 50);
  Serial.println("Current: " + i.asArduinoString());
  Serial.println("Power: " + (u * i).asArduinoString());
  Serial.println("Resistance: " + (u / i).asArduinoString());

  // What if the current was 500 times lower?
  i /= 500;
  Serial.println("New current: " + i.asArduinoString());
  Serial.println("New power: " + (u * i).asArduinoString());
  Serial.println("New resistance: " + (u / i).asArduinoString());

  // Random capacitance between 0 and 4.7µF.
  Capacitance c = CapacitanceInNanoFarads(rand() % 4700);
  Serial.println("Capacitance " + c.asArduinoString());
  Serial.printf("Charge at %s: %s %s\n", u.asString().c_str(),
                (c * u).asString().c_str());
```

Output:
```
Voltage: 3.43 V
Current: 5 mA
Power: 17.15 mW
Resistance: 686 Ω
New current: 10 µA
New power: 34.3 µW
New resistance: 343 kΩ
Capacitance: 4.18 µF
Charge at voltage 3.43 V: 14.3374 µC
```

Note how the library selects human-friendly units when pretty-printing the output.

## Runtime overhead

Everything is inlined: the generated code will look as if you simply used float variables. Pretty-printing will have some small overhead, but only if you actually use it.

In particular, quantity classes are _not_ virtual. (If they were, we could avoid needing to explicitly call ```asArduinoString()``` when writing to Serial, but at a cost of adding vtable pointer to each quantity representation.)