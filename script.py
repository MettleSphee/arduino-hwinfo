import serial
import time
import psutil
import math

#Define your settings here
arduinoSerial = '/dev/ttyACM0'
baudRate = 9600
timeoutBetweenCommands = 0.25
byteSize = 8
stopbitsCount = 1

arduino = serial.Serial(arduinoSerial, baudRate, bytesize=byteSize, timeout=timeoutBetweenCommands, stopbits=stopbitsCount)

def messageFunction(message):
	arduino.write((message+"\n").encode())
	response = arduino.read(200).decode()
	print(response,"\n")

def Init():
	print("Waiting for device to initialize...")
	time.sleep(2)
	Checkstring = "Diagnostic Tool ready to receive data! Confirmation: e326a5"
	a = arduino.readline()
	b = arduino.readline()

	if (Checkstring in a.decode() or Checkstring in b.decode()):
		print("Device initialized and running.")
	else:
		print("Device not ready. Please re-run the script.")
		exit()

def cpu():
	cpuFreq = str(int(psutil.cpu_freq().current)//100/10)
	cpuTemp = psutil.sensors_temperatures()
	if (cpuTemp == {}):
		cpuTemp = "None"
	output = "Freq: CPU Temps:"+str(cpuFreq)+"G  CPU   "+cpuTemp
	messageFunction(output)
	time.sleep(2)

def battery():
	battery = psutil.sensors_battery()
	if (battery == None):
		output = "No battery  AC  "+"detected    only"
	else:
		batteryPercentage = str(battery.percent)
		charging = "Charging" if battery.power_plugged else "Draining"
		output = "Battery   Status"+f"{batteryPercentage :03d}"+"%    "+charging
	messageFunction(output)
	time.sleep(2)


def Loop():
	while(1):
		cpu()
		battery()
		



Init()
Loop()

arduino.close()
