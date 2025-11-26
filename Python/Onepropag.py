import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.patches as mpatches

# Função para ler dados de um arquivo e retorná-los como colunas
def read_data(filename):
    data = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip().split()
            if len(line) == 3:
                data.append([float(x) for x in line])
    x_values = [row[0] for row in data]
    y_values = [row[1] for row in data]
    z_values = [row[2] for row in data]
    return x_values, y_values, z_values

# Especificar o raio e a espessura do cilindro
radius_cylinder = 20  # Raio em kpc
thickness_cylinder = 0.1  # Espessura em kpc
height_cylinder = 0.1  # Altura em kpc

# Gerar dados para o cilindro
z_cylinder = np.linspace(-height_cylinder/2, height_cylinder/2, 100)
theta_cylinder = np.linspace(0, 2*np.pi, 100)
z_cylinder, theta_cylinder = np.meshgrid(z_cylinder, theta_cylinder)
x_cylinder = (radius_cylinder + thickness_cylinder/2) * np.cos(theta_cylinder)
y_cylinder = (radius_cylinder + thickness_cylinder/2) * np.sin(theta_cylinder)

# Especificar o raio da esfera
radius_sphere = 20  # Raio em kpc

# Gerar dados para a esfera
u_sphere = np.linspace(0, 2 * np.pi, 100)
v_sphere = np.linspace(0, np.pi, 100)
x_sphere = radius_sphere * np.outer(np.cos(u_sphere), np.sin(v_sphere))
y_sphere = radius_sphere * np.outer(np.sin(u_sphere), np.sin(v_sphere))
z_sphere = radius_sphere * np.outer(np.ones(np.size(u_sphere)), np.cos(v_sphere))

# Leitura do arquivo de dados para uma única partícula
#file = r'../Simulacoes_Resultados/Energia_1_0E17/Helio/Pos_ASS_Sim01_E1_0E17_P2.dat'
file = r'../Pos.dat'
x_values, y_values, z_values = read_data(file)

# Criar a figura com dois subplots 3D lado a lado
fig = plt.figure(figsize=(12, 6))

# Subplot 1: Cilindro + Esfera
ax1 = fig.add_subplot(121, projection='3d')
ax1.set_title('Galatic Halo BSS propagation (Iron - Energy:10^18eV)')

# Plotar o cilindro
ax1.plot_surface(x_cylinder, y_cylinder, z_cylinder, color='lightblue', alpha=0.8)

# Plotar a esfera
ax1.plot_surface(x_sphere, y_sphere, z_sphere, color='lightblue', alpha=0.1)

# Adicionar pontos para o cilindro
ax1.scatter([0], [0], [0], color='black', s=30, label='Galactic Center')
ax1.scatter([-8.5], [0], [0], color='red', s=30, label='Earth')

# Adicionar a partícula no gráfico 1
ax1.scatter(x_values, y_values, z_values, color='blue', s=0.5, label='Particle 1')

# Subplot 2: Trajetória da partícula
ax2 = fig.add_subplot(122, projection='3d')
ax2.set_title('Propagation BSS (Iron - Energy:10^18eV)')

# Plotar os dados da partícula
ax2.scatter(x_values, y_values, z_values, color='blue', s=0.5, label='Particle 1')

# Adicionar marcadores para o Centro Galáctico e a Terra
ax2.scatter([0], [0], [0], color='black', s=30, label='Galactic Center')
ax2.scatter([-8.5], [0], [0], color='red', s=30, label='Earth')

# Definir rótulos dos eixos para ambos os gráficos
for ax in [ax1, ax2]:
    ax.set_xlabel('X (kpc)')
    ax.set_ylabel('Y (kpc)')
    ax.set_zlabel('Z (kpc)')

# Criar uma legenda lateral com descrição para a partícula e pontos
plt.legend(handles=[
    mpatches.Patch(color='blue', label='Particle 1'),
    mpatches.Patch(color='black', label='Galactic Center (black)'),
    mpatches.Patch(color='red', label='Earth (red)')
], bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)

# Salvar o gráfico
output_path = 'Iron_propag_BSS_10^18_single_particle.png'
plt.savefig(output_path, bbox_inches='tight')

print(f"Gráfico salvo como {output_path}")
print("Gráfico gerado e salvo com sucesso!")

# Exibir o gráfico
plt.tight_layout()
plt.show()
