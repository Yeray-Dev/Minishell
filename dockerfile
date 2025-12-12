# Imagen base ligera
FROM debian:stable-slim

# Instalar dependencias necesarias para compilar y probar minishell
RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    git \
    valgrind \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Carpeta del proyecto dentro del contenedor
WORKDIR /minishell

# Copiar todos los archivos del proyecto
COPY . .
