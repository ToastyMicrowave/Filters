# Edge Detection & Image Filters in C (CS50x)

An image-processing program written in **C** as part of **CS50x**, implementing several bitmap filters — **grayscale**, **reflection**, **blur**, and **Sobel edge detection**.

# Features
- Converts images to grayscale and mirrored reflections  
- Applies a box blur for smoothing  
- Detects edges using **Sobel operators** on RGB channels  
- Handles pixel boundaries safely and efficiently
- Free from memory leaks, manages memory efficiently

# Usage
```bash
make filter
./filter [FILTER] input.bmp output.bmp
```
# Tech Stack
Language: C
Tools: GCC, CS50 Library
Concepts: 2D Convolution, Pointers, Memory Management, Image Processing
