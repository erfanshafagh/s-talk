# s-talk

s-talk is a simple chat program developed in C, allowing users to send and receive messages over a network using UDP sockets.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction
s-talk is a command-line chat program that enables communication between two users over a network. It uses UDP sockets for message transmission. The program is developed in C and consists of different modules for input handling, message sending, message receiving, and overall socket management.

## Features
- Two-way communication between users.
- Simple command-line interface.
- Uses UDP for message transmission.
- Modular design with components for input, output, sending, and receiving.

## Getting Started
To get started with s-talk, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/s-talk.git
    ```

2. Compile the program:
    ```bash
    make
    ```

3. Run the program with the required command-line arguments:
    ```bash
    ./s-talk yourPort remoteIP remotePort
    ```

## Usage
- Once the program is running, you can start typing messages to communicate with the other user.
- Press Enter to send a message.
- To exit the program, type `!` and press Enter.

## Contributing

If you find any issues or have suggestions for improvement, feel free to open an [issue](https://github.com/erfanshafagh/s-talk/issues) or create a [pull request](https://github.com/erfanshafagh/s-talk/pulls).
