import pandas as pd
import serial
import time
t=int(input())
t=1
file_path = 'User/tablefile.csv'
ser = serial.Serial('COMX0', 9600)
response = ser.readline()
ser = serial.Serial(serial_port, baud_rate)
time.sleep(2)  # Ждем, пока откроется соединение
df = pd.read_csv(file_path)
while t=1:
   found = False
   for row_index in range(df.shape[0]):  # Проход через строки
   	if df.iat[row_index, col_index] == response:
	   if localtime([row_index, col_index + 1]) > time.localtime:
	      ser.write(2) 
           else:
	      ser.write(response)  # Отправка сообщения через сериал-порт
       	found = True
        break
   if found:
   	break
   if not found:
       ser.write(1)  # Отправка сообщения "0" через сериал-порт