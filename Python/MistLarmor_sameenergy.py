import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.patches as mpatches # Importamos mpatches para criar as barras na legenda

# --- CONFIGURAÇÃO DAS PARTÍCULAS E CORES ---
PARTICLE_TYPES = [
    'Proton',
    'Helium',
    'Nitrogen',
    'Aluminium',
    'Iron'
]

UNIQUE_PARTICLE_COLORS = [
    'blue',   # Para Proton
    'green',  # Para Hélio
    'brown',  # Para Nitrogênio
    'purple', # Para Alumínio
    'cyan'    # Para Ferro
]

ENERGY_LABEL = r'60 PeV' 

# --- CAMINHOS DOS ARQUIVOS DE DADOS DO RAIO DE LARMOR ---
# --- MODELO ASS ---
LARMOR_FILES_ASS_BY_PARTICLE = [
    [ # Arquivos para Proton (azul)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_ASS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_ASS_Sim02_E6_0E16_P1.dat',
    ],
    [ # Arquivos para Hélio (verde)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\larmor_ASS_Sim01_E6_0E16_P2.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\larmor_ASS_Sim02_E6_0E16_P2.dat',
    ],
    [ # Arquivos para Nitrogênio (marrom)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\larmor_ASS_Sim01_E6_0E16_P4.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\larmor_ASS_Sim02_E6_0E16_P4.dat',
    ],
    [ # Arquivos para Alumínio (roxo)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\larmor_ASS_Sim01_E6_0E16_P6.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\larmor_ASS_Sim02_E6_0E16_P6.dat',
    ],
    [ # Arquivos para Ferro (ciano)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_ASS_Sim01_E6_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_ASS_Sim02_E6_0E16_P8.dat',
    ]
]

# --- MODELO BSS ---
# DUPLIQUE E AJUSTE ESTES CAMINHOS PARA SEUS ARQUIVOS BSS CORRETOS!
LARMOR_FILES_BSS_BY_PARTICLE = [
    [ # Arquivos para Proton (azul)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_BSS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_BSS_Sim02_E6_0E16_P1.dat',
    ],
    [ # Arquivos para Hélio (verde)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\larmor_BSS_Sim01_E6_0E16_P2.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Helio\larmor_BSS_Sim02_E6_0E16_P2.dat',
    ],
    [ # Arquivos para Nitrogênio (marrom)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\larmor_BSS_Sim01_E6_0E16_P4.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Nitrogenio\larmor_BSS_Sim02_E6_0E16_P4.dat',
    ],
    [ # Arquivos para Alumínio (roxo)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\larmor_BSS_Sim01_E6_0E16_P6.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Aluminio\larmor_BSS_Sim02_E6_0E16_P6.dat',
    ],
    [ # Arquivos para Ferro (ciano)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_BSS_Sim01_E6_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_BSS_Sim02_E6_0E16_P8.dat',
    ]
]
# --- FIM DOS CAMINHOS DOS ARQUIVOS ---

# --- CRIAÇÃO DA FIGURA E SUBPLOTS ---
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7), sharey=True) # Criamos duas subplots lado a lado

# Definir o título geral da figura
fig.suptitle(f'Larmor Radius VS Time for Different Particle Types ({ENERGY_LABEL})', fontsize=16)

# --- PLOTAGEM PARA O MODELO ASS (ax1) ---
ax1.set_title('ASS Model')
ax1.set_xlabel(r'$\log(t[s])$')
ax1.set_ylabel(r'$\log(r_L[kpc])$')
ax1.grid(True)

# Lista para armazenar os "handles" da legenda para o eixo ASS
legend_handles_ass = []

for i, particle_type in enumerate(PARTICLE_TYPES):
    current_color = UNIQUE_PARTICLE_COLORS[i]
    files_for_this_particle = LARMOR_FILES_ASS_BY_PARTICLE[i]

    # Crie um patch para esta partícula e adicione-o aos handles da legenda
    legend_handles_ass.append(mpatches.Patch(color=current_color, label=particle_type))

    for j, file_path in enumerate(files_for_this_particle):
        try:
            data = pd.read_csv(file_path, header=None, delim_whitespace=True)
            time_data = data[0]
            larmor_radius_data = data[1]

            time_ln = np.log10(time_data + 1e-10)
            larmor_radius_ln = np.log10(larmor_radius_data + 1e-10)

            # Plote os dados no subplot ASS
            ax1.scatter(time_ln, larmor_radius_ln, marker='o', s=1, color=current_color)

        except FileNotFoundError:
            print(f"AVISO: Arquivo ASS não encontrado para {particle_type}, run {j+1}: {file_path}. Pulando.")
        except pd.errors.EmptyDataError:
            print(f"AVISO: Arquivo ASS vazio encontrado para {particle_type}, run {j+1}: {file_path}. Pulando.")
        except Exception as e:
            print(f"Erro ao processar o arquivo ASS {file_path}: {e}. Pulando.")

# Adiciona a legenda ao subplot ASS
ax1.legend(handles=legend_handles_ass, title='Particle Type', loc='best',
           fontsize='medium', handlelength=2.0, handletextpad=0.5)

# --- PLOTAGEM PARA O MODELO BSS (ax2) ---
ax2.set_title('BSS Model')
ax2.set_xlabel(r'$\log(t[s])$')
# ax2.set_ylabel(r'$\ln(r_L[kpc])$') # Removido pois sharey=True já faz o trabalho
ax2.grid(True)

# Lista para armazenar os "handles" da legenda para o eixo BSS
legend_handles_bss = []

for i, particle_type in enumerate(PARTICLE_TYPES):
    current_color = UNIQUE_PARTICLE_COLORS[i]
    files_for_this_particle = LARMOR_FILES_BSS_BY_PARTICLE[i]

    # Crie um patch para esta partícula e adicione-o aos handles da legenda
    # Não é estritamente necessário duplicar os patches se a legenda for a mesma,
    # mas é uma prática mais robusta caso você queira legendas diferentes no futuro.
    legend_handles_bss.append(mpatches.Patch(color=current_color, label=particle_type))

    for j, file_path in enumerate(files_for_this_particle):
        try:
            data = pd.read_csv(file_path, header=None, delim_whitespace=True)
            time_data = data[0]
            larmor_radius_data = data[1]

            time_ln = np.log10(time_data + 1e-10)
            larmor_radius_ln = np.log10(larmor_radius_data + 1e-10)

            # Plote os dados no subplot BSS
            ax2.scatter(time_ln, larmor_radius_ln, marker='o', s=1, color=current_color)

        except FileNotFoundError:
            print(f"AVISO: Arquivo BSS não encontrado para {particle_type}, run {j+1}: {file_path}. Pulando.")
        except pd.errors.EmptyDataError:
            print(f"AVISO: Arquivo BSS vazio encontrado para {particle_type}, run {j+1}: {file_path}. Pulando.")
        except Exception as e:
            print(f"Erro ao processar o arquivo BSS {file_path}: {e}. Pulando.")

# Adiciona a legenda ao subplot BSS
# Optamos por compartilhar a legenda entre os dois gráficos para evitar redundância.
# Uma forma de fazer isso é plotar a legenda em apenas um dos gráficos ou
# criar uma legenda comum para toda a figura (mas a localização pode ser complicada).
# Neste caso, vamos adicionar a legenda ao ax2 (o gráfico da direita) e ele compartilha os mesmos itens de legenda.
ax2.legend(handles=legend_handles_bss, title='Particle Type', loc='best',
           fontsize='medium', handlelength=2.0, handletextpad=0.5)


# --- AJUSTES FINAIS E SALVAMENTO ---
plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Ajusta o layout, deixando espaço para o suptitle
output_path = f'60PeVLarmorRadius_ASS_BSS_AllParticles_{ENERGY_LABEL.replace(" ", "")}.png' # Nome do arquivo dinâmico
plt.savefig(output_path, dpi=300)

plt.show()

print(f"Gráfico salvo como {output_path}")