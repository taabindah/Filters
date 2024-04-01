# Filters

This C code provides implementations for applying various filters to images. Each filter serves a different purpose and can be used to manipulate and enhance images.

## Filters Implemented  

### **Grayscale Filter**
Converts the input image to grayscale by averaging the RGB values of each pixel and setting them all to the same value.

### **Reflect Filter**
Reflects the input image horizontally across the vertical axis.

### **Sepia Filter**
Converts the input image to sepia tone using specific formulas to calculate new RGB values based on the original RGB values for each pixel.

### **Blur Filter**
Blurs the input image by averaging the RGB values of neighboring pixels within a 3x3 grid centered on each pixel.

### **Edges Filter**
Detects edges in the input image using the Sobel operator. It calculates the gradients in both the x and y directions for each pixel and computes the magnitude to identify edges.

These filters can be used individually or in combination to achieve different visual effects and enhancements in images.
