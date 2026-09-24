*This project has been created as part of the 42 curriculum by tolanini.*

# Inception

## Description

Inception is a system administration project that builds a small web infrastructure with Docker Compose. The stack provides a WordPress website served through Nginx over HTTPS, with PHP-FPM handling PHP requests and MariaDB storing the WordPress database.

Each service runs in its own container and is built from a custom Dockerfile based on Debian. The containers communicate through a dedicated Docker bridge network. WordPress files and MariaDB data are persisted with Docker named volumes stored under `/home/tolanini/data` on the host.

### Services

- **Nginx**: the only public entry point, exposed on HTTPS port `443`.
- **WordPress and PHP-FPM**: the application layer, without Nginx.
- **MariaDB**: the database layer, without Nginx.

### Main design choices

- Nginx terminates TLS and forwards PHP requests to the WordPress container over the Docker network.
- WordPress connects to MariaDB using the service name `mariadb`, which Docker resolves internally.
- Credentials are supplied through Docker secrets stored locally in the `secrets/` directory.
- Non-sensitive configuration such as the domain name and usernames is stored in `srcs/.env`.
- Named volumes preserve the website and database data across container recreation.

### Comparisons

#### Virtual machines vs Docker

A virtual machine includes a complete guest operating system and provides strong isolation, but it requires more memory and storage. Docker containers share the host kernel, start quickly, and package services with their dependencies. This project uses a virtual machine as required by the subject and Docker containers to isolate the individual services inside it.

#### Secrets vs environment variables

Environment variables are convenient for non-sensitive configuration, but their values can be exposed through process and container inspection. Docker secrets are mounted as files and are better suited to passwords. This project uses `.env` for public configuration and Docker secrets for credentials.

#### Docker network vs host network

A Docker bridge network provides service discovery and controlled communication between containers. Host networking removes that isolation and exposes containers directly to the host network stack. This project uses a dedicated bridge network and exposes only Nginx port `443`.

#### Docker volumes vs bind mounts

Named volumes are managed by Docker and provide persistent storage without coupling a container to an arbitrary application path. Bind mounts map an explicit host path and are useful when files must be edited directly from the host. The mandatory WordPress and MariaDB storage uses named volumes whose data is located under `/home/tolanini/data`.

## Instructions

### Prerequisites

- A Linux virtual machine
- Docker Engine
- Docker Compose plugin
- A user account with permission to run Docker commands
- The domain `tolanini.42.fr` mapped to the local machine

Add the local mapping when required:

```bash
sudo sh -c 'printf "127.0.0.1 tolanini.42.fr\\n" >> /etc/hosts'
```

### Start the project

From the repository root:

```bash
make
```

This creates the persistent host directories, builds the custom images, and starts the containers in detached mode.

Open the website at:

```text
https://tolanini.42.fr
```

The certificate is self-signed, so a browser warning is expected during local testing.

### Useful commands

```bash
make status
make logs
make down
make clean
make re
```

`make clean` removes the Compose volumes. `make re` also removes the project data under `/home/tolanini/data` and prunes Docker resources; use it only when a complete reset is intended.

## Resources

- Docker documentation: https://docs.docker.com/
- Docker Compose documentation: https://docs.docker.com/compose/
- Docker volumes: https://docs.docker.com/engine/storage/volumes/
- Docker networking: https://docs.docker.com/engine/network/
- Nginx documentation: https://nginx.org/en/docs/
- WordPress developer documentation: https://developer.wordpress.org/
- WP-CLI documentation: https://make.wordpress.org/cli/handbook/
- MariaDB documentation: https://mariadb.com/kb/en/documentation/

### Use of AI

AI assistance was used to review the subject requirements, explain Docker, Compose, networking, volumes, secrets, Nginx, PHP-FPM, and MariaDB concepts, and help troubleshoot the initial container startup. All generated suggestions were checked against the project files and tested through Docker commands. The final configuration and documentation were reviewed by the project author.
