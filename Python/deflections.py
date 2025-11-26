import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import cartopy.crs as ccrs
from pathlib import Path

# --- 1. CONFIGURAÇÃO PRINCIPAL ---
ROOT_DIRECTORY = Path("../Simulacoes_Resultados/")
ENERGIES = [
    "Energia_1_0E18",
    "Energia_1_0E19",
    "Energia_1_0E20",
]
PARTICLES = [
    "Proton",
    "Helio",
    "Nitrogenio", 
    "Aluminio",
    "Ferro"
]
MODELS = ["ASS", "BSS"]

PARTICLE_NAMES_EN = {
    "Proton": "Proton",
    "Helio": "Helium",
    "Nitrogenio": "Nitrogen",
    "Aluminio": "Aluminum",
    "Ferro": "Iron"
}

ENERGY_LABELS = {
    "Energia_1_0E18": "1 EeV",
    "Energia_1_0E19": "10 EeV",
    "Energia_1_0E20": "100 EeV"
}

P_TERRA_KPC = np.array([-8.5, 0, 0])

# --- 2. Funções de Processamento ---

def esferica_para_cartesiana(r, theta_deg, phi_deg):
    theta_rad = np.deg2rad(theta_deg)
    phi_rad = np.deg2rad(phi_deg)
    x = r * np.sin(theta_rad) * np.cos(phi_rad)
    y = r * np.sin(theta_rad) * np.sin(phi_rad)
    z = r * np.cos(theta_rad)
    return np.array([x, y, z])

def cartesiana_para_esferica(x, y, z):
    r = np.sqrt(x**2 + y**2 + z**2)
    if r == 0:
        return 0, 0, 0
    theta_rad = np.arccos(z / r)
    phi_rad = np.arctan2(y, x)
    theta_deg = np.rad2deg(theta_rad)
    phi_deg = np.rad2deg(phi_rad)
    if phi_deg < 0:
        phi_deg += 360
    return r, theta_deg, phi_deg

def calculate_deflection_angle(theta_i_deg, phi_i_deg, theta_f_deg, phi_f_deg):
    theta_i_rad, phi_i_rad = np.deg2rad(theta_i_deg), np.deg2rad(phi_i_deg)
    theta_f_rad, phi_f_rad = np.deg2rad(theta_f_deg), np.deg2rad(phi_f_deg)
    v_initial = np.array([np.sin(theta_i_rad)*np.cos(phi_i_rad), np.sin(theta_i_rad)*np.sin(phi_i_rad), np.cos(theta_i_rad)])
    v_final = np.array([np.sin(theta_f_rad)*np.cos(phi_f_rad), np.sin(theta_f_rad)*np.sin(phi_f_rad), np.cos(theta_f_rad)])
    dot_product = np.clip(np.dot(v_initial, v_final), -1.0, 1.0)
    angle_rad = np.arccos(dot_product)
    return np.rad2deg(angle_rad)

def load_single_file(file_path):
    try:
        temp_df = pd.read_csv(file_path, sep=r'\s+', header=None,
                              names=['r', 'theta', 'phi'])
        if len(temp_df) != 2:
            return None

        theta_i_deg, phi_i_deg = temp_df.loc[0, 'theta'], temp_df.loc[0, 'phi']
        r_f, theta_f_deg, phi_f_deg = temp_df.loc[1, 'r'], temp_df.loc[1, 'theta'], temp_df.loc[1, 'phi']
        P_halo_cart = esferica_para_cartesiana(r_f, theta_f_deg, phi_f_deg)
        V_visada_cart = P_halo_cart - P_TERRA_KPC
        r_visada, theta_f_novo, phi_f_novo = cartesiana_para_esferica(
            V_visada_cart[0], V_visada_cart[1], V_visada_cart[2]
        )
        deflection_angle = calculate_deflection_angle(theta_i_deg, phi_i_deg, theta_f_novo, phi_f_novo)
        
        data = pd.DataFrame({
            'filename':      [file_path.name],
            'deflection':    [deflection_angle],
            'theta_initial': [theta_i_deg], 'phi_initial':   [phi_i_deg],
            'theta_final':   [theta_f_novo], 'phi_final':     [phi_f_novo]
        })

        data['lat_initial'] = 90 - data['theta_initial']
        data['lat_final'] = 90 - data['theta_final']
        data['lon_initial'] = data['phi_initial'].apply(lambda x: x - 360 if x > 180 else x)
        data['lon_final'] = data['phi_final'].apply(lambda x: x - 360 if x > 180 else x)
        return data

    except Exception as e:
        print(f"ERRO ao processar o arquivo '{file_path.name}': {e}")
        return None

def process_all_files_for_model(base_dir, model_name):
    file_pattern = f"deflection_{model_name}_*.dat"
    all_dataframes = []
    for file_path in base_dir.glob(file_pattern):
        single_df = load_single_file(file_path)
        if single_df is not None:
            all_dataframes.append(single_df)
    if not all_dataframes: return None
    return pd.concat(all_dataframes, ignore_index=True)

def plot_on_axis(ax, data, title):
    ax.set_extent([-180, 180, -90, 90], crs=ccrs.PlateCarree())
    ax.gridlines(draw_labels=True, dms=False, x_inline=False, y_inline=False)
    ax.set_title(title, fontsize=16)
    if data is not None:
        for index, row in data.iterrows():
            lon_i, lat_i, lon_f, lat_f = row['lon_initial'], row['lat_initial'], row['lon_final'], row['lat_final']
            ax.arrow(x=lon_i, y=lat_i, dx=(lon_f - lon_i), dy=(lat_f - lat_i),
                      color='red', width=0.1, head_width=0.4,
                      transform=ccrs.PlateCarree(), zorder=2)
            ax.scatter(lon_i, lat_i, color='blue', marker='o', s=20, 
                       edgecolor='black', transform=ccrs.PlateCarree(), zorder=3)
            ax.scatter(lon_f, lat_f, color='green', marker='x', s=30, 
                       linewidth=1.5, transform=ccrs.PlateCarree(), zorder=4)

def create_comparison_map(data_dict, particle, energy):
    # --- MODIFICAÇÃO: Usar dicionários para obter nome em Inglês e Energia abreviada ---
    particle_label = PARTICLE_NAMES_EN.get(particle, particle)
    energy_label = ENERGY_LABELS.get(energy, energy)
    
    fig, axes = plt.subplots(1, 2, figsize=(20, 8), subplot_kw={'projection': ccrs.Robinson()})
    
    # Título do gráfico atualizado
    fig.suptitle(f"Deflections: {particle_label} ({energy_label})", fontsize=20)
    
    plot_on_axis(axes[0], data_dict.get(MODELS[0]), f"Modelo {MODELS[0]}")
    plot_on_axis(axes[1], data_dict.get(MODELS[1]), f"Modelo {MODELS[1]}")
    output_filename = f"mapa_comparativo_{particle}_{energy}.png"
    plt.savefig(output_filename, bbox_inches='tight', dpi=150)
    print(f"-> Gráfico salvo como: {output_filename}")
    plt.close(fig)

# --- 3. Funções de Exibição (Sem alterações na lógica) ---

def display_deflection_summary(results_list, particle_order, energy_order):
    if not results_list:
        print("Nenhum dado foi processado com sucesso. A tabela final está vazia.")
        return
    
    summary_df = pd.DataFrame(results_list)

    def format_result_with_comma(row):
        if row['N_Amostras'] == 0 or pd.isna(row['Deflexao_Media_graus']):
            return "N/A"
        mean_str = f"{row['Deflexao_Media_graus']:.4f}".replace('.', ',')
        if pd.isna(row['Deflexao_Erro_graus']):
            sem_str = ""
        else:
            sem_str = f" ± {row['Deflexao_Erro_graus']:.4f}".replace('.', ',')
        n_str = f" (N={row['N_Amostras']})"
        return f"{mean_str}{sem_str}{n_str}"

    summary_df['Resultado_Formatado'] = summary_df.apply(format_result_with_comma, axis=1)
    summary_df['Energia'] = pd.Categorical(summary_df['Energia'], categories=energy_order, ordered=True)
    summary_df['Particula'] = pd.Categorical(summary_df['Particula'], categories=particle_order, ordered=True)
    
    try:
        final_table = summary_df.pivot_table(
            index=['Energia', 'Particula'], 
            columns='Modelo', 
            values='Resultado_Formatado',
            aggfunc='first'
        )
        print("\n\n" + "#"*70)
        print(" ANÁLISE CONCLUÍDA - TABELA-RESUMO FINAL [Média (graus) ± Erro (N)]")
        print(" (Separador decimal é vírgula)")
        print("#"*70)
        print(final_table.to_string())

    except Exception as e:
        print(f"\nERRO ao criar tabela pivô: {e}")
        print(summary_df)


# --- 4. Execução Principal ---

if __name__ == "__main__":
    summary_results = [] 
    print("--- INICIANDO PIPELINE DE ANÁLISE AUTOMATIZADA ---")
    
    for energy in ENERGIES:
        for particle in PARTICLES:
            print("\n" + "="*60)
            print(f"Processando: Energia={energy}, Partícula={particle}")
            print("="*60)
            
            current_path = ROOT_DIRECTORY / energy / particle
            if not current_path.exists():
                print(f"AVISO: Pasta não encontrada, pulando: {current_path}")
                continue
                
            all_model_data = {}
            
            for model in MODELS:
                print(f"\nAnalisando modelo: {model}")
                model_data = process_all_files_for_model(current_path, model)
                
                if model_data is not None:
                    num_amostras = len(model_data)
                    print(f"  - Processadas {num_amostras} deflexões VÁLIDAS.")
                    
                    mean_deflection = model_data['deflection'].mean()
                    sem_deflection = np.nan
                    if num_amostras > 1:
                        std_dev = np.std(model_data['deflection'], ddof=1)
                        sem_deflection = std_dev / np.sqrt(num_amostras)
                    
                    all_model_data[model] = model_data
                    
                    summary_results.append({
                        'Energia': energy, 
                        'Particula': particle, 
                        'Modelo': model, 
                        'Deflexao_Media_graus': mean_deflection,
                        'Deflexao_Erro_graus': sem_deflection,
                        'N_Amostras': num_amostras
                    })
                    
                else:
                    print("  - Nenhum arquivo VÁLIDO encontrado.")
                    summary_results.append({
                        'Energia': energy, 
                        'Particula': particle, 
                        'Modelo': model, 
                        'Deflexao_Media_graus': np.nan,
                        'Deflexao_Erro_graus': np.nan,
                        'N_Amostras': 0
                    })
                    
            if all_model_data:
                create_comparison_map(all_model_data, particle, energy)
                
    display_deflection_summary(summary_results, PARTICLES, ENERGIES)