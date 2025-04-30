# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    command_git_essentials                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 12:25:03 by hmateque          #+#    #+#              #
#    Updated: 2025/04/25 12:25:03 by hmateque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Git Guide para o Projeto cub3D

Este guia resume os principais comandos e práticas do Git que vocês vão usar durante o projeto cub3D.

---

## 📦 Inicialização e Configuração

```bash
git init              # Inicia um repositório Git na pasta atual
git clone <url>       # Clona um repositório remoto

# Configuração inicial
git config user.name "Seu Nome"
git config user.email "seuemail@42.fr"
```

## 📁 Controle de Versão Básico

```bash
git status            # Mostra o status dos arquivos (modificados, não rastreados, etc.)
git add <arquivo>     # Adiciona um arquivo para staging
git add .             # Adiciona tudo

git commit -m "mensagem"    # Cria um commit com os arquivos adicionados

git log               # Mostra o histórico de commits
```

## 🌿 Trabalhando com Branches

```bash
git branch            # Lista todas as branches
git branch <nome>     # Cria uma nova branch
git checkout <nome>   # Muda para a branch
git switch <nome>     # Alternativa moderna ao checkout

# Criar e mudar de branch ao mesmo tempo:
git checkout -b nova-feature
```

## 🔀 Merge e Rebase

```bash
git merge <branch>         # Junta a branch atual com <branch>
git rebase <branch>        # Reaplica commits da branch atual em cima da <branch>

Exemplo:
git checkout main
git merge desenvolvimento

```

## 🧪 Corrigindo Erros e Recuperando

```bash
git restore <arquivo>      # Desfaz mudanças não commitadas
git reset HEAD <arquivo>   # Remove do stage (git add)
git checkout -- <arquivo>  # Volta ao último commit

git revert <hash>          # Reverte um commit específico
git reset --hard <hash>    # CUIDADO! Reseta tudo até aquele commit

git clean -fd              # Remove arquivos não rastreados
```

## 📤 Trabalhando com Repositórios Remotos

```bash
git remote -v              # Lista os repositórios remotos
git push origin <branch>   # Envia as alterações para o repositório remoto
git pull origin <branch>   # Atualiza o repositório local

# Clonar um projeto remoto e subir uma branch
git clone <url>
cd projeto
git checkout -b nova-branch
```

## 🧠 Dicas de Colaboração
Commitem com frequência, mas só com coisas que funcionam.

Escrevam mensagens de commit claras.

Antes de começar a trabalhar, sempre:
```bash
git pull origin main
```
Ao terminar uma funcionalidade:
```bash
git push origin sua-branch
```
Para revisar e testar antes de unir ao main, use pull requests no GitHub.

## 🔍 Visualização e Diagnóstico
```bash
git diff                # Mostra as mudanças nos arquivos
git diff --staged       # Mostra as mudanças que vão ser commitadas
git log --oneline --graph --all  # Visualização do histórico com grafo
```

## 🧰 Extras úteis
```bash
git stash               # Salva alterações temporariamente
git stash pop           # Recupera alterações do stash

git blame <arquivo>     # Mostra quem modificou cada linha
```

## 💡 Exemplos rápidos

```bash
# Criar uma branch nova e trabalhar nela
git checkout -b mapa-parse
# Edita, testa...
git add .
git commit -m "Parser básico do mapa implementado"
git push origin mapa-parse

# Junta no main depois de testar
git checkout main
git pull origin main
git merge mapa-parse
git push origin main
```