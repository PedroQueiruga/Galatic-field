import numpy as np
import matplotlib.pyplot as plt
import winsound # Para aviso sonoro ao finalizar
import matplotlib.patches as mpatches # Importado para a legenda de patches

# --- CONFIGURAÇÃO DAS PARTÍCULAS E CORES ---
# Definimos os tipos de partículas e suas cores correspondentes.
# Agora temos 5 tipos de partículas, cada uma com sua cor única.
PARTICLE_TYPES = [
    'Proton',
    'Helium',
    'Nitrogen',
    'Aluminium',
    'Iron'
]

# As cores devem ser únicas para cada tipo de partícula para a legenda.
# Você tinha ['blue', 'blue', 'green', 'green', 'brown', 'brown', 'purple', 'purple', 'cyan', 'cyan']
# Vamos usar apenas 5 cores únicas para a legenda, uma para cada tipo de partícula.
# As cores na lista 'colors_for_files' serão usadas para plotar os dados,
# correspondendo à ordem dos arquivos.
UNIQUE_PARTICLE_COLORS = [
    'blue',   # Para Proton
    'green',  # Para Hélio
    'brown',  # Para Nitrogênio
    'purple', # Para Alumínio
    'cyan'    # Para Ferro
]

# --- LEITURA DOS DADOS DAS PARTÍCULAS ---
# Organizamos os caminhos dos arquivos.
# CADA SUB-LISTA AQUI DEVE TER OS ARQUIVOS PARA AQUELA PARTÍCULA.
# MUITO IMPORTANTE: AJUSTE ESTES CAMINHOS PARA OS SEUS ARQUIVOS REAIS!
# Certifique-se de que a ordem das listas de arquivos corresponda à ordem em PARTICLE_TYPES e UNIQUE_PARTICLE_COLORS.

# Arquivos para o MODELO ASS (2 runs para cada uma das 5 partículas)
FILES_ASS_BY_PARTICLE = [
    [ # Proton (azul)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_ASS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_ASS_Sim02_E6_0E16_P1.dat',
    ],
    [ # Hélio (verde)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\Pos_ASS_Sim01_E6_0E16_P2.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\Pos_ASS_Sim02_E6_0E16_P2.dat',
    ],
    [ # Nitrogênio (marrom)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\Pos_ASS_Sim01_E6_0E16_P4.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\Pos_ASS_Sim02_E6_0E16_P4.dat',
    ],
    [ # Alumínio (roxo)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\Pos_ASS_Sim01_E6_0E16_P6.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\Pos_ASS_Sim02_E6_0E16_P6.dat',
    ],
    [ # Ferro (ciano)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_ASS_Sim01_E6_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_ASS_Sim02_E6_0E16_P8.dat',
    ]
]

# Arquivos para o MODELO BSS (2 runs para cada uma das 5 partículas)
FILES_BSS_BY_PARTICLE = [
    [ # Proton (azul)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_BSS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_BSS_Sim02_E6_0E16_P1.dat',
    ],
    [ # Hélio (verde)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\Pos_BSS_Sim01_E6_0E16_P2.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\Pos_BSS_Sim02_E6_0E16_P2.dat',
    ],
    [ # Nitrogênio (marrom)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\Pos_BSS_Sim01_E6_0E16_P4.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\Pos_BSS_Sim02_E6_0E16_P4.dat',
    ],
    [ # Alumínio (roxo)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\Pos_BSS_Sim01_E6_0E16_P6.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\Pos_BSS_Sim02_E6_0E16_P6.dat',
    ],
    [ # Ferro (ciano)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_BSS_Sim01_E6_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\Pos_BSS_Sim02_E6_0E16_P8.dat',
    ]
]
# --- FIM DA LEITURA DOS DADOS DAS PARTÍCULAS ---


# Leitura dos dados dos vetores magnéticos (quiver) - MANTIDO
data_ASS = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\magneticvectorASSxy.dat')
data_BSS = np.loadtxt(r'C:\Users\User\Dropbox\Queiruga\progs\CRs_python\data\magneticvectorBSSxy.dat')

# Separação das colunas para os vetores magnéticos (ASS) - MANTIDO
x_ASS = data_ASS[:, 0]
y_ASS = data_ASS[:, 1]
Bx_ASS = data_ASS[:, 2] * 1e10 # Convertendo para Microgauss
By_ASS = data_ASS[:, 3] * 1e10

# Separação das colunas para os vetores magnéticos (BSS) - MANTIDO
x_BSS = data_BSS[:, 0]
y_BSS = data_BSS[:, 1]
Bx_BSS = data_BSS[:, 2] * 1e10
By_BSS = data_BSS[:, 3] * 1e10

# Criando duas subplots (um para ASS e outro para BSS) - MANTIDO
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# --- Gráfico ASS ---
# Campo Magnético
ax1.quiver(x_ASS, y_ASS, Bx_ASS, By_ASS, color='black', alpha=0.6, scale=1e2, zorder=0)

# Trajetórias das Partículas
for i, particle_type in enumerate(PARTICLE_TYPES):
    current_color = UNIQUE_PARTICLE_COLORS[i]
    files_for_this_particle = FILES_ASS_BY_PARTICLE[i]
    for j, filename in enumerate(files_for_this_particle):
        try:
            particle_data = np.loadtxt(filename)
            particle_x = particle_data[:, 0]
            particle_y = particle_data[:, 1]
            # Removendo 'label' da plotagem para que a legenda seja construída manualmente
            ax1.scatter(particle_x, particle_y, color=current_color, s=5, zorder=1)
        except FileNotFoundError:
            print(f"AVISO: Arquivo não encontrado para ASS ({particle_type}, run {j+1}): {filename}. Pulando.")

# Ponto da Terra
# Removendo 'label' da plotagem para que a legenda seja construída manualmente
ax1.scatter([-8.5], [0], color='red', s=30, zorder=2)

ax1.set_title('ASS Model: 2D trajectory of Particles (60 PeV)') # Título mais genérico
ax1.set_xlabel('X (kpc)')
ax1.set_ylabel('Y (kpc)')
ax1.grid()

# --- Construção da Legenda para ax1 ---
legend_handles_ax1 = []

# Adicionando a seta para o Campo Magnético na legenda
# Usamos FancyArrow para simular uma seta
field_arrow_patch = mpatches.FancyArrow(0, 0, 0.5, 0, width=0.1, head_width=0.3, head_length=0.2,
                                         fc='black', ec='black', label='Magnetic Field')
legend_handles_ax1.append(field_arrow_patch)

# Adicionando as barras para as Partículas na legenda
for i, particle_type in enumerate(PARTICLE_TYPES):
    particle_patch = mpatches.Patch(color=UNIQUE_PARTICLE_COLORS[i], label=particle_type)
    legend_handles_ax1.append(particle_patch)

# Adicionando a barra para a Terra na legenda
earth_patch = mpatches.Patch(color='red', label='Earth')
legend_handles_ax1.append(earth_patch)

# Configurando a legenda do ax1
ax1.legend(handles=legend_handles_ax1, loc='lower right', title='Legend',
           fontsize='small', handlelength=2.0, handletextpad=0.5,
           bbox_to_anchor=(1.02, 0), borderaxespad=0.)


# --- Gráfico BSS ---
# Campo Magnético
ax2.quiver(x_BSS, y_BSS, Bx_BSS, By_BSS, color='black', alpha=0.6, scale=1e2, zorder=0)

# Trajetórias das Partículas
for i, particle_type in enumerate(PARTICLE_TYPES):
    current_color = UNIQUE_PARTICLE_COLORS[i]
    files_for_this_particle = FILES_BSS_BY_PARTICLE[i]
    for j, filename in enumerate(files_for_this_particle):
        try:
            particle_data = np.loadtxt(filename)
            particle_x = particle_data[:, 0]
            particle_y = particle_data[:, 1]
            # Removendo 'label' da plotagem para que a legenda seja construída manualmente
            ax2.scatter(particle_x, particle_y, color=current_color, s=5, zorder=1)
        except FileNotFoundError:
            print(f"AVISO: Arquivo não encontrado para BSS ({particle_type}, run {j+1}): {filename}. Pulando.")

# Ponto da Terra
# Removendo 'label' da plotagem para que a legenda seja construída manualmente
ax2.scatter([-8.5], [0], color='red', s=30, zorder=2)

ax2.set_title('BSS Model: 2D trajectory of Particles (60 PeV)') # Título mais genérico
ax2.set_xlabel('X (kpc)')
ax2.grid()

# --- Construção da Legenda para ax2 ---
legend_handles_ax2 = []

# Adicionando a seta para o Campo Magnético na legenda
field_arrow_patch_ax2 = mpatches.FancyArrow(0, 0, 0.5, 0, width=0.1, head_width=0.3, head_length=0.2,
                                             fc='black', ec='black', label='Magnetic Field')
legend_handles_ax2.append(field_arrow_patch_ax2)

# Adicionando as barras para as Partículas na legenda
for i, particle_type in enumerate(PARTICLE_TYPES):
    particle_patch_ax2 = mpatches.Patch(color=UNIQUE_PARTICLE_COLORS[i], label=particle_type)
    legend_handles_ax2.append(particle_patch_ax2)

# Adicionando a barra para a Terra na legenda
earth_patch_ax2 = mpatches.Patch(color='red', label='Earth')
legend_handles_ax2.append(earth_patch_ax2)

# Configurando a legenda do ax2
ax2.legend(handles=legend_handles_ax2, loc='lower right', title='Legend',
           fontsize='small', handlelength=2.0, handletextpad=0.5,
           bbox_to_anchor=(1.02, 0), borderaxespad=0.)

# Ajuste de layout e salvamento - MANTIDO
fig.set_facecolor('white')
plt.tight_layout()

# Aviso sonoro de término - MANTIDO
try:
    winsound.MessageBeep()
except ImportError:
    print("Módulo 'winsound' não disponível (apenas Windows).")

output_path = '60PeVTrajectories_ASS_BSS_AllParticles.png' # Nome do arquivo mais descritivo
plt.savefig(output_path, bbox_inches='tight')

# Exibindo a figura
plt.show()

print(f"Gráfico salvo como {output_path}")