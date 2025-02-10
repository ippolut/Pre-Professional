import pandas as pd
import serial
import time
t=int(input())
t=1
file_path = 'your_file.csv'
ser = serial.Serial('COMX', 9600)
response = ser.readline()
ser = serial.Serial(serial_port, baud_rate)
time.sleep(2)  # Ждем, пока откроется соединение
df = pd.read_csv(file_path)
while t=1:
   found = False
   for row_index in range(df.shape[0]):  # Проход через строки
      for col_index in range(df.shape[1]):  # Проход через столбцы
           if df.iat[row_index, col_index] == response:
               print(f'Найдена ячейка с "Дата" на строке {row_index + 1}, колонке {col_index + 1}.')
               ser.write(f'response)  # Отправка сообщения через сериал-порт
               found = True
               break
       if found:
           break

   if not found:
       ser.write(f'0)  # Отправка сообщения "0" через сериал-порт