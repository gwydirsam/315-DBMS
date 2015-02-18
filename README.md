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
The following will build the release, debug and shared library version of dbengine (a release and debug version),
dbengine, libdbengine.so(or dylib on os x)
```bash
cd engine
./build.sh
# release binaries will be in engine/build/release/dbengine/
# release libraries will be in engine/build/release/dbengine/lib/
# release unittest will be in engine/build/release/dbengine/
# debug binaries will be in engine/build/debug/dbengine/
# debug libraries will be in engine/build/debug/dbengine/lib/
# debug unittest will be in engine/build/debug/dbengine/
```

for repeating builds
```bash
cd engine/build/debug/dbengine
make -j4 && cd dbengine && ./dbengine&& cd ..
```

# Execution
## Engine
```bash
# cd to project root
cd CSCE315-Project2
#for debug binary
cd engine/build/debug/dbengine/
mkdir tables
./dbengine
#for debug unittest binary
./dbenginetest
#for relase binary
cd engine/build/release/dbengined/
mkdir tables
./dbengine
#for release unittest binary
./dbenginetest
```
