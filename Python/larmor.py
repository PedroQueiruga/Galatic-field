import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#Read the data from the file
file_path = r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\larmor_ASS_Sim01_E1_0E16_P1.dat'
data=pd.read_csv(file_path, header=None, delim_whitespace=True) #Assuming whitespace delimeter

#Extract the first two columns:
x = data[0] #Tempo
y = data[1] #Raio de larmor

#Aplicando o logaritmo natural:

x_ln = np.log(x)
y_ln = np.log(y)

#Plot the data

plt.figure (figsize=(10,6))
plt.scatter(x_ln, y_ln, marker='o', s=1)
plt.xlabel('T (s)')  # X-axis Label
plt.ylabel('Gamma')  # Y-axis Label
plt.title('2D Particle Propagation')
plt.grid(True)
plt.show()