import numpy as np
import matplotlib.pyplot as plt
import winsound # Para aviso sonoro ao finalizar
import matplotlib.patches as mpatches # Importado para a legenda de patches

# --- CONFIGURAÇÃO DE ENERGIAS E CORES ---
# Definimos as energias e suas cores correspondentes.
# Ajuste '6.0E16 eV' para '1.0E17 eV' se essa for a energia correta para seus dados.
ENERGIES = [
    r'0.1 PeV',
    r'1 PeV',
    r'10 PeV',
    r'60 PeV'
]

COLORS = [
    'blue',  # Para 1.0E14 eV
    'orange',
    'green', # Para 1.0E16 eV
    'brown'  # Para 6.0E16 eV
]

# --- LEITURA DOS DADOS DAS PARTÍCULAS ---
# Organizamos os caminhos dos arquivos.
# CADA SUB-LISTA AQUI DEVE TER OS 3 ARQUIVOS PARA AQUELA ENERGIA.
# MUITO IMPORTANTE: AJUSTE ESTES CAMINHOS PARA OS SEUS ARQUIVOS REAIS!
# Certifique-se de que a ordem das listas de arquivos corresponda à ordem em ENERGIES e COLORS.

# Arquivos para o MODELO ASS (3 runs para cada uma das 3 energias)
FILES_ASS_BY_ENERGY = [
    [ # Energia 1.0E14 eV (azul)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\Pos_ASS_Sim01_E1_0E14_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\Pos_ASS_Sim02_E1_0E14_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\Pos_ASS_Sim03_E1_0E14_P1.dat',
    ],
    [ # Energia 1.0E15 eV (Laranja)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\Pos_ASS_Sim01_E1_0E15_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\Pos_ASS_Sim02_E1_0E15_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\Pos_ASS_Sim03_E1_0E15_P1.dat',
    ],
    [ # Energia 1.0E16 eV (verde)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\Pos_ASS_Sim01_E1_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\Pos_ASS_Sim02_E1_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\Pos_ASS_Sim03_E1_0E16_P1.dat',
    ],
    [ # Energia 6.0E16 eV (marrom)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_ASS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_ASS_Sim02_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_ASS_Sim03_E6_0E16_P1.dat',
    ]
]

# Arquivos para o MODELO BSS (3 runs para cada uma das 3 energias)
FILES_BSS_BY_ENERGY = [
    [ # Energia 1.0E14 eV (azul)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\Pos_BSS_Sim01_E1_0E14_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\Pos_BSS_Sim02_E1_0E14_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\Pos_BSS_Sim03_E1_0E14_P1.dat',
    ],
    [ # Energia 1.0E15 eV (Laranja)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\Pos_BSS_Sim01_E1_0E15_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\Pos_BSS_Sim02_E1_0E15_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\Pos_BSS_Sim03_E1_0E15_P1.dat',
    ],
    [ # Energia 1.0E16 eV (verde)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\Pos_BSS_Sim01_E1_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\Pos_BSS_Sim02_E1_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\Pos_BSS_Sim03_E1_0E16_P1.dat',
    ],
    [ # Energia 6.0E16 eV (marrom)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_BSS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_BSS_Sim02_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\Pos_BSS_Sim03_E6_0E16_P1.dat',
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
# Removendo 'label' da plotagem para que a legenda seja construída manualmente
ax1.quiver(x_ASS, y_ASS, Bx_ASS, By_ASS, color='black', alpha=0.6, scale=1e2)

# Trajetórias das Partículas
for i, energy_label in enumerate(ENERGIES):
    current_color = COLORS[i]
    files_for_this_energy = FILES_ASS_BY_ENERGY[i]
    for j, filename in enumerate(files_for_this_energy):
        try:
            particle_data = np.loadtxt(filename)
            particle_x = particle_data[:, 0]
            particle_y = particle_data[:, 1]
            # Removendo 'label' da plotagem para que a legenda seja construída manualmente
            ax1.scatter(particle_x, particle_y, color=current_color, s=0.5)
        except FileNotFoundError:
            print(f"AVISO: Arquivo não encontrado para ASS ({energy_label}, run {j+1}): {filename}. Pulando.")

# Ponto da Terra
# Removendo 'label' da plotagem para que a legenda seja construída manualmente
ax1.scatter([-8.5], [0], color='red', s=30)

ax1.set_title('ASS Model: 2D trajectory of Proton')
ax1.set_xlabel('X (kpc)')
ax1.set_ylabel('Y (kpc)')
ax1.grid()

# --- Construção da Legenda para ax1 ---
legend_handles_ax1 = []

# Adicionando a seta para o Campo Magnético na legenda
field_arrow_patch = mpatches.FancyArrow(0, 0, 0.5, 0, width=0.1, head_width=0.3, head_length=0.2,
                                         fc='black', ec='black', label='Magnetic Field')
legend_handles_ax1.append(field_arrow_patch)

# Adicionando as barras para as Energias na legenda
for i, energy_label in enumerate(ENERGIES):
    energy_patch = mpatches.Patch(color=COLORS[i], label=energy_label)
    legend_handles_ax1.append(energy_patch)

# Adicionando a barra para a Terra na legenda
earth_patch = mpatches.Patch(color='red', label='Earth')
legend_handles_ax1.append(earth_patch)

# Configurando a legenda do ax1
ax1.legend(handles=legend_handles_ax1, loc='lower right', title='Legend',
           fontsize='small', handlelength=2.0, handletextpad=0.5,
           bbox_to_anchor=(1.02, 0), borderaxespad=0.)


# --- Gráfico BSS ---
# Campo Magnético
# Removendo 'label' da plotagem para que a legenda seja construída manualmente
ax2.quiver(x_BSS, y_BSS, Bx_BSS, By_BSS, color='black', alpha=0.6, scale=1e2)

# Trajetórias das Partículas
for i, energy_label in enumerate(ENERGIES):
    current_color = COLORS[i]
    files_for_this_energy = FILES_BSS_BY_ENERGY[i]
    for j, filename in enumerate(files_for_this_energy):
        try:
            particle_data = np.loadtxt(filename)
            particle_x = particle_data[:, 0]
            particle_y = particle_data[:, 1]
            # Removendo 'label' da plotagem para que a legenda seja construída manualmente
            ax2.scatter(particle_x, particle_y, color=current_color, s=0.5)
        except FileNotFoundError:
            print(f"AVISO: Arquivo não encontrado para BSS ({energy_label}, run {j+1}): {filename}. Pulando.")

# Ponto da Terra
# Removendo 'label' da plotagem para que a legenda seja construída manualmente
ax2.scatter([-8.5], [0], color='red', s=30)

ax2.set_title('BSS Model: 2D trajectory of Proton')
ax2.set_xlabel('X (kpc)')
ax2.grid()

# --- Construção da Legenda para ax2 ---
legend_handles_ax2 = []

# Adicionando a seta para o Campo Magnético na legenda
field_arrow_patch_ax2 = mpatches.FancyArrow(0, 0, 0.5, 0, width=0.1, head_width=0.3, head_length=0.2,
                                             fc='black', ec='black', label='Magnetic Field')
legend_handles_ax2.append(field_arrow_patch_ax2)

# Adicionando as barras para as Energias na legenda
for i, energy_label in enumerate(ENERGIES):
    energy_patch_ax2 = mpatches.Patch(color=COLORS[i], label=energy_label)
    legend_handles_ax2.append(energy_patch_ax2)

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

output_path = 'ProtonPos_ASS_BSS.png'
plt.savefig(output_path, bbox_inches='tight')

# Exibindo a figura
plt.show()

# Aviso sonoro de término - MANTIDO
try:
    winsound.MessageBeep()
except ImportError:
    print("Módulo 'winsound' não disponível (apenas Windows).")
print(f"Gráfico salvo como {output_path}")
print("Gráfico gerado e salvo com sucesso!")