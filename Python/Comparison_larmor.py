import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.patches as mpatches

# --- CONFIGURAÇÕES ---
ENERGIES = [r'0.1 PeV', r'1 PeV', r'10 PeV', r'60 PeV']
COLORS = ['blue', 'orange', 'green', 'brown']

# --- ESCOLHA DO MODELO A SER USADO: 'ASS' ou 'BSS' ---
USE_MODEL = 'ASS'  # Altere para 'BSS' para trocar de modelo

# --- FUNÇÃO PARA GERAR CAMINHOS AUTOMATICAMENTE ---
def generate_paths(particle, model):
    base = r'C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados'
    energies = ['Energia_1_0E14', 'Energia_1_0E15', 'Energia_1_0E16', 'Energia_6_0E16']
    energy_tags = ['E1_0E14', 'E1_0E15', 'E1_0E16', 'E6_0E16']
    
    paths = []
    for energy_folder, tag in zip(energies, energy_tags):
        folder = f'{base}\\{energy_folder}\\{particle}'
        files = [f'{folder}\\larmor_{model}_Sim0{i}_' + f'{tag}_P1.dat' for i in range(1, 4)]
        paths.append(files)
    return paths

# --- GERA OS CAMINHOS PARA CADA PARTÍCULA ---
LARMOR_FILES_PROTON = generate_paths('Proton', USE_MODEL)
LARMOR_FILES_IRON   = generate_paths('Ferro', USE_MODEL)

# --- CRIAÇÃO DOS SUBPLOTS ---
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7), sharey=True)
fig.suptitle(f'Larmor Radius VS Time: Proton vs Iron ({USE_MODEL} Model)', fontsize=16)

# --- PLOTAGEM PARA PRÓTON ---
ax1.set_title('Proton')
ax1.set_xlabel(r'$\log(t[s])$')
ax1.set_ylabel(r'$\log(r_L[kpc])$')
ax1.grid(True)

legend_handles_proton = []
for i, energy_label in enumerate(ENERGIES):
    color = COLORS[i]
    files = LARMOR_FILES_PROTON[i]
    legend_handles_proton.append(mpatches.Patch(color=color, label=energy_label))
    for j, file_path in enumerate(files):
        try:
            data = pd.read_csv(file_path, header=None, delim_whitespace=True)
            time_ln = np.log10(data[0] + 1e-10)
            radius_ln = np.log10(data[1] + 1e-10)
            ax1.scatter(time_ln, radius_ln, s=1, color=color)
        except Exception as e:
            print(f"Erro (Proton - {energy_label} - run {j+1}): {file_path} - {e}")

ax1.legend(handles=legend_handles_proton, title='Energy', loc='best', fontsize='medium')

# --- PLOTAGEM PARA FERRO ---
ax2.set_title('Iron')
ax2.set_xlabel(r'$\log(t[s])$')
ax2.grid(True)

legend_handles_iron = []
for i, energy_label in enumerate(ENERGIES):
    color = COLORS[i]
    files = LARMOR_FILES_IRON[i]
    legend_handles_iron.append(mpatches.Patch(color=color, label=energy_label))
    for j, file_path in enumerate(files):
        try:
            data = pd.read_csv(file_path, header=None, delim_whitespace=True)
            time_ln = np.log10(data[0] + 1e-10)
            radius_ln = np.log10(data[1] + 1e-10)
            ax2.scatter(time_ln, radius_ln, s=1, color=color)
        except Exception as e:
            print(f"Erro (Iron - {energy_label} - run {j+1}): {file_path} - {e}")

ax2.legend(handles=legend_handles_iron, title='Energy', loc='best', fontsize='medium')

# --- SALVAMENTO ---
plt.tight_layout(rect=[0, 0.03, 1, 0.95])
output_path = f'Comparison_{USE_MODEL}_Proton_vs_Iron.png'
plt.savefig(output_path, dpi=300)
plt.show()
print(f"Gráfico salvo como {output_path}")
