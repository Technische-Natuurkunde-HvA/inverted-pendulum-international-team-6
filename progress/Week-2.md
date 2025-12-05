# Week 2

## 1. Progress description
Pendulum is built and complete, sensor is working, but the pendulum does not swing around. 
This is because the engine doesn't have enough power to create enough momentum to flip over the pendulum itself.

Our sollution is to create a bigger wheel for the pendulum and we are getting a new engine for the pendulum which should produce more power.

## 2. Code

You can display code using three backticks (```) followed by an optional language extension.  
For example:  
- For C/C++ code, use `c` or `cpp`.  
- For Python, use `python`.


#### Example:
this is the code to getting the sensor to record the angle, to use this you must close the serial monitor before running or else it will give an access denied error.
```python
import serial
import time
import csv
import matplotlib.pyplot as plt

# ---------- SETTINGS ----------
PORT = "COM3"       # change to your Arduino port (COM4, COM5, ...)
BAUD = 11500         # MUST match Serial.begin() on Arduino
DURATION = 10       # seconds to record (2–10 sec is fine)
CSV_FILE = "as5600_data.csv"
PLOT_FILE = "as5600_plot.png"
# ------------------------------

def record_data():
    print(f"Opening {PORT} at {BAUD} baud...")
    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)  # Arduino reset time

    start_time = time.time()
    print(f"Recording for {DURATION} seconds...")

    with open(CSV_FILE, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["time_s", "angle_deg"])

        while time.time() - start_time < DURATION:
            line = ser.readline().decode("utf-8").strip()
            if not line:
                continue

            try:
                angle = float(line)   # one angle per line from Arduino
                t = time.time() - start_time
                writer.writerow([t, angle])
                print(t, angle)
            except ValueError:
                pass  # skip garbage lines

    ser.close()
    print("Done. Data saved to", CSV_FILE)


def plot_data():
    times = []
    angles = []

    with open(CSV_FILE, "r") as f:
        reader = csv.reader(f)
        next(reader)  # skip header
        for row in reader:
            times.append(float(row[0]))
            angles.append(float(row[1]))

    plt.figure(figsize=(8, 4))
    plt.plot(times, angles)
    plt.xlabel("Time (s)")
    plt.ylabel("Angle (deg)")
    plt.title("AS5600 angle vs time")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(PLOT_FILE)
    print("Plot saved as", PLOT_FILE)
    plt.show()


if __name__ == "__main__":
    record_data()
    plot_data()

``` 
## 3. Results

<img width="447" height="762" alt="image" src="https://github.com/user-attachments/assets/370c9f93-5560-44dd-8470-b69ee6fb8e8e" />
<img src="https://github.com/user-attachments/assets/f749436e-5a09-499d-a982-40eb85d81b4f" />
<img src="https://github.com/user-attachments/assets/29bbc4b2-6fbc-414d-821a-010b1057b986" />



## 4. Reflection 

We learned how to use the pendulum and how to use the code to start the motor.
