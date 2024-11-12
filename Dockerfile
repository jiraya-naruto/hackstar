# Use an official Ubuntu base image
FROM ubuntu:20.04

# Set environment variables to non-interactive to avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libgtk-3-dev \
    libwebkit2gtk-4.0-dev \
    pkg-config \
    wget \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Create a directory for the application
WORKDIR /app

# Copy the C++ source code and HTML files into the container
COPY main.cpp /app/
COPY index.html /app/

# Compile the C++ application
RUN g++ main.cpp -o fullscreen_app `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`

# Expose the port (if needed for a web server)
EXPOSE 8080

# Set the default command to run the compiled application
CMD ["./fullscreen_app"]
