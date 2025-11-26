import numpy as np
import matplotlib.pyplot as plt

# Leitura dos dados dos arquivos
data = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\magneticvectorASSxy.dat')
data2 = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\magneticvectorBSSxy.dat')

# Separação das colunas para o primeiro conjunto de dados (ASS)
x = data[:, 0]  # Primeira coluna: posição x
y = data[:, 1]  # Segunda coluna: posição y
Bx = data[:, 2] * 1e10  # Convertendo de Tesla para Microgauss
By = data[:, 3] * 1e10

# Separação das colunas para o segundo conjunto de dados (BSS)
x2 = data2[:, 0]  # Primeira coluna: posição x
y2 = data2[:, 1]  # Segunda coluna: posição y
Bx2 = data2[:, 2] * 1e10  # Convertendo de Tesla para Microgauss
By2 = data2[:, 3] * 1e10

# Criando duas subplots (um ao lado do outro)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))


# Primeiro gráfico (ASS)
ax1.quiver(x, y, Bx, By, color='black', alpha=0.6, scale=1e2)
ax1.scatter([-8.5], [0], color='Blue', s=40, label='Earth')
ax1.set_title('ASS Model')
ax1.set_xlabel('X (kpc)')
ax1.set_ylabel('Y (kpc)')
ax1.grid()

# Segundo gráfico (BSS)
ax2.quiver(x2, y2, Bx2, By2, color='black', alpha=0.6, scale=1e2)
ax2.scatter([-8.5], [0], color='Blue', s=40, label='Earth')
ax2.set_title('BSS Model')
ax2.set_xlabel('X (kpc)')
ax2.grid()

# Ajuste de layout e exibição
fig.set_facecolor('white')
plt.tight_layout()
plt.show()


