# -*- coding: utf-8 -*-


# --- 1. Importação de Bibliotecas ---
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from mpl_toolkits.mplot3d import Axes3D
from pathlib import Path

# --- 2. CONFIGURAÇÃO PRINCIPAL ---
# AJUSTE APENAS AS VARIÁVEIS DESTA SEÇÃO

PROJECT_ROOT = Path(__file__).parent.parent
BASE_DATA_DIR = PROJECT_ROOT
MAGNETIC_FIELD_DIR = PROJECT_ROOT / "mapping_data"
OUTPUT_DIR = PROJECT_ROOT / "Graficos_Gerados_MultiEnergia"

# <<< ALTERAÇÃO CHAVE 1: Dicionário de Tradução >>>
# Mapeia o nome da pasta (em Português) para o nome de exibição (em Inglês).
PARTICLE_TRANSLATION_MAP = {
    'Proton':     'Proton',
    'Helio':      'Helium',
    'Nitrogenio': 'Nitrogen',
    'Aluminio':   'Aluminium',
    'Ferro':      'Iron'
}

# Defina a partícula que você quer analisar usando o NOME DA PASTA (em Português).
TARGET_PARTICLE_FOLDER = 'Ferro'

# Mapeamento de Energias para legendas e cores.
ENERGY_MAPPING = {
    '1_0E18': {'display_label': '1 EeV',   'color': 'brown'},
    '1_0E19': {'display_label': '10 EeV',  'color': 'green'},
    '1_0E20': {'display_label': '100 EeV', 'color': 'pink'}
}

# Configurações de visualização
N_TRAJECTORIES_TO_PLOT = 5
SCATTER_SIZE_3D = 1.0
SCATTER_SIZE_2D = 1.5

# --- FIM DA CONFIGURAÇÃO ---


def find_data_files(base_dir, particle_folder, energy_map):
    """
    Encontra e organiza todos os arquivos para uma dada PARTÍCULA em várias energias.
    """
    # Usa o nome em português para encontrar a pasta
    print(f"Finding data for folder: '{particle_folder}'...")
    
    organized_data = {energy_key: {'ASS': {}, 'BSS': {}} for energy_key in energy_map.keys()}

    for energy_key in energy_map.keys():
        energy_folder_name = f"Energia_{energy_key}"
        particle_dir = base_dir / "Simulacoes_Resultados" / energy_folder_name / particle_folder

        if not particle_dir.is_dir():
            print(f"--> WARNING: Directory not found: {particle_dir}. Skipping energy '{energy_key}'.")
            continue

        organized_data[energy_key]['ASS']['pos'] = sorted(particle_dir.glob('Pos_ASS_*.dat'))
        organized_data[energy_key]['BSS']['pos'] = sorted(particle_dir.glob('Pos_BSS_*.dat'))
        organized_data[energy_key]['ASS']['larmor'] = sorted(particle_dir.glob('larmor_ASS_*.dat'))
        organized_data[energy_key]['BSS']['larmor'] = sorted(particle_dir.glob('larmor_BSS_*.dat'))
        organized_data[energy_key]['ASS']['plane'] = sorted(particle_dir.glob('plane_ASS_*.dat'))
        organized_data[energy_key]['BSS']['plane'] = sorted(particle_dir.glob('plane_BSS_*.dat'))

    print("Archive search completed.")
    return organized_data


def plot_3d_trajectories(data_paths, particle_display_name):
    # Usa o nome em inglês para os prints e títulos
    print(f"[1/4] Making 3D graphs for: {particle_display_name}...")
    for model in ["ASS", "BSS"]:
        fig = plt.figure(figsize=(18, 8))
        fig.suptitle(f'Galactic Propagation for {particle_display_name} - {model} Model', fontsize=16)

        ax1 = fig.add_subplot(121, projection='3d')
        radius_sphere = 20
        u, v = np.mgrid[0:2*np.pi:100j, 0:np.pi:100j]
        x_s, y_s, z_s = radius_sphere * np.cos(u) * np.sin(v), radius_sphere * np.sin(u) * np.sin(v), radius_sphere * np.cos(v)
        ax1.plot_wireframe(x_s, y_s, z_s, color='lightblue', alpha=0.4)
        ax1.set_title("Trajectory with Galactic Halo")
        ax2 = fig.add_subplot(122, projection='3d')
        ax2.set_title("Trajectory Only")

        for energy_key, info in ENERGY_MAPPING.items():
            color = info['color']
            all_files = data_paths.get(energy_key, {}).get(model, {}).get('pos', [])
            files_to_plot = all_files[:N_TRAJECTORIES_TO_PLOT]
            
            for file_path in files_to_plot:
                try:
                    data = pd.read_csv(file_path, sep=r'\s+', header=None, names=['x', 'y', 'z'])
                    for ax in [ax1, ax2]:
                        ax.scatter(data['x'], data['y'], data['z'], color=color, alpha=0.6, s=SCATTER_SIZE_3D)
                except Exception as e:
                    print(f"  -> WARNING: Could not process {file_path.name}: {e}")

        for ax in [ax1, ax2]:
            ax.scatter([0], [0], [0], color='black', s=50, label='Galactic Center', zorder=10)
            ax.scatter([-8.5], [0], [0], color='blue', s=40, label='Earth', zorder=10)
            ax.set_xlabel('X (kpc)'); ax.set_ylabel('Y (kpc)'); ax.set_zlabel('Z (kpc)')

        patches = [mpatches.Patch(color=info['color'], label=info['display_label']) for info in ENERGY_MAPPING.values()]
        patches.append(mpatches.Patch(color='blue', label='Earth'))
        patches.append(mpatches.Patch(color='black', label='Galactic Center'))
        ax2.legend(handles=patches, title="Energy", bbox_to_anchor=(1.05, 1), loc='upper left')

        output_filename = f"1_3D_Trajectory_{particle_display_name}_{model}.png"
        plt.savefig(OUTPUT_DIR / output_filename, bbox_inches='tight', dpi=150)
        plt.close(fig)
    print(" -> 3D Graphs saved")


def plot_2d_projection(data_paths, particle_display_name, data_type):
    plot_id = "2" if data_type == 'pos' else "3"
    title_suffix = "Total Projection (Pos.dat)" if data_type == 'pos' else "Galactic Plane (Plane.dat)"
    filename_suffix = "TotalProjection" if data_type == 'pos' else "GalacticPlane"
    
    # Usa o nome em inglês para os prints e títulos
    print(f"[{plot_id}/4] Making 2D graphs for {particle_display_name} ({title_suffix})...")

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 7), sharey=True)
    fig.suptitle(f'2D Trajectory for {particle_display_name} - {title_suffix}', fontsize=16)
    
    try:
        b_field_ass = np.loadtxt(MAGNETIC_FIELD_DIR / 'magneticvectorASSxy.dat')
        b_field_bss = np.loadtxt(MAGNETIC_FIELD_DIR / 'magneticvectorBSSxy.dat')
    except Exception as e:
        print(f"  -> WARNING: Was not possible to load the magnetic field data: {e}")
        b_field_ass, b_field_bss = None, None

    ax1.set_title('ASS Model')
    if b_field_ass is not None:
        ax1.quiver(b_field_ass[:, 0], b_field_ass[:, 1], b_field_ass[:, 2]*1e10, b_field_ass[:, 3]*1e10, color='black', alpha=0.5, scale=1e2)
    ax2.set_title('BSS Model')
    if b_field_bss is not None:
        ax2.quiver(b_field_bss[:, 0], b_field_bss[:, 1], b_field_bss[:, 2]*1e10, b_field_bss[:, 3]*1e10, color='black', alpha=0.5, scale=1e2)

    for model, ax in zip(['ASS', 'BSS'], [ax1, ax2]):
        for energy_key, info in ENERGY_MAPPING.items():
            color = info['color']
            all_files = data_paths.get(energy_key, {}).get(model, {}).get(data_type, [])
            files_to_plot = all_files[:N_TRAJECTORIES_TO_PLOT]

            for file_path in files_to_plot:
                try:
                    data = pd.read_csv(file_path, sep=r'\s+', header=None, usecols=[0, 1], names=['x', 'y'])
                    ax.scatter(data['x'], data['y'], color=color, alpha=0.6, s=SCATTER_SIZE_2D)
                except Exception as e:
                    print(f"  -> WARNING: Unable to process {file_path.name}: {e}")

    patches = [mpatches.Patch(color=info['color'], label=info['display_label']) for info in ENERGY_MAPPING.values()]
    patches.append(mpatches.Patch(color='blue', label='Earth'))
    for ax in [ax1, ax2]:
        ax.scatter([-8.5], [0], color='blue', s=50, zorder=5, label='Earth')
        ax.set_xlabel('X (kpc)'); ax.set_ylabel('Y (kpc)')
        ax.grid(True); ax.set_aspect('equal', adjustable='box')
    
    ax2.legend(handles=patches, title="Energy", bbox_to_anchor=(1.02, 1), loc='upper left')
    
    output_filename = f"{plot_id}_2D_Trajectory_{particle_display_name}_{filename_suffix}.png"
    plt.savefig(OUTPUT_DIR / output_filename, bbox_inches='tight', dpi=150)
    plt.close(fig)
    print(f" -> Graphics {title_suffix} saved.")


def plot_larmor_radius(data_paths, particle_display_name):
    # Usa o nome em inglês para os prints e títulos
    print(f"[4/4] Making Larmor radius graphs for {particle_display_name}...")
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7), sharey=True)
    fig.suptitle(f'Larmor Radius vs. Time for {particle_display_name}', fontsize=16)

    axes = {'ASS': ax1, 'BSS': ax2}
    for model, ax in axes.items():
        ax.set_title(f'{model} Model')
        for energy_key, info in ENERGY_MAPPING.items():
            color = info['color']
            all_files = data_paths.get(energy_key, {}).get(model, {}).get('larmor', [])
            files_to_plot = all_files[:N_TRAJECTORIES_TO_PLOT]

            for file_path in files_to_plot:
                try:
                    data = pd.read_csv(file_path, sep=r'\s+', header=None, usecols=[0, 1], names=['time', 'radius'])
                    time_log = np.log10(data['time'] + 1e-12)
                    radius_log = np.log10(data['radius'].abs() + 1e-12)
                    ax.scatter(time_log, radius_log, color=color, s=2, alpha=0.8)
                except Exception as e:
                    print(f"  -> WARNING: Unable to process {file_path.name}: {e}")

    patches = [mpatches.Patch(color=info['color'], label=info['display_label']) for info in ENERGY_MAPPING.values()]
    for ax in [ax1, ax2]:
        ax.set_xlabel(r'$\log_{10}(Time [s])$')
        ax.set_ylabel(r'$\log_{10}(Larmor \ Radius [kpc])$')
        ax.grid(True)
        ax.legend(handles=patches, loc='best', title='Energy')
    
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    output_filename = f"4_Larmor_Radius_{particle_display_name}.png"
    plt.savefig(OUTPUT_DIR / output_filename, dpi=300)
    plt.close(fig)
    print(" -> Larmor radius graphs saved")


# --- BLOCO DE EXECUÇÃO PRINCIPAL ---
if __name__ == "__main__":
    print("Beginning the script")
    
    OUTPUT_DIR.mkdir(exist_ok=True)
    print(f"The graphs were saved in: {OUTPUT_DIR.resolve()}")

    # <<< ALTERAÇÃO CHAVE 2: Lógica de Tradução >>>
    # Pega o nome da pasta em português da configuração.
    particle_folder_name = TARGET_PARTICLE_FOLDER
    # Procura o nome de exibição em inglês no dicionário.
    # Se não encontrar, usa o nome da pasta como padrão para evitar erros.
    particle_display_name = PARTICLE_TRANSLATION_MAP.get(particle_folder_name, particle_folder_name)

    # A função de busca usa o nome da PASTA (português)
    all_files = find_data_files(BASE_DATA_DIR, particle_folder_name, ENERGY_MAPPING)

    if all_files:
        # As funções de plotagem usam o nome de EXIBIÇÃO (inglês)
        plot_3d_trajectories(all_files, particle_display_name)
        plot_2d_projection(all_files, particle_display_name, data_type='pos')
        plot_2d_projection(all_files, particle_display_name, data_type='plane')
        plot_larmor_radius(all_files, particle_display_name)
        
        # O print final também usa o nome em inglês
        print(f"\nAnalysis of '{particle_display_name}' completed! All graphs have been generated.")
    else:
        print(f"\nNo data files found for '{particle_display_name}'. Chart generation has been stopped.")