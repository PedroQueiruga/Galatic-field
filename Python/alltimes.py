import pandas as pd
import numpy as np
from pathlib import Path

# 1. Main Configuration:

ROOT_DIRECTORY = Path("../Simulacoes_Resultados/")
METADATA_FILE_PREFIX = "data"

# O nome do arquivo excel que será salvo:
OUTPUT_FILENAME = "all_times.xlsx"

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
    "Ferro",
]

MODELS = ["ASS", "BSS"]

# 2. Data Extraction Function:

def extract_simulation_data(metadata_file_path):
    """
    Lê um arquivo de metadados e extrai os valores de tempo de interesse.
    Retorna um dicionário com os valores.
    """
    results = {
        'propagacao_anos': np.nan,
        'escape_anos': np.nan,
        'simulacao_min': np.nan
    }
    
    try:
        with open(metadata_file_path, 'r', encoding='latin-1') as f:
            for line in f:
                line = line.strip()
                
                # --- Extrai o Tempo de Propagação (anos) ---
                if line.startswith("Tempo de propagacao"):
                    try:
                        parts = line.split('=')
                        value_str = parts[-1].strip()
                        value_anos = value_str.split(' ')[0]
                        results['propagacao_anos'] = float(value_anos)
                    except (IndexError, ValueError):
                        print(f"    AVISO: Falha ao parsear 'Tempo de propagacao' em {metadata_file_path.name}")
                
                # --- Extrai o Tempo de Escape (anos) ---
                elif line.startswith("Escape_time (plane)"):
                    try:
                        parts = line.split('=')
                        value_str = parts[-1].strip()
                        value_anos = value_str.split(' ')[0]
                        results['escape_anos'] = float(value_anos)
                    except (IndexError, ValueError):
                        print(f"    AVISO: Falha ao parsear 'Escape_time' em {metadata_file_path.name}")
                
                # --- Extrai o Tempo de Simulação (min) ---
                elif line.startswith("Tempo da Simulação (min)"):
                    try:
                        parts = line.split(':')
                        value_str = parts[-1].strip()
                        # Adicionada verificação para valores não numéricos
                        if value_str:
                            results['simulacao_min'] = float(value_str)
                        # Se value_str for vazio, permanece np.nan
                    except (IndexError, ValueError):
                         print(f"    AVISO: Falha ao parsear 'Tempo da Simulação' em {metadata_file_path.name}")

        return results
        
    except Exception as e:
        print(f"    ERRO: Falha crítica ao ler {metadata_file_path.name}: {e}")
        return None # Retorna None se o arquivo não puder ser lido

# --- 3. Funções de Cálculo e Formatação de Stats ---

def calculate_stats(data_list):
    """
    Calcula Média, Erro Padrão (SEM) e N para uma lista de números.
    IGNORA valores NaN (nulos) no cálculo.
    """
    # Remove quaisquer valores NaN que possam ter vindo do parsing
    data_list = [v for v in data_list if not np.isnan(v)]
    
    n = len(data_list)
    
    if n == 0:
        return (np.nan, np.nan, 0)
    
    mean = np.mean(data_list)
    
    if n > 1:
        sem = np.std(data_list, ddof=1) / np.sqrt(n)
    else:
        sem = np.nan
        
    return (mean, sem, n)

def format_stat_string(mean, sem, n):
    """
    Formata os stats no formato 'Média ± Erro (N)'.
    """
    if n == 0 or np.isnan(mean):
        return "N/A"
    
    mean_str = f"{mean:.4f}"
    
    if n > 1 and not np.isnan(sem):
        sem_str = f" ± {sem:.4f}"
    else:
        sem_str = ""
        
    return f"{mean_str}{sem_str} (N={n})"


# --- 4. Função Final de Tabela e Exportação ---

def display_and_save_summary(results_list, particle_order, energy_order):
    """
    Cria a tabela de resumo, imprime no console e salva em Excel.
    """
    if not results_list:
        print("Nenhum dado foi processado com sucesso.")
        return

    summary_df = pd.DataFrame(results_list)

    summary_df['Energia'] = pd.Categorical(summary_df['Energia'], categories=energy_order, ordered=True)
    summary_df['Particula'] = pd.Categorical(summary_df['Particula'], categories=particle_order, ordered=True)
    
    try:
        final_table = summary_df.pivot_table(
            index=['Energia', 'Particula'], 
            columns='Modelo', 
            values=['Propagacao (anos)', 'Escape (anos)', 'Simulacao (min)'],
            aggfunc='first'
        )
        
        final_table = final_table.swaplevel(0, 1, axis=1).sort_index(axis=1)

        print("\n\n" + "#"*70)
        print(" FINAL RESULTS - SIMULATION TIME ANALYSIS (ALL FILES) [Mean ± SEM (N)]")
        print("#"*70)
        print(final_table.to_string())

        # --- Salvar em Excel ---
        final_table.to_excel(OUTPUT_FILENAME)
        
        print("\n" + "="*70)
        print(f"Resultados também salvos em: {OUTPUT_FILENAME}")
        print("="*70)

    except Exception as e:
        print(f"\nErro ao criar tabela final ou salvar Excel: {e}")
        print("Se for um erro de 'openpyxl', instale a biblioteca:")
        print("pip install openpyxl")


# --- 5. Main Execution (Lógica de Filtro Removida) ---

if __name__ == "__main__":
    
    print("--- Iniciando Análise de Tempo de Simulação (Média ± SEM) ---")
    print("--- Processando TODOS os arquivos de metadados encontrados ---")
    
    summary_results_list = []

    for energy in ENERGIES:
        print(f"\n========================================")
        print(f"Processando Energia: {energy}")
        print(f"========================================")

        for particle in PARTICLES:
            print(f"\n  Analisando Partícula: {particle}")
            
            current_path = ROOT_DIRECTORY / energy / particle
            
            if not current_path.exists():
                print(f"    AVISO: Caminho não encontrado: {current_path}")
                continue 
            
            for model in MODELS:
                
                metadata_pattern = f"{METADATA_FILE_PREFIX}_{model}_*.dat"
                metadata_file_list = list(current_path.glob(metadata_pattern))
                total_files = len(metadata_file_list)

                if total_files == 0:
                    print(f"    Modelo {model}: Nenhum arquivo de metadados encontrado.")
                    continue

                print(f"    Modelo {model}: Processando {total_files} arquivos.")

                # Listas para armazenar os valores brutos *deste grupo*
                propagacao_data = []
                escape_data = []
                simulacao_data = []
                
                for metadata_file in metadata_file_list:
                    
                    # 1. Extrai os dados (NÃO HÁ MAIS FILTRO)
                    data = extract_simulation_data(metadata_file)
                    
                    if data:
                        propagacao_data.append(data['propagacao_anos'])
                        escape_data.append(data['escape_anos'])
                        simulacao_data.append(data['simulacao_min'])
                
                # 2. Calcula as estatísticas para este grupo
                #    A função calculate_stats ignora NaNs internamente.
                prop_stats = calculate_stats(propagacao_data)
                esc_stats = calculate_stats(escape_data)
                sim_stats = calculate_stats(simulacao_data)
                
                # 3. Formata os resultados e armazena para a tabela final
                summary_results_list.append({
                    'Energia': energy, 
                    'Particula': particle, 
                    'Modelo': model,
                    # N em (N=...) será o N de valores NÃO-NULOS
                    'Propagacao (anos)': format_stat_string(prop_stats[0], prop_stats[1], prop_stats[2]),
                    'Escape (anos)': format_stat_string(esc_stats[0], esc_stats[1], esc_stats[2]),
                    'Simulacao (min)': format_stat_string(sim_stats[0], sim_stats[1], sim_stats[2])
                })

    # --- 6. Final Summary Printout & Save ---
    display_and_save_summary(summary_results_list, PARTICLES, ENERGIES)
