# Use a base image with GTK and WebKit2GTK support
FROM ubuntu:20.04

# Set environment variables to prevent interaction during package installations
ENV DEBIAN_FRONTEND=noninteractive

# Install required dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    pkg-config \
    gtk+-3.0 \
    libwebkit2gtk-4.0-dev \
    g++ \
    wget && \
    rm -rf /var/lib/apt/lists/*

# Copy the source code and HTML files into the container
COPY main.cpp /app/main.cpp
COPY index.html /app/index.html

# Set the working directory
WORKDIR /app

# Compile the C++ code
RUN g++ main.cpp -o app `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`

# Expose any necessary ports (if your WebView loads content from a local server, for example)
# EXPOSE 8080

# Run the application
CMD ["./app"]
