#!/bin/bash

CUB3D_EXEC="./cub3D"
VALID_DIR="maps/valid"
INVALID_DIR="maps/invalid"
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

echo "🔍 Testando mapas válidos:"
for map in "$VALID_DIR"/*.cub; do
    $CUB3D_EXEC "$map" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}[OK]${NC} $map"
    else
        echo -e "${RED}[FAIL]${NC} $map deveria ser válido"
    fi
done

echo ""
echo "🛑 Testando mapas inválidos:"
for map in "$INVALID_DIR"/*.cub; do
    $CUB3D_EXEC "$map" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${GREEN}[OK]${NC} $map"
    else
        echo -e "${RED}[FAIL]${NC} $map deveria ser inválido"
    fi
done
