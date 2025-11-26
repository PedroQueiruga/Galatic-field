import os
import re

def gerar_nome_arquivo_desvio(tipo_simulacao, numero_simulacao, energia, tipo_particula="Proton"):
    """
    Gera o nome completo do arquivo de desvio com base nos parâmetros.
    Ex: desvio_ASS_Sim01_E1_0E14_P1.dat
    """
    # Garante que o número da simulação tenha dois dígitos (ex: 1 -> 01, 10 -> 10)
    num_formatado = f"{numero_simulacao:02d}"
    return f"desvio_{tipo_simulacao}_Sim{num_formatado}_E{energia}_P8.dat"

def extrair_ultimo_valor_coluna_meio(caminho_arquivo):
    """
    Extrai o último valor da coluna do meio de um arquivo de dados.
    Retorna o valor como float e None para erro, ou None e uma mensagem de erro.
    """
    try:
        with open(caminho_arquivo, 'r') as f:
            linhas = f.readlines()
            if not linhas:
                return None, "ARQUIVO_VAZIO"

            ultima_linha_valida = None
            for linha in reversed(linhas):
                if linha.strip(): # Encontra a primeira linha não vazia de trás para frente
                    ultima_linha_valida = linha.strip()
                    break
            
            if not ultima_linha_valida:
                return None, "ARQUIVO_SEM_DADOS_VALIDOS"

            # CORREÇÃO AQUI: era 'colunas.split()' e foi corrigido para 'ultima_linha_valida.split()'
            colunas = [col for col in ultima_linha_valida.split() if col]
            
            if len(colunas) < 2:
                return None, "ERRO_FORMATO_COLUNAS"
            
            return float(colunas[1]), None # Retorna o valor e nenhum erro
    
    except FileNotFoundError:
        return None, "ARQUIVO_NAO_ENCONTRADO"
    except ValueError: # Erro ao converter para float
        return None, "ERRO_VALOR_NUMERICO"
    except Exception as e:
        return None, f"ERRO_PROCESSAMENTO: {e}"

def extrair_desvio_multiplas_energias_simplificado(diretorio_raiz, energias, tipo_particula="Proton", num_arquivos=10):
    """
    Extrai o último valor da coluna do meio de arquivos de desvio para múltiplas energias,
    e os formata para importação no Excel, usando vírgula como separador decimal.
    Código simplificado com função auxiliar.
    """
    dados_completos = []
    dados_completos.append("Energia\tTipo_Arquivo\tNumero_Simulacao\tDesvio_Coluna_Meio")

    for energia_str in energias:
        # Constroi o caminho completo para a pasta da energia e tipo de partícula
        caminho_pasta_energia = os.path.join(diretorio_raiz, f"Energia_{energia_str}", tipo_particula)
        print(f"Processando arquivos para Energia: {energia_str} e Partícula: {tipo_particula}")

        tipos_simulacao = ["ASS", "BSS"]
        for tipo_sim in tipos_simulacao:
            for i in range(1, num_arquivos + 1):
                nome_arquivo = os.path.join(caminho_pasta_energia, gerar_nome_arquivo_desvio(tipo_sim, i, energia_str, tipo_particula))
                
                # Chama a função auxiliar para extrair o valor e verificar erros
                valor_desvio, erro = extrair_ultimo_valor_coluna_meio(nome_arquivo)
                
                if erro:
                    dados_completos.append(f"{energia_str}\t{tipo_sim}\t{i}\t{erro}")
                else:
                    # Formata o valor com vírgula e o adiciona à lista
                    valor_desvio_formatado = f"{valor_desvio:.6e}".replace('.', ',')
                    dados_completos.append(f"{energia_str}\t{tipo_sim}\t{i}\t{valor_desvio_formatado}")

    return "\n".join(dados_completos)

# --- Como usar o script ---
# Defina o diretório raiz que contém as pastas de energia
# Baseado no seu exemplo:
diretorio_base_simulacoes = r"C:\Users\User\OneDrive\RPG\Universidade\Mestrado\Dados_Dissertação\Dados_recentes (pós 24.09.2024)\Simulacoes_Resultados"

# Lista das energias que você deseja analisar (strings exatas dos nomes das pastas)
energias_para_analisar = ["1_0E15"]
particula = "Ferro" # O tipo de partícula que você está analisando

dados_para_excel = extrair_desvio_multiplas_energias_simplificado(
    diretorio_base_simulacoes,
    energias_para_analisar,
    tipo_particula=particula
)

print("Copie o texto abaixo e cole diretamente em uma planilha do Excel:")
print("--------------------------------------------------")
print(dados_para_excel)
print("--------------------------------------------------")

# Salvar os dados em um arquivo .tsv para facilitar a importação
nome_arquivo_saida = "desvio_raios_cosmicos_multi_energia_final.tsv"
with open(nome_arquivo_saida, "w") as f:
    f.write(dados_para_excel)
print(f"\nOs dados também foram salvos em '{nome_arquivo_saida}' no mesmo diretório do script.")