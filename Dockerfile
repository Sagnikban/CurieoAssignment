# Use a specific version of GCC image from the Docker Hub
FROM gcc:10

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Compile the C++ source file
RUN g++ -o myapp main.cpp

# Command to run the executable
CMD ["./myapp"]
