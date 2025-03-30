# Smart-Bin-Simulation-Using-Wokwi-ThingSpeak  

## Objective  
This project simulates a Smart Bin that automatically opens, detects waste levels, and sends real-time data to ThingSpeak. 

## Components Used  

- **PIR Sensor** – Detects human presence near the bin  
- **Ultrasonic Sensor** – Measures waste level inside the bin  
- **Servo Motor** – Opens and closes the bin lid  
- **LED Indicators** – Show waste level status  
- **Microcontroller** – Simulated in Wokwi  
- **ThingSpeak** – Logs waste level and displays a live chart  

## Working   

1. When a person approaches, the **PIR sensor** detects motion, and the **servo motor** opens the bin lid.  
2. The **ultrasonic sensor**, placed inside the lid, continuously measures the waste level.  
3. Based on the detected waste level, different **LEDs** indicate the bin status:  
   - When the waste level **reaches 30%**, the **green LED** turns on.  
   - At **50%**, the **yellow LED** also turns on.  
   - When it reaches **85%**, the **orange LED** turns on.  
   - If the bin is **90% full or more**, the **red LED** turns on, and the lid remains closed.  
5. The waste level is **sent to ThingSpeak**, where a live chart visualizes the data.  

## Project Links

Wokwi: <u>[Click here](https://wokwi.com/projects/422468464408486913)</u>  
ThingSpeak:
1. Go to [ThingSpeak](https://thingspeak.com/).  
2. Click on **"Channels"** in the navigation bar.  
3. In the search bar, enter the tag **"SMART BIN"** and click **Submit**.  
4. Find the channel with **Channel ID: `2834140`** and select it.  
5. You can now view the Smart Bin data.

