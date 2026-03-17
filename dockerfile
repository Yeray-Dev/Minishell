# Imagen base ligera
FROM debian:stable-slim

# Instalar dependencias necesarias para compilar y probar minishell
RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    git \
    valgrind \
    python3 \
    python3-pip \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Instalar norminette
RUN pip3 install norminette --break-system-packages

# Carpeta del proyecto dentro del contenedor
WORKDIR /minishell

# Copiar todos los archivos del proyecto
COPY . .