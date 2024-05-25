# Use GCC 7 image from Docker Hub
FROM gcc:7

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Compile the C++ source file with C++17 support
RUN g++ -std=c++17 -o myapp code.cpp

# Command to run the executable
CMD ["./myapp"]
