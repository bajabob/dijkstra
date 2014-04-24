#Dijkstra's Shortest Path
![Alt text](images/1-7.png?raw=true "Shortest Path 1-7")
![Alt text](images/1-20.png?raw=true "Shortest Path 1-20")
![Alt text](images/1-256.png?raw=true "Shortest Path 1-256")

##Purpose
This project parses a graph data file in C, and outputs a generated index.html file based on [@julianbrowne's](https://github.com/julianbrowne/dijkstra) awesome Javascript Dijkstra graph library. Additionally this project is designed to read very large graph data files, calculate the shortest user defined path, and output the necessary files to be visually represented via web browser.

##How To Run
* Clone to a local environment
* Run "Make" from the working directory. Note, if you don't have gcc-47 installed, try removing the "-4.7" flag" (not tested).
* Run the compiled application, "./da".
* When prompted, enter a test file. A couple samples are included and are formatted very specifically. "test.txt", "test1.txt", "test2.txt".
* Read the list of read Vertexes and pick two to traverse too, enter them when prompted. I suggest for "test.txt" to traverse from 1 to 7, "test1.txt" 1 to 20, and have fun with "test2.txt", it is quite large.
* The program will then generate an index.html file to which you can then navigate using your web server. 

##Requirements
* C compiler: The Makefile is set to compile on gcc-47, though other versions should work as well. This implementation was only tested on 4.7, remove this flag if you are running a different version.
* Local Web Server: Additionally you will need a local web server setup to point to your working directory that generates the index.html. Because this project is capable of representing large amounts of data, JavaScript requires the ability to read a local file from your file system. These are the files that are generated in C.



