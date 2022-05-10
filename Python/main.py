from serial import Serial

gps = Serial("COM14",baudrate=9600)

while True:
    line  = str(gps.readline())
    if "$GPGGA" in line:
        data = line.split(",")
        latitud = data[2].strip()
        longitud = data[4].strip()
        satelites = data[7].strip()
        print(f"Latitud: {latitud} Longitud: {longitud} # de satelites: {satelites}")