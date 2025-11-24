import serial
import time

PORT = "COM4"
BAUD = 115200

logfile = "greenhouse.csv"

ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)

print(f"Logging to {logfile} ... ctrl+C to stop.")

with open(logfile, "a", encoding="utf-8") as f:
    while True:
        line = ser.readline().decode(errors="ignore").strip()
        if line:
            print(line)
            f.write(line + "\n")
            f.flush()
