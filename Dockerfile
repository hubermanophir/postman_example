FROM debian:stable-slim

# Install libmicrohttpd and build tools
RUN apt-get update && apt-get install -y \
    gcc \
    libmicrohttpd-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy source
WORKDIR /app
COPY server.c .

# Build
RUN gcc -o server server.c -lmicrohttpd

# Expose port
EXPOSE 8080

# Run server
CMD ["./server"]
