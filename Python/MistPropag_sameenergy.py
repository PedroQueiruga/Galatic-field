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
OUTPUT_DIR = PROJECT_ROOT / "Graficos_Gerados"

TARGET_ENERGY_STR = '1.0E17'
ENERGY_LABEL = '0.1 EeV'

N_TRAJECTORIES_TO_PLOT = 4 #Ajusta a quantidade de arquivos a ser processada por tipo de partícula

SCATTER_SIZE_3D = 1.5  # Tamanho dos pontos para os gráficos 3D
SCATTER_SIZE_2D = 2.0  # Tamanho dos pontos para os gráficos 2D

PARTICLE_MAPPING = {
    'Proton':     {'display_name': 'Proton',    'color': 'yellow'},
    'Helio':      {'display_name': 'Helium',    'color': 'green'},
    'Nitrogenio': {'display_name': 'Nitrogen',  'color': 'brown'},
    'Aluminio':   {'display_name': 'Aluminium', 'color': 'purple'},
    'Ferro':      {'display_name': 'Iron',      'color': 'cyan'}
}

# --- FIM DA CONFIGURAÇÃO ---


def find_data_files(base_dir, energy_str):
    print(f"Finding energy data: {energy_str} eV...")
    energy_folder_name = f"Energia_{energy_str.replace('.', '_')}"
    energy_dir = base_dir / "Simulacoes_Resultados" / energy_folder_name

    if not energy_dir.is_dir():
        print(f"--> ERROR: Energy directory not found: {energy_dir}")
        return None

    organized_data = {ptype_folder: {'ASS': {}, 'BSS': {}} for ptype_folder in PARTICLE_MAPPING.keys()}

    for ptype_folder in PARTICLE_MAPPING.keys():
        particle_dir = energy_dir / ptype_folder
        if not particle_dir.is_dir():
            print(f"--> WARNING: Particle directory not found '{ptype_folder}'. skipping.")
            continue

        organized_data[ptype_folder]['ASS']['pos'] = sorted(particle_dir.glob('Pos_ASS_*.dat'))
        organized_data[ptype_folder]['BSS']['pos'] = sorted(particle_dir.glob('Pos_BSS_*.dat'))
        organized_data[ptype_folder]['ASS']['larmor'] = sorted(particle_dir.glob('larmor_ASS_*.dat'))
        organized_data[ptype_folder]['BSS']['larmor'] = sorted(particle_dir.glob('larmor_BSS_*.dat'))
        organized_data[ptype_folder]['ASS']['plane'] = sorted(particle_dir.glob('plane_ASS_*.dat'))
        organized_data[ptype_folder]['BSS']['plane'] = sorted(particle_dir.glob('plane_BSS_*.dat'))

    print("Archives Found")
    return organized_data


def plot_3d_trajectories(data_paths, energy_label):
    print("[1/4] Plotting the 3D tragectory")
    for model in ["ASS", "BSS"]:
        fig = plt.figure(figsize=(18, 8))
        fig.suptitle(f'Galactic Propagation {model} - {energy_label}', fontsize=16)

        ax1 = fig.add_subplot(121, projection='3d')
        radius_sphere = 20
        u, v = np.mgrid[0:2*np.pi:100j, 0:np.pi:100j]
        x_s, y_s, z_s = radius_sphere * np.cos(u) * np.sin(v), radius_sphere * np.sin(u) * np.sin(v), radius_sphere * np.cos(v)
        ax1.plot_wireframe(x_s, y_s, z_s, color='lightblue', alpha=0.2)
        ax1.set_title("Trajectory with Galactic Halo")
        ax2 = fig.add_subplot(122, projection='3d')
        ax2.set_title("Trajecory without the Halo")

        for ptype_folder, info in PARTICLE_MAPPING.items():
            color = info['color']
            all_files = data_paths.get(ptype_folder, {}).get(model, {}).get('pos', [])
            files_to_plot = all_files[:N_TRAJECTORIES_TO_PLOT]

            for file_path in files_to_plot:
                try:
                    data = pd.read_csv(file_path, sep=r'\s+', header=None, names=['x', 'y', 'z'])
                    for ax in [ax1, ax2]:
                        # <<< ALTERAÇÃO AQUI: Trocado 'plot' por 'scatter' e usado o parâmetro 's' para o tamanho >>>
                        ax.scatter(data['x'], data['y'], data['z'], color=color, alpha=0.6, s=SCATTER_SIZE_3D)
                except Exception as e:
                    print(f"  -> AVISO: Não foi possível processar {file_path.name}: {e}")

        for ax in [ax1, ax2]:
            ax.scatter([0], [0], [0], color='black', s=50, label='Galactic Center', zorder=10)
            ax.scatter([-8.5], [0], [0], color='blue', s=40, label='Earth', zorder=10)
            ax.set_xlabel('X (kpc)'); ax.set_ylabel('Y (kpc)'); ax.set_zlabel('Z (kpc)')

        patches = [mpatches.Patch(color=info['color'], label=info['display_name']) for info in PARTICLE_MAPPING.values()]
        patches.append(mpatches.Patch(color='blue', label='Earth'))
        patches.append(mpatches.Patch(color='black', label='Galactic Center'))
        ax2.legend(handles=patches, bbox_to_anchor=(1.05, 1), loc='upper left')

        output_filename = f"1_3D_Trajectory_{model}_{energy_label.replace(' ', '')}.png"
        plt.savefig(OUTPUT_DIR / output_filename, bbox_inches='tight', dpi=150)
        plt.close(fig)
    print(" -> Graphics Saved")


def plot_2d_projection(data_paths, energy_label, data_type):
    plot_id = "2" if data_type == 'pos' else "3"
    title_suffix = "Total Projection (Pos.dat)" if data_type == 'pos' else "Galactic Plane (Plane.dat)"
    filename_suffix = "TotalProjection" if data_type == 'pos' else "GalacticPlane"

    print(f"[{plot_id}/4] Making the 2D projection graphs ({title_suffix})...")

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 7), sharey=True)
    fig.suptitle(f'2D Trajectory - {title_suffix} - {energy_label}', fontsize=16)

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
        for ptype_folder, info in PARTICLE_MAPPING.items():
            color = info['color']
            all_files = data_paths.get(ptype_folder, {}).get(model, {}).get(data_type, [])
            files_to_plot = all_files[:N_TRAJECTORIES_TO_PLOT]

            for file_path in files_to_plot:
                try:
                    data = pd.read_csv(file_path, sep=r'\s+', header=None, usecols=[0, 1], names=['x', 'y'])
                    # <<< ALTERAÇÃO AQUI: Trocado 'plot' por 'scatter' e usado o parâmetro 's' para o tamanho >>>
                    ax.scatter(data['x'], data['y'], color=color, alpha=0.6, s=SCATTER_SIZE_2D)
                except Exception as e:
                    print(f"  -> WARNING: Unable to process  {file_path.name}: {e}")

    patches = [mpatches.Patch(color=info['color'], label=info['display_name']) for info in PARTICLE_MAPPING.values()]
    patches.append(mpatches.Patch(color='blue', label='Earth'))
    for ax in [ax1, ax2]:
        ax.scatter([-8.5], [0], color='blue', s=50, zorder=5, label='Earth')
        ax.set_xlabel('X (kpc)'); ax.set_ylabel('Y (kpc)')
        ax.grid(True); ax.set_aspect('equal', adjustable='box')

    ax2.legend(handles=patches, bbox_to_anchor=(1.02, 1), loc='upper left', title='Particles')

    output_filename = f"{plot_id}_2D_Trajectory_{filename_suffix}_{energy_label.replace(' ', '')}.png"
    plt.savefig(OUTPUT_DIR / output_filename, bbox_inches='tight', dpi=150)
    plt.close(fig)
    print(f" -> Graphics {title_suffix} saved.")


def plot_larmor_radius(data_paths, energy_label):
    print("[4/4] Generating Larmor graphics")
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7), sharey=True)
    fig.suptitle(f'Larmor Radius vs. Time - {energy_label}', fontsize=16)

    axes = {'ASS': ax1, 'BSS': ax2}
    for model, ax in axes.items():
        ax.set_title(f'{model} Model')
        for ptype_folder, info in PARTICLE_MAPPING.items():
            color = info['color']
            all_files = data_paths.get(ptype_folder, {}).get(model, {}).get('larmor', [])
            files_to_plot = all_files[:N_TRAJECTORIES_TO_PLOT]

            for file_path in files_to_plot:
                try:
                    data = pd.read_csv(file_path, sep=r'\s+', header=None, usecols=[0, 1], names=['time', 'radius'])
                    time_log = np.log10(data['time'] + 1e-12)
                    radius_log = np.log10(data['radius'].abs() + 1e-12)
                    ax.scatter(time_log, radius_log, color=color, s=2, alpha=0.8)
                except Exception as e:
                    print(f"  -> AVISO: Não foi possível processar {file_path.name}: {e}")

    patches = [mpatches.Patch(color=info['color'], label=info['display_name']) for info in PARTICLE_MAPPING.values()]
    for ax in [ax1, ax2]:
        ax.set_xlabel(r'$\log_{10}(Time [s])$')
        ax.set_ylabel(r'$\log_{10}(Larmor \ Radius [kpc])$')
        ax.grid(True)
        ax.legend(handles=patches, loc='best', title='Particle Type')

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    output_filename = f"4_Larmor_Radius_{energy_label.replace(' ', '')}.png"
    plt.savefig(OUTPUT_DIR / output_filename, dpi=300)
    plt.close(fig)
    print(" -> Gráficos do Raio de Larmor salvos.")


# --- BLOCO DE EXECUÇÃO PRINCIPAL ---
if __name__ == "__main__":
    print("Initializing the unified script")

    OUTPUT_DIR.mkdir(exist_ok=True)
    print(f"The graphs will be saven in: {OUTPUT_DIR.resolve()}")

    all_files = find_data_files(BASE_DATA_DIR, TARGET_ENERGY_STR)

    if all_files:
        plot_3d_trajectories(all_files, ENERGY_LABEL)
        plot_2d_projection(all_files, ENERGY_LABEL, data_type='pos')
        plot_2d_projection(all_files, ENERGY_LABEL, data_type='plane')
        plot_larmor_radius(all_files, ENERGY_LABEL)

        print("\nAnalysis successfully completed! All graphs have been generated.")
    else:
        print("\nNo data files found. Chart generation has been stopped.")