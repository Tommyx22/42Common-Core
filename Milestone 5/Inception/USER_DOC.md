# User Documentation

## Services provided

The stack provides a WordPress website with the following services:

- Nginx serves the website over HTTPS.
- WordPress provides the content management system.
- PHP-FPM executes WordPress PHP code.
- MariaDB stores the WordPress database.

Only Nginx is exposed to the host, on HTTPS port `443`.

## Start the project

From the repository root, run:

```bash
make
```

Check the running services:

```bash
make status
```

## Stop the project

Stop the containers without deleting persistent data:

```bash
make down
```

To follow service logs:

```bash
make logs
```

## Access the website

Open:

```text
https://tolanini.42.fr
```

The local TLS certificate is self-signed, so the browser may display a security warning.

The WordPress administration panel is available at:

```text
https://tolanini.42.fr/wp-admin
```

The administrator username is configured in `srcs/.env` with `WORDPRESS_ADMIN_USER`. The administrator password is stored locally in `secrets/wp_admin_password.txt`.

## Credentials

Credential files are stored locally in:

```text
secrets/db_password.txt
secrets/db_root_password.txt
secrets/wp_admin_password.txt
secrets/wp_user_password.txt
```

Do not publish these files or share their contents. Change the local passwords when needed, then recreate the database and WordPress data if the credentials were already used during initialization.

Non-sensitive usernames, email addresses, the database name, and the domain are configured in:

```text
srcs/.env
```

## Check that the stack is working

List the containers:

```bash
docker ps
```

Check the HTTPS response:

```bash
curl -kI https://tolanini.42.fr
```

Check service logs:

```bash
docker logs nginx
docker logs wordpress
docker logs mariadb
```

Check persistent data:

```bash
ls -la /home/tolanini/data/wordpress
ls -la /home/tolanini/data/mariadb
```

A healthy stack should have running `nginx`, `wordpress`, and `mariadb` containers, and the WordPress directory should contain `index.php`, `wp-admin`, `wp-content`, and `wp-includes`.
