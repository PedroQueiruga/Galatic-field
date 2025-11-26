import pandas as pd
import numpy as np
from pathlib import Path

# --- 1. Main Configuration ---

ROOT_DIRECTORY = Path("../Simulacoes_Resultados/")

# Prefixo para os arquivos de trajetória (posição)
TRAJECTORY_FILE_PREFIX = "Pos"

# Prefixo para os arquivos de METADADOS
METADATA_FILE_PREFIX = "data" 

# !!! LÓGICA SIMPLIFICADA !!!
# Agora procuramos apenas pela string de SUCESSO.
# Verifique se o número de asteriscos está exato.
ESCAPE_SUCCESS_KEYWORD = "**********ESCAPE THE GALATIC HALO**********"


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


# --- 2. Função de Verificação de Escape (Lógica Simplificada) ---

def check_escape_status(metadata_file_path):
    """
    Verifica se a partícula escapou.
    Retorna True (Escapou) se a keyword de SUCESSO for encontrada.
    Retorna False (Não Escapou) caso contrário.
    """
    try:
        # Usando 'latin-1' para corrigir o erro de 'codec'
        with open(metadata_file_path, 'r', encoding='latin-1') as f:
            content = f.read()
            
            # *** LÓGICA SIMPLIFICADA ***
            # Retorna True apenas se a string de sucesso exata for encontrada.
            if ESCAPE_SUCCESS_KEYWORD in content:
                return True
            else:
                return False # Não encontrou a string de sucesso
            
    except Exception as e:
        # Se o arquivo não puder ser lido, tratamos como falha.
        print(f"    ERRO: Não foi possível ler {metadata_file_path}: {e}")
        return False

# --- 3. File Processing Function (Sem alterações) ---

def calculate_distance_between_points(file_path):
    """
    Reads a single (x, y, z) file and calculates the Euclidean
    distance between the first and last point.
    """
    try:
        df = pd.read_csv(file_path, sep=r'\s+', header=None,
                         names=['x', 'y', 'z'])
        
        if len(df) < 2:
            return None 

        linha_inicial = df.iloc[0]
        linha_final = df.iloc[-1]

        delta_x = linha_final['x'] - linha_inicial['x']
        delta_y = linha_final['y'] - linha_inicial['y']
        delta_z = linha_final['z'] - linha_inicial['z']

        distancia = np.sqrt(delta_x**2 + delta_y**2 + delta_z**2)
        
        return distancia

    except Exception as e:
        return None

# --- 4. Final Summary Display Function (Correção do 'KeyError') ---

def display_summary_table(results_list, particle_order, energy_order):
    """
    Creates and prints a pivot table from the collected results.
    """
    if not results_list:
        print("No data was successfully processed. Summary table is empty.")
        return

    summary_df = pd.DataFrame(results_list)

    # --- Format the 'Result' string (e.g., "Mean ± SEM") ---
    def format_result(row):
        if pd.isna(row['Media']):
            return "N/A"
        
        mean_str = f"{row['Media']:.4f}"
        
        if pd.isna(row['Erro']):
            sem_str = ""
        else:
            sem_str = f" ± {row['Erro']:.4f}"
            
        return f"{mean_str}{sem_str} (N={row['N']})"

    summary_df['Resultado_Formatado'] = summary_df.apply(format_result, axis=1)

    # --- Create the Pivot Table ---
    
    # Correção do erro de digitação ('EnergIA' -> 'Energia')
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
        print(" FINAL RESULTS - MEAN EUCLIDEAN DISTANCE (kpc) [Mean ± SEM (N)]")
        print(" (Filtered for Escaped Particles Only)")
        print("#"*70)
        print(final_table.to_string())

    except Exception as e:
        print(f"\nError creating pivot table: {e}")
        print("--- Raw Data ---")
        print(summary_df)


# --- 5. Main Execution (Sem alterações na lógica do loop) ---

if __name__ == "__main__":
    
    print("--- Starting Euclidean Distance Calculation (Mean ± SEM) ---")
    print(f"--- Filtering for SUCCESS keyword: '{ESCAPE_SUCCESS_KEYWORD}' ---")
    
    summary_results_list = []

    for energy in ENERGIES:
        print(f"\n========================================")
        print(f"Processing Energy: {energy}")
        print(f"========================================")

        for particle in PARTICLES:
            print(f"\n  Analyzing Particle: {particle}")
            
            current_path = ROOT_DIRECTORY / energy / particle
            
            if not current_path.exists():
                print(f"    WARNING: Path not found: {current_path}")
                continue 
            
            for model in MODELS:
                
                # 1. Procurar arquivos de METADADOS
                metadata_pattern = f"{METADATA_FILE_PREFIX}_{model}_*.dat"
                metadata_file_list = list(current_path.glob(metadata_pattern))

                if not metadata_file_list:
                    print(f"    Model {model}: No metadata files matching '{metadata_pattern}' found.")
                    summary_results_list.append({
                        'Energia': energy, 'Particula': particle, 'Modelo': model, 
                        'Media': np.nan, 'Erro': np.nan, 'N': 0
                    })
                    continue

                calculated_distances = []
                num_escaped = 0
                num_failed = 0 
                
                for metadata_file in metadata_file_list:
                    
                    # 2. Verifica o status de escape (LÓGICA SIMPLIFICADA)
                    if check_escape_status(metadata_file):
                        num_escaped += 1
                    else:
                        num_failed += 1
                        continue 
                    
                    # 3. Se escapou, encontre o arquivo 'Pos'
                    pos_file_name = metadata_file.name.replace(
                        METADATA_FILE_PREFIX, TRAJECTORY_FILE_PREFIX, 1
                    )
                    pos_file_path = metadata_file.parent / pos_file_name
                    
                    if not pos_file_path.exists():
                        print(f"    WARNING: Found escaped particle {metadata_file.name}, but missing Pos file: {pos_file_name}")
                        continue
                        
                    # 4. Calcule a distância
                    distancia = calculate_distance_between_points(pos_file_path)
                    if distancia is not None:
                        calculated_distances.append(distancia)
                
                # --- Calcular estatísticas ---
                num_files = len(calculated_distances) 
                mean_distance = np.nan
                std_err_mean = np.nan

                print(f"    Model {model}: Found {len(metadata_file_list)} total particles. {num_escaped} escaped, {num_failed} failed.")

                if num_files > 1:
                    mean_distance = np.mean(calculated_distances)
                    std_dev = np.std(calculated_distances, ddof=1)
                    std_err_mean = std_dev / np.sqrt(num_files)
                    
                    print(f"    -> Result: {mean_distance:.4f} ± {std_err_mean:.4f} kpc (N={num_files})")
                
                elif num_files == 1:
                    mean_distance = calculated_distances[0]
                    print(f"    -> Result: {mean_distance:.4f} kpc (Only N=1, no SEM)")
                
                else:
                    print(f"    -> Result: No valid data processed.")
                
                if num_files > 0 and num_files < num_escaped:
                    print(f"    (Note: {num_escaped - num_files} escaped particles were skipped due to missing/invalid Pos files)")
                
                summary_results_list.append({
                    'Energia': energy, 
                    'Particula': particle, 
                    'Modelo': model, 
                    'Media': mean_distance, 
                    'Erro': std_err_mean, 
                    'N': num_files
                })

    # --- 6. Final Summary Printout ---
    display_summary_table(summary_results_list, PARTICLES, ENERGIES)