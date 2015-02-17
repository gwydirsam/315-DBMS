# Database Management System and App
## CSCE315 Project 2

[Project 2 Spec](http://faculty.cse.tamu.edu/ritchey/courses/csce315/spring15/homework/project2.html)

### Team 15 CSCE315-503
* Rabia Gunonu
  * sgunonu@tamu.edu

* Sam Gwydir
  * gwydir8@tamu.edu

* Nicolas Juarez
  * nickj_4@tamu.edu

* Daniel "Kade" Koon
  * kadekoon@tamu.edu

# Building
## Engine
The following will build the release, debug and shared library version of dbengine,
dbengine, dbengined, lib15dbengine.so (or dylib on os x)
```bash
cd engine
./configure.sh
cd build
make
# binaries and library will be in engine/build/src/
```

# Execution
## Engine
```bash
# cd to project root
cd CSCE315-Project2
#for debug binary
./engine/build/src/dbengined
#for relase binary
./engine/build/src/dbengine