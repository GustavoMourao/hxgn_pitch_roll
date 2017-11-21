# hxgn_pitch_roll
This program get raw cartesian data and transform to pitch and roll angles. Project developmented to Hexagon Agriculture.

### Getting Started
This program were development in Microsoft Visual Studio plataform. To execute you have to run the file HXGNApplication_eval.cpp, inside the folder HXGNApplication_eval. 

The algorithm requires an .txt file which contains the set of raw data (cartesian points from accelerometer). The file has to be put inside the folder HXGNApplication_eval.

### Runing and test
Once execute the main HXGNApplication_eval.cpp, the software will create an output file containing the set of algles calculated (roll and pitch), named output_attitude.txt.

Note that in the folder already contains a file with this name, which in case of the user delete it, the program will create a new one.

### Procediments to obtain angles
First step is to get raw data from accelerometer. Since the set of data is structured in line formats (time sampled; x-axis; y-axis; z-axis), is necessary to separated the set of data. 

To do that we call the function:
```sh
wordsInFile(string line, int& wordCount, int& charCount)
```
Once counted identified the data, we perform the calculations necessary to obtain the roll and pitch angles, as:

![equation](https://latex.codecogs.com/gif.latex?tan%5Cphi%3D%5Cfrac%7By%7D%7B%5Csqrt%7B%28x%29%5E2&plus;%28z%29%5E2%7D%7D)
and 
![equation](https://latex.codecogs.com/gif.latex?tan%5Cphi%3D%5Cfrac%7B-x%7D%7Bz%7D)

The function resposible to calculate is:
```sh
rollAndpitch(atof(time), atof(x_axis), atof(y_axis), atof(z_axis));
```

Finally, to store the set of calculated values in .txt files we use the function:

```sh
storageRollPitch(timems, phi, theta);
```
### Authors
Gustavo L. Mourao.

With consults in: http://www.cplusplus.com/

