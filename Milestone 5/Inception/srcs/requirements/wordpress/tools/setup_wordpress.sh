#!/bin/bash
set -e

WP_PATH="/var/www/html"

if [ -f "$WORDPRESS_DB_PASSWORD_FILE" ]; then
    MYSQL_PASSWORD=$(cat "$WORDPRESS_DB_PASSWORD_FILE")
fi
 
if [ -f "$WORDPRESS_ADMIN_PASSWORD_FILE" ]; then
    WORDPRESS_ADMIN_PASSWORD=$(cat "$WORDPRESS_ADMIN_PASSWORD_FILE")
fi
 
if [ -f "$WORDPRESS_USER_PASSWORD_FILE" ]; then
    WORDPRESS_USER_PASSWORD=$(cat "$WORDPRESS_USER_PASSWORD_FILE")
fi

while ! mariadb-admin ping -h"$MYSQL_HOST" -u"$MYSQL_USER" -p"$MYSQL_PASSWORD" --silent; do
    sleep 2
done

if [ ! -f "$WP_PATH/wp-config.php" ]; then
    echo "Configurazione automatica di WordPress con WP-CLI..."

    wp core download --path="$WP_PATH" --allow-root

    wp config create \
        --path="$WP_PATH" \
        --dbname="$MYSQL_DATABASE" \
        --dbuser="$MYSQL_USER" \
        --dbpass="$MYSQL_PASSWORD" \
        --dbhost="$MYSQL_HOST" \
        --allow-root

    wp core install \
        --path="$WP_PATH" \
        --url="https://$DOMAIN_NAME" \
        --title="$WORDPRESS_TITLE" \
        --admin_user="$WORDPRESS_ADMIN_USER" \
        --admin_password="$WORDPRESS_ADMIN_PASSWORD" \
        --admin_email="$WORDPRESS_ADMIN_EMAIL" \
        --skip-email \
        --allow-root

    wp user create \
        "$WORDPRESS_USER" \
        "$WORDPRESS_USER_EMAIL" \
        --path="$WP_PATH" \
        --role=author \
        --user_pass="$WORDPRESS_USER_PASSWORD" \
        --allow-root

    chown -R www-data:www-data "$WP_PATH"
fi

exec "$@"