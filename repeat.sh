#!/bin/bash

# --- 1. Configurações Globais ---
CRsExecutable="./CRs"          # Executável C++ no Linux
InputFile="input.dat"          # Nome do ficheiro de input
InputTemplate="input_template.dat" # Nome do nosso novo molde

OutputFiles=(                  # Nomes dos ficheiros de saída
    "Pos.dat"
    "larmor.dat"
    "data.dat"
    "plane.dat"
    "desvio.dat"
    "deflection.dat"
)

BaseOutputDirectory="Simulacoes_Resultados" # Pasta raiz para os resultados

# Mapeamento para nomes de Partículas (Associative Array em Bash)
declare -A SpecieNames
SpecieNames["1"]="Proton"
SpecieNames["2"]="Helio"
SpecieNames["3"]="Carbono"
SpecieNames["4"]="Nitrogenio"
SpecieNames["5"]="Oxigenio"
SpecieNames["6"]="Aluminio"
SpecieNames["7"]="Silicio"
SpecieNames["8"]="Ferro"
SpecieNames["9"]="Eletron"

# Mapeamento para nomes de Modelos
declare -A ModelNames
ModelNames["0"]="ASS"
ModelNames["1"]="BSS"

# --- 2. Parâmetros a Variar (Ranges) ---
TargetSpecies=("1" "2" "4" "6" "8")
TargetModels=("0" "1")
Energies=("1.0e18" "1.0e19")
NumberOfParticlesPerCondition=30

# --- PARÂMETROS FIXOS ---
FixedStep="1.0e7"
FixedTurbulence="0"
FixedMapping="0"
FixedPosition0="-8.5"
FixedPosition1="0"
FixedPosition2="0"

# --- 3. Criação da Pasta Raiz de Saída ---
mkdir -p "$BaseOutputDirectory"
echo "A iniciar sequência de simulações. Resultados serão guardados em $BaseOutputDirectory"

# --- 4. Loop Principal sobre as Energias ---
for energy in "${Energies[@]}"; do
    energyFormatted=$(echo "$energy" | sed 's/\./_/g' | sed 's/e/E/g')
    energyDirectory="$BaseOutputDirectory/Energia_$energyFormatted"
    mkdir -p "$energyDirectory"

    # --- 5. Loop sobre as Espécies de Partículas ---
    for specieID in "${TargetSpecies[@]}"; do
        specieName=${SpecieNames[$specieID]}
        specieDirectory="$energyDirectory/$specieName"
        mkdir -p "$specieDirectory"

        # --- 6. Loop para o Número de Partículas ---
        for (( particleIndex=1; particleIndex<=NumberOfParticlesPerCondition; particleIndex++ )); do
            
            # --- 7. Loop sobre os Modelos ---
            for modelID in "${TargetModels[@]}"; do
                modelName=${ModelNames[$modelID]}

                echo ""
                echo "--- A processar: E=$energy, Partícula=$specieName, Modelo=$modelName, Iteração=$particleIndex ---"

                # --- 8. Criar o ficheiro input.dat ---
                # Construir a linha de dados que irá substituir o marcador
                dataLine="$specieID $modelID $FixedTurbulence $FixedMapping $energy $FixedStep $FixedPosition0 $FixedPosition1 $FixedPosition2"
                # Usar 'sed' para substituir o marcador no molde e criar o input.dat
                sed "s/__DATALINE__/$dataLine/" "$InputTemplate" > "$InputFile"

                # --- 9. Executar o programa C++ ---
                echo "A executar $CRsExecutable..."
                $CRsExecutable

                # --- 10. Renomear e Mover Ficheiros de Saída ---
                for file in "${OutputFiles[@]}"; do
                    if [ -f "$file" ]; then
                        # Formatar o índice da partícula com um zero à esquerda (ex: 01, 02...)
                        pIndexFormatted=$(printf "%02d" $particleIndex)
                        
                        # Extrair o nome base do ficheiro (ex: "Pos" de "Pos.dat")
                        baseName=$(basename "$file" .dat)
                        
                        # Gerar o novo nome do ficheiro
                        newFileName="${baseName}_${modelName}_Sim${pIndexFormatted}_E${energyFormatted}_P${specieID}.dat"
                        destinationPath="$specieDirectory/$newFileName"

                        # Mover e renomear o ficheiro
                        mv "$file" "$destinationPath"
                        echo "  -> Resultado movido para $destinationPath"
                    fi
                done
                echo "Simulação concluída."

            done # Fim do loop de Modelos
        done # Fim do loop de Número de Partículas
    done # Fim do loop de Espécies
done # Fim do loop de Energias

echo ""
echo "Todas as simulações concluídas com sucesso!"
