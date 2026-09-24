#!/bin/bash
set -e

DATA_DIR="/var/lib/mysql"

if [ -f "$MYSQL_ROOT_PASSWORD_FILE" ]; then
    MYSQL_ROOT_PASSWORD=$(cat "$MYSQL_ROOT_PASSWORD_FILE")
fi
 
if [ -f "$MYSQL_PASSWORD_FILE" ]; then
    MYSQL_PASSWORD=$(cat "$MYSQL_PASSWORD_FILE")
fi

if [ ! -f "$DATA_DIR/.inception_initialized" ]; then
    echo "[MariaDB] Prima esecuzione rilevata: Inizializzazione dati e configurazione credenziali..."

    mkdir -p /var/run/mysqld "$DATA_DIR"
    chown -R mysql:mysql /var/run/mysqld "$DATA_DIR"

    mysql_install_db --user=mysql --datadir="$DATA_DIR" > /dev/null

    mysqld --user=mysql --bootstrap << EOF
USE mysql;
FLUSH PRIVILEGES;

ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';

CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;

CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';

FLUSH PRIVILEGES;
EOF

    touch "$DATA_DIR/.inception_initialized"

    echo "[MariaDB] Inizializzazione completata con successo."
else
    echo "[MariaDB] Volume persistente già esistente. Salto l'inizializzazione."
fi

echo "[MariaDB] Avvio di MariaDB in foreground..."
exec mysqld --user=mysql