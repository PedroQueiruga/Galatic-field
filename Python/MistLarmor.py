import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.patches as mpatches # Importamos mpatches para criar as barras na legenda

# --- CONFIGURAÇÃO DE ENERGIAS E CORES ---
# Definimos as energias que você tem e as cores que deseja para cada uma.
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

# --- CAMINHOS DOS ARQUIVOS DE DADOS DO RAIO DE LARMOR ---
# --- MODELO ASS ---
# MUITO IMPORTANTE: AJUSTE ESTES CAMINHOS PARA OS SEUS ARQUIVOS REAIS DO MODELO ASS!
LARMOR_FILES_ASS_BY_ENERGY = [
    [ # Arquivos para 1.0E14 eV (ASS)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\larmor_BSS_Sim01_E1_0E14_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\larmor_BSS_Sim02_E1_0E14_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Proton\larmor_BSS_Sim03_E1_0E14_P1.dat', 
    ],
    [ # Energia 1.0E15 eV (Laranja)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\larmor_BSS_Sim01_E1_0E15_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\larmor_BSS_Sim02_E1_0E15_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Proton\larmor_BSS_Sim03_E1_0E15_P1.dat',
    ],
    [ # Arquivos para 1.0E16 eV (BSS)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\larmor_BSS_Sim01_E1_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\larmor_BSS_Sim02_E1_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Proton\larmor_BSS_Sim03_E1_0E16_P1.dat',
    ],
    [ # Arquivos para 6.0E16 eV (BSS)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_BSS_Sim01_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_BSS_Sim02_E6_0E16_P1.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Proton\larmor_BSS_Sim03_E6_0E16_P1.dat',
    ]
]

# --- MODELO BSS --- ##Substituido temporariamente para comparar dois modelos BSS e dois BSS
# AJUSTE ESTES CAMINHOS PARA OS SEUS ARQUIVOS REAIS DO MODELO BSS!
LARMOR_FILES_BSS_BY_ENERGY = [
    [ # Arquivos para 1.0E14 eV (BSS)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Ferro\larmor_BSS_Sim01_E1_0E14_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Ferro\larmor_BSS_Sim02_E1_0E14_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E14\Ferro\larmor_BSS_Sim03_E1_0E14_P8.dat',
    ],
    [ # Energia 1.0E15 eV (Laranja)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro\larmor_BSS_Sim01_E1_0E15_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro\larmor_BSS_Sim02_E1_0E15_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro\larmor_BSS_Sim03_E1_0E15_P8.dat',
    ],
    [ # Arquivos para 1.0E16 eV (BSS)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Ferro\larmor_BSS_Sim01_E1_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Ferro\larmor_BSS_Sim02_E1_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E16\Ferro\larmor_BSS_Sim03_E1_0E16_P8.dat',
    ],
    [ # Arquivos para 6.0E16 eV (BSS)
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_BSS_Sim01_E6_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_BSS_Sim02_E6_0E16_P8.dat',
        r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_6_0E16\Ferro\larmor_BSS_Sim03_E6_0E16_P8.dat',
    ]
]
# --- FIM DOS CAMINHOS DOS ARQUIVOS ---

# --- CRIAÇÃO DA FIGURA E SUBPLOTS ---
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7), sharey=True) # Criamos duas subplots lado a lado

# Definir o título geral da figura
fig.suptitle('Larmor Radius VS Time Comparison in Different Energies (BSS Model)', fontsize=16)

# --- PLOTAGEM PARA O MODELO ASS (ax1) ---
ax1.set_title('Proton')
ax1.set_xlabel(r'$\log(t[s])$')
ax1.set_ylabel(r'$\log(r_L[kpc])$')
ax1.grid(True)

# Lista para armazenar os "handles" da legenda para o eixo ASS
legend_handles_ass = []

# Loop sobre as energias para carregar e plotar os dados no ax1 (ASS)
for i, energy_label in enumerate(ENERGIES):
    current_color = COLORS[i]
    files_for_this_energy = LARMOR_FILES_ASS_BY_ENERGY[i]

    # Crie um patch para esta energia e adicione-o aos handles da legenda do ASS
    legend_handles_ass.append(mpatches.Patch(color=current_color, label=energy_label))

    for j, file_path in enumerate(files_for_this_energy):
        try:
            data = pd.read_csv(file_path, header=None, delim_whitespace=True)
            time_data = data[0]
            larmor_radius_data = data[1]

            time_ln = np.log10(time_data + 1e-10)
            larmor_radius_ln = np.log10(larmor_radius_data + 1e-10)

            # Plote os dados no subplot ASS
            ax1.scatter(time_ln, larmor_radius_ln, marker='o', s=1, color=current_color)

        except FileNotFoundError:
            print(f"AVISO: Arquivo ASS não encontrado para {energy_label}, run {j+1}: {file_path}. Pulando.")
        except pd.errors.EmptyDataError:
            print(f"AVISO: Arquivo ASS vazio encontrado para {energy_label}, run {j+1}: {file_path}. Pulando.")
        except Exception as e:
            print(f"Erro ao processar o arquivo ASS {file_path}: {e}. Pulando.")

# Adiciona a legenda ao subplot ASS
ax1.legend(handles=legend_handles_ass, title='Particle Energy', loc='best',
           fontsize='medium', handlelength=2.0, handletextpad=0.5)

# --- PLOTAGEM PARA O MODELO BSS (ax2) ---
ax2.set_title('Iron')
ax2.set_xlabel(r'$\log(t[s])$')
# ax2.set_ylabel(r'$\ln(r_L[kpc])$') # Removido pois sharey=True já faz o trabalho
ax2.grid(True)

# Lista para armazenar os "handles" da legenda para o eixo BSS
# (Poderíamos usar os mesmos handles do ASS se a legenda for idêntica)
legend_handles_bss = []

# Loop sobre as energias para carregar e plotar os dados no ax2 (BSS)
for i, energy_label in enumerate(ENERGIES):
    current_color = COLORS[i]
    files_for_this_energy = LARMOR_FILES_BSS_BY_ENERGY[i]

    # Crie um patch para esta energia e adicione-o aos handles da legenda do BSS
    legend_handles_bss.append(mpatches.Patch(color=current_color, label=energy_label))

    for j, file_path in enumerate(files_for_this_energy):
        try:
            data = pd.read_csv(file_path, header=None, delim_whitespace=True)
            time_data = data[0]
            larmor_radius_data = data[1]

            time_ln = np.log10(time_data + 1e-10)
            larmor_radius_ln = np.log10(larmor_radius_data + 1e-10)

            # Plote os dados no subplot BSS
            ax2.scatter(time_ln, larmor_radius_ln, marker='o', s=1, color=current_color)

        except FileNotFoundError:
            print(f"AVISO: Arquivo BSS não encontrado para {energy_label}, run {j+1}: {file_path}. Pulando.")
        except pd.errors.EmptyDataError:
            print(f"AVISO: Arquivo BSS vazio encontrado para {energy_label}, run {j+1}: {file_path}. Pulando.")
        except Exception as e:
            print(f"Erro ao processar o arquivo BSS {file_path}: {e}. Pulando.")

# Adiciona a legenda ao subplot BSS
ax2.legend(handles=legend_handles_bss, title='Particle Energy', loc='best',
           fontsize='medium', handlelength=2.0, handletextpad=0.5)


# --- AJUSTES FINAIS E SALVAMENTO ---
plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Ajusta o layout, deixando espaço para o suptitle
output_path = 'Comparison_larmor_proton_iron_BSS.png' # Nome do arquivo
plt.savefig(output_path, dpi=300)

plt.show()

print(f"Gráfico salvo como {output_path}")