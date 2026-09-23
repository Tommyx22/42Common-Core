#!/bin/bash

DOMAIN_NAME=${DOMAIN_NAME:-tolanini.42.fr}
SSL_DIR="/etc/nginx/ssl"
CRT_FILE="${SSL_DIR}/nginx.crt"
KEY_FILE="${SSL_DIR}/nginx.key"

mkdir -p "$SSL_DIR"

if [ ! -f "$CRT_FILE" ] || [ ! -f "$KEY_FILE" ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -out "$CRT_FILE" \
        -keyout "$KEY_FILE" \
        -subj "/C=IT/ST=Tuscany/L=Florence/O=42Florence/OU=tolanini/CN=${DOMAIN_NAME}"
    
    chmod 600 "$KEY_FILE"
    chmod 644 "$CRT_FILE"
fi

nginx -t

exec "$@"