import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import winsound # Para aviso sonoro ao finalizar
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
radius_cylinder = 20 # Raio em kpc
thickness_cylinder = 0.1 # Espessura em kpc
height_cylinder = 0.1 # Altura em kpc

# Gerar dados para o cilindro
z_cylinder = np.linspace(-height_cylinder/2, height_cylinder/2, 100)
theta_cylinder = np.linspace(0, 2*np.pi, 100)
z_cylinder, theta_cylinder = np.meshgrid(z_cylinder, theta_cylinder)
x_cylinder = (radius_cylinder + thickness_cylinder/2) * np.cos(theta_cylinder)
y_cylinder = (radius_cylinder + thickness_cylinder/2) * np.sin(theta_cylinder)

# Especificar o raio da esfera
radius_sphere = 20 # Raio em kpc

# Gerar dados para a esfera
u_sphere = np.linspace(0, 2 * np.pi, 100)
v_sphere = np.linspace(0, np.pi, 100)
x_sphere = radius_sphere * np.outer(np.cos(u_sphere), np.sin(v_sphere))
y_sphere = radius_sphere * np.outer(np.sin(u_sphere), np.sin(v_sphere))
z_sphere = radius_sphere * np.outer(np.ones(np.size(u_sphere)), np.cos(v_sphere))

# Leitura dos arquivos de dados
#Esse arquivo pode ser usado para colocar as partículas de diferentes energias para se propagar de forma conjunta.
#basta alterar o caminho que está sendo utilizado.
files = [
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Ferro\Pos_ASS_Sim01_E1_0E14_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Ferro\Pos_ASS_Sim02_E1_0E14_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Ferro\Pos_ASS_Sim03_E1_0E14_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro\Pos_ASS_Sim01_E1_0E15_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro\Pos_ASS_Sim02_E1_0E15_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro\Pos_ASS_Sim03_E1_0E15_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Ferro\Pos_ASS_Sim01_E1_0E16_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Ferro\Pos_ASS_Sim02_E1_0E16_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Ferro\Pos_ASS_Sim03_E1_0E16_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_ASS_Sim01_E6_0E16_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_ASS_Sim02_E6_0E16_P8.dat',
    r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_ASS_Sim03_E6_0E16_P8.dat',
]

# Cores diferentes para cada arquivo (mantidas como no original)
colors = ['blue', 'blue', 'blue','orange','orange','orange', 'green', 'green', 'green', 'brown', 'brown', 'brown']


# Rótulos para cada partícula (mantidos como no original, mas não serão usados na legenda principal)
labels = [f'Particle {i+1}' for i in range(len(files))]

# Criar a figura com um único título
fig = plt.figure(figsize=(12, 6))
fig.suptitle('Galatic Propagation ASS - Iron')
#fig.suptitle('Galatic Propagation ASS - Energy ')

# Subplot 1: Cilindro + Esfera
ax1 = fig.add_subplot(121, projection='3d')

# Plotar o cilindro
ax1.plot_surface(x_cylinder, y_cylinder, z_cylinder, color='lightblue', alpha=0.8)

# Plotar a esfera
ax1.plot_surface(x_sphere, y_sphere, z_sphere, color='lightblue', alpha=0.1)

# Adicionar pontos para o cilindro
ax1.scatter([0], [0], [0], color='black', s=30, label='Galactic Center')
ax1.scatter([-8.5], [0], [0], color='red', s=30, label='Earth')

# Adicionando o espalhamento para o gráfico 1
# Removido o 'label' para evitar entradas repetidas na legenda automática.
for file, color in zip(files, colors):
    x_values, y_values, z_values = read_data(file)
    ax1.scatter(x_values, y_values, z_values, color=color, s=0.5)

# Subplot 2: Trajetórias das partículas
ax2 = fig.add_subplot(122, projection='3d')

# Plotar os dados das partículas com scatter
# Removido o 'label' para evitar entradas repetidas na legenda automática.
for file, color in zip(files, colors):
    x_values, y_values, z_values = read_data(file)
    ax2.scatter(x_values, y_values, z_values, color=color, s=0.5)

# Adicionar marcadores para o Centro Galáctico e a Terra
ax2.scatter([0], [0], [0], color='black', s=30, label='Galactic Center')
ax2.scatter([-8.5], [0], [0], color='red', s=30, label='Earth')

# Definir rótulos dos eixos para ambos os gráficos
for ax in [ax1, ax2]:
    ax.set_xlabel('X (kpc)')
    ax.set_ylabel('Y (kpc)')
    ax.set_zlabel('Z (kpc)')

# --- INÍCIO DA SEÇÃO DA LEGENDA CORRIGIDA E INTEGRADA ---

# Mapeamento de energias para cores para a legenda
# Importante: Revise esta parte se suas energias forem diferentes ou em ordem diferente.
# Baseado em seus 'files' e 'colors' originais:
# 3x 'blue' -> 1.0E14 eV
# 3x 'green' -> 1.0E16 eV
# 3x 'brown' -> 6.0E16 eV (ajuste se for 1.0E17 eV)
legend_info = {
    r'0.1 PeV': 'blue', 
    r'1 PeV': 'orange',
    r'10 PeV': 'green',
    r'60 PeV': 'brown' 
}

# Crie os patches para as energias
energy_patches = [mpatches.Patch(color=color, label=energy_label)
                  for energy_label, color in legend_info.items()]

# Crie os patches para o Centro Galáctico e a Terra (mantidos para serem incluídos na legenda)
additional_patches = [
    mpatches.Patch(color='black', label='Galactic Center'),
    mpatches.Patch(color='red', label='Earth')
]

# Combine todos os patches e adicione a legenda
plt.legend(handles=energy_patches + additional_patches,
           bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)

# --- FIM DA SEÇÃO DA LEGENDA CORRIGIDA E INTEGRADA ---

# Salvar o gráfico
output_path = 'IASSpropag.png' #Nomenclatura ((Inicial da partícula)(Modelo)(Tipo de gráfico))
plt.savefig(output_path, bbox_inches='tight')

# Aviso sonoro de término
winsound.MessageBeep() # Esta linha foi verificada para não ter o caractere invisível
print(f"Gráfico salvo como {output_path}")
print("Gráfico gerado e salvo com sucesso!")

# Exibir o gráfico
plt.tight_layout()
plt.show()