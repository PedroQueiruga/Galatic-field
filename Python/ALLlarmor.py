import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Caminho base para os arquivos
base_path = r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\ASSLP14'

# Configurar o gráfico
plt.figure(figsize=(10, 6))

# Iterar sobre os 10 arquivos numerados
for i in range(1, 11):
    file_path = f'{base_path}{i}.dat'
    
    # Ler o arquivo de dados
    data = pd.read_csv(file_path, header=None, delim_whitespace=True)  # Assume separação por espaços
    
    # Extrair as colunas
    x = data[0]  # Tempo
    y = data[1]  # Raio de Larmor
    
    # Plotar os dados de cada arquivo
    plt.scatter(x, y, marker='o', s=1, label=f'Partícula {i}')

# Personalizar o gráfico
plt.xlabel('T (s)')  # Rótulo do eixo X
plt.ylabel('Raio de Larmor (kpc)')  # Rótulo do eixo Y
plt.title('Larmor Radius Proton (Energy - 10^14 eV)')
plt.grid(True)
plt.legend(loc='upper right', fontsize='small')
plt.tight_layout()

# Exibir o gráfico
plt.show()
