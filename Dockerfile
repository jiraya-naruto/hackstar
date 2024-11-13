# Use a base image with GTK + WebKit dependencies
FROM ubuntu:20.04

# Set environment variables to avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libgtk-3-dev \
    libwebkit2gtk-4.0-dev \
    g++ \
    git \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Create a working directory
WORKDIR /app

# Copy C++ source code and HTML file
COPY . /app

# Build the C++ application using g++
RUN g++ -o my_app main.cpp -lgtk-3 -lwebkit2gtk-4.0

# Expose a port if needed (e.g., for a local server, but this example runs the app directly)
# EXPOSE 8080

# Set the command to run the application
CMD ["./my_app"]
