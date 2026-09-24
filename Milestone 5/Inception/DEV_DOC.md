# Developer Documentation

## Project layout

```text
.
├── Makefile
├── secrets/
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        ├── nginx/
        └── wordpress/
```

Each service has its own Dockerfile, configuration files, and startup script.

## Prerequisites

Install Docker Engine and the Docker Compose plugin inside the project virtual machine. Verify the installation:

```bash
docker --version
docker compose version
```

The Docker user must be able to run Docker commands. The project also expects the host directories below to be available:

```text
/home/tolanini/data/mariadb
/home/tolanini/data/wordpress
```

The Makefile creates them automatically.

## Configuration

Non-sensitive settings are stored in `srcs/.env`:

- `DOMAIN_NAME`
- `MYSQL_DATABASE`
- `MYSQL_USER`
- WordPress administrator and regular-user names and email addresses
- `WORDPRESS_TITLE`

Passwords are stored in the local files under `secrets/` and are mounted into the containers as Docker secrets. Never commit or publish their contents.

Make sure the local domain resolves to the VM:

```bash
sudo sh -c 'printf "127.0.0.1 tolanini.42.fr\\n" >> /etc/hosts'
```

Use the VM IP instead of `127.0.0.1` when the website is accessed from another machine.

## Build and launch

Run from the repository root:

```bash
make
```

The default target performs `make build` followed by `make up`.

Build only:

```bash
make build
```

Start existing images:

```bash
make up
```

Inspect the Compose-resolved configuration:

```bash
docker compose -f srcs/docker-compose.yml --env-file srcs/.env config
```

## Container and volume management

Show service status:

```bash
make status
```

Follow all service logs:

```bash
make logs
```

Stop containers while keeping data:

```bash
make down
```

Stop containers and remove Compose volumes:

```bash
make clean
```

The `re` target performs a complete cleanup, prunes Docker resources, removes `/home/tolanini/data`, rebuilds the images, and starts the stack:

```bash
make re
```

Use it only when deleting all project data is acceptable.

Useful Docker commands:

```bash
docker compose -f srcs/docker-compose.yml ps
docker compose -f srcs/docker-compose.yml logs -f
docker network inspect inception-network
docker volume ls
docker exec wordpress ls -la /var/www/html
```

## Persistence

The Compose file defines two named volumes:

- `mariadb_data` stores the MariaDB data at `/var/lib/mysql`.
- `wordpress_data` stores the WordPress files at `/var/www/html`.

Their host locations are:

```text
/home/tolanini/data/mariadb
/home/tolanini/data/wordpress
```

The data remains after `make down` and normal container recreation. Removing volumes or running `make clean` deletes the Docker volume references; running `make re` also removes the host data directory.

## Service communication

The containers use the `inception-network` bridge network. Internal service names are used instead of host networking:

- WordPress connects to MariaDB at `mariadb:3306`.
- Nginx connects to PHP-FPM at `wordpress:9000`.
- Nginx is the only service publishing a host port: `443`.

## Troubleshooting

Check all containers:

```bash
docker ps
```

Check the service-specific logs:

```bash
docker logs mariadb
docker logs wordpress
docker logs nginx
```

If WordPress files are missing after a failed first initialization, stop the stack and remove the project data before starting again:

```bash
make down
sudo rm -rf /home/tolanini/data/mariadb/* /home/tolanini/data/wordpress/*
make
```

This reset deletes persistent data and should only be used for a fresh installation or troubleshooting.
