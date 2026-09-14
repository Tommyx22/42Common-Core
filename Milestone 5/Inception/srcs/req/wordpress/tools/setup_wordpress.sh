set -e

WP_PATH="/var/www/html"

if [ -n "$WORDPRESS_DB_PASSWORD_FILE" ] && [ -f "$WORDPRESS_DB_PASSWORD_FILE" ]; then
    WORDPRESS_DB_PASSWORD=$(cat "$WORDPRESS_DB_PASSWORD_FILE")
    export WORDPRESS_DB_PASSWORD
fi

echo "Setting up WordPress..."

if [ ! -f "$WP_PATH/wp-config.php" ]; then
    echo "Downloading WordPress..."
    curl -o /tmp/wordpress.tar.gz https://wordpress.org/latest.tar.gz
    tar -xzf /tmp/wordpress.tar.gz -C /tmp
    cp -rn /tmp/wordpress/* "$WP_PATH/"
    rm -rf /tmp/wordpress /tmp/wordpress.tar.gz

    echo "Configuring WordPress..."

    WP_SALTS=$(wget -qO- https://api.wordpress.org/secret-key/1.1/salt/)

    cat > "$WP_PATH/wp-config.php" << EOF
<?php
define('DB_NAME', '${WORDPRESS_DB_NAME}');
define('DB_USER', '${WORDPRESS_DB_USER}');
define('DB_PASSWORD', '${WORDPRESS_DB_PASSWORD}');
define('DB_HOST', '${WORDPRESS_DB_HOST}');
define('DB_CHARSET', 'utf8');
define('DB_COLLATE', '');

\$table_prefix = '${WORDPRESS_TABLE_PREFIX:-wp_}';

${WP_SALTS}

define('WP_DEBUG', false);

if ( !defined('ABSPATH') )
    define('ABSPATH', __DIR__ . '/');

require_once ABSPATH . 'wp-settings.php';
EOF

    find "$WP_PATH" -type d -exec chmod 750 {} \;
    find "$WP_PATH" -type f -exec chmod 640 {} \;
    chown -R www-data:www-data "$WP_PATH"

    echo "WordPress setup complete."
else
    echo "WordPress is already set up."
fi

echo "Starting PHP-FPM..."
exec php-fpm8.2 -F