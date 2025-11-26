import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Leitura dos dados do arquivo
data = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\mapping.dat')

# Separação dos dados em colunas
x = data[:, 0]
y = data[:, 1]
z = data[:, 2] * 1e10  # Intensidade magnética para ASS

# Criação da figura
fig, ax = plt.subplots(figsize=(7, 8))

# Gráfico para o modelo ASS
contour = ax.tricontourf(x, y, z, levels=40, cmap='viridis')
ax.set_xlabel('X (Kpc)', labelpad=10)
ax.set_ylabel('Y (Kpc)', labelpad=10)
ax.set_title('ASS Model', pad=20)

# Adiciona a barra de cores para o modelo ASS
cbar = fig.colorbar(contour, ax=ax)
cbar.set_label('Magnetic Intensity (µG)')

# Ajusta o layout para evitar sobreposição de elementos
plt.tight_layout()

# Mostra o gráfico
plt.show()
