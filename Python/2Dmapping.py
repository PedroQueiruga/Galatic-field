import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Leitura dos dados dos arquivos
data = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\mappingASSxy.dat')
data2 = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\mappingBSSxy.dat')

# Separação dos dados em colunas
x = data[:, 0]
y = data[:, 1]
z = data[:, 2] * 1e10# Intensidade magnética para BSS
x2 = data2[:, 0]
y2 = data2[:, 1]
z2 = data2[:, 2] * 1e10  # Intensidade magnética para ASS

# Cria a figura com dois subgráficos
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 8))

# Gráfico para o modelo BSS
contour1 = ax1.tricontourf(x, y, z, levels=40, cmap='viridis')
ax1.set_xlabel('X (Kpc)', labelpad=10)
ax1.set_ylabel('Y (Kpc)', labelpad=10)
ax1.set_title('ASS Model', pad=20)

# Adiciona a barra de cores para o modelo BSS
cbar1 = fig.colorbar(contour1, ax=ax1)
cbar1.set_label('Magnetic Intensity (µG)')

# Gráfico para o modelo ASS
contour2 = ax2.tricontourf(x2, y2, z2, levels=40, cmap='viridis')
ax2.set_xlabel('X (Kpc)', labelpad=10)
ax2.set_ylabel('Y (Kpc)', labelpad=10)
ax2.set_title('BSS Model', pad=20)

# Adiciona a barra de cores para o modelo ASS
cbar2 = fig.colorbar(contour2, ax=ax2)
cbar2.set_label('Magnetic Intensity (µG)')

# Ajusta o layout para evitar sobreposição de elementos
plt.tight_layout()

# Mostra os gráficos no mesmo frame
plt.show()
