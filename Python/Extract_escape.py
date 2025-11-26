import os
import re # Importar o módulo de expressões regulares

def gerar_nome_arquivo(tipo_arquivo, numero_simulacao, energia="1_0E15"):
    """
    Gera o nome completo do arquivo com base no tipo e número da simulação.
    Ex: data_ASS_Sim01_E1_0E16_P2.dat
    """
    # Garante que o número da simulação tenha dois dígitos (ex: 1 -> 01, 10 -> 10)
    num_formatado = f"{numero_simulacao:02d}"
    return f"data_{tipo_arquivo}_Sim{num_formatado}_E{energia}_P8.dat"

def extrair_dados_raio_cosmico_ajustado(diretorio_arquivos, num_arquivos=10):
    """
    Extrai o Escape_time (plane) e o Tempo de Propagação de arquivos de dados
    de raios cósmicos com um padrão de nome de arquivo específico e os formata
    para importação no Excel, usando vírgula como separador decimal.
    A ordem das colunas é: Tipo, Número da Simulação, Escape_time (plane), Tempo de Propagação.

    Args:
        diretorio_arquivos (str): O caminho para o diretório onde os arquivos de dados estão localizados.
        num_arquivos (int): O número de arquivos para cada tipo (ASS e BSS).

    Returns:
        str: Uma string formatada com os cabeçalhos e os dados extraídos,
             pronta para ser copiada e colada no Excel.
    """

    dados_ass = []
    dados_bss = []

    for i in range(1, num_arquivos + 1):
        # --- Processar arquivos ASS ---
        nome_arquivo_ass = os.path.join(diretorio_arquivos, gerar_nome_arquivo("ASS", i))
        try:
            with open(nome_arquivo_ass, 'r') as f:
                conteudo = f.read()
                tempo_propagacao = None
                escape_time_plane = None

                match_tp = re.search(r"Tempo de propagacao=(\d+\.\d+e[+-]\d+)\s*s", conteudo)
                if match_tp:
                    tempo_propagacao = float(match_tp.group(1))

                match_etp = re.search(r"Escape_time \(plane\)=(\d+\.\d+e[+-]\d+)\s*s", conteudo)
                if match_etp:
                    escape_time_plane = float(match_etp.group(1))

                if tempo_propagacao is not None and escape_time_plane is not None:
                    # Formatar com vírgula como separador decimal
                    tp_formatado = f"{tempo_propagacao:.6e}".replace('.', ',')
                    etp_formatado = f"{escape_time_plane:.6e}".replace('.', ',')
                    # Ordem alterada: Escape_time (plane) primeiro, depois Tempo de Propagação
                    dados_ass.append(f"ASS\t{i}\t{etp_formatado}\t{tp_formatado}")
                else:
                    dados_ass.append(f"ASS\t{i}\tERRO_LEITURA\tERRO_LEITURA")

        except FileNotFoundError:
            dados_ass.append(f"ASS\t{i}\tARQUIVO_NAO_ENCONTRADO\tARQUIVO_NAO_ENCONTRADO")
        except Exception as e:
            dados_ass.append(f"ASS\t{i}\tERRO_PROCESSAMENTO: {e}\tERRO_PROCESSAMENTO: {e}")

        # --- Processar arquivos BSS ---
        nome_arquivo_bss = os.path.join(diretorio_arquivos, gerar_nome_arquivo("BSS", i))
        try:
            with open(nome_arquivo_bss, 'r') as f:
                conteudo = f.read()
                tempo_propagacao = None
                escape_time_plane = None

                match_tp = re.search(r"Tempo de propagacao=(\d+\.\d+e[+-]\d+)\s*s", conteudo)
                if match_tp:
                    tempo_propagacao = float(match_tp.group(1))

                match_etp = re.search(r"Escape_time \(plane\)=(\d+\.\d+e[+-]\d+)\s*s", conteudo)
                if match_etp:
                    escape_time_plane = float(match_etp.group(1))

                if tempo_propagacao is not None and escape_time_plane is not None:
                    # Formatar com vírgula como separador decimal
                    tp_formatado = f"{tempo_propagacao:.6e}".replace('.', ',')
                    etp_formatado = f"{escape_time_plane:.6e}".replace('.', ',')
                    # Ordem alterada: Escape_time (plane) primeiro, depois Tempo de Propagação
                    dados_bss.append(f"BSS\t{i}\t{etp_formatado}\t{tp_formatado}")
                else:
                    dados_bss.append(f"BSS\t{i}\tERRO_LEITURA\tERRO_LEITURA")

        except FileNotFoundError:
            dados_bss.append(f"BSS\t{i}\tARQUIVO_NAO_ENCONTRADO\tARQUIVO_NAO_ENCONTRADO")
        except Exception as e:
            dados_bss.append(f"BSS\t{i}\tERRO_PROCESSAMENTO: {e}\tERRO_PROCESSAMENTO: {e}")

    # Combinar os dados: ASS primeiro, depois BSS
    # Cabeçalho atualizado para refletir a nova ordem
    dados_completos = ["Tipo_Arquivo\tNumero_Simulacao\tEscape_Time_Plane_s\tTempo_Propagacao_s"]
    dados_completos.extend(dados_ass)
    dados_completos.extend(dados_bss)

    return "\n".join(dados_completos)

# --- Como usar o script ---
# Altere esta variável para o caminho do seu diretório de arquivos.
diretorio_dos_seus_arquivos = r"C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados\Energia_1_0E15\Ferro"

dados_para_excel = extrair_dados_raio_cosmico_ajustado(diretorio_dos_seus_arquivos)

print("Copie o texto abaixo e cole diretamente em uma planilha do Excel:")
print("--------------------------------------------------")
print(dados_para_excel)
print("--------------------------------------------------")

# Salvar os dados em um arquivo .tsv (tab-separated values)
nome_arquivo_saida = "dados.tsv"
with open(nome_arquivo_saida, "w") as f:
    f.write(dados_para_excel)
print(f"\nOs dados também foram salvos em '{nome_arquivo_saida}' no mesmo diretório do script.")