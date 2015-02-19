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
* DBEngine depends on boost 1.57.0, gtest 1.7.0 and to improve build times, it is helpful to use ccache.
* engine/build.sh will check if you have boost 1.57.0, gtest 1.7.0 and ccache, if not, it will install them for you.
* engine/build.sh will then build the release, debug and shared library version of dbengine (a release and debug version), dbengine, libdbengine.so(or dylib on os x) and all unittests
```bash
cd engine
./build.sh
# release binaries will be in engine/build/release/dbengine/
# release unittest will be in engine/build/release/dbengine/
# release libraries will be in engine/build/release/dbengine/lib/
# debug binaries will be in engine/build/debug/dbengine/
# debug unittest will be in engine/build/debug/dbengine/
# debug libraries will be in engine/build/debug/dbengine/lib/
```

for repeating builds
* Running build.sh more than one time will result in running make clean in build/debug and build/release. And then make. Running make clean allows ccache to be utilized.
```bash
cd engine/
./build.sh
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
#for release binary
cd engine/build/release/dbengined/
mkdir tables
./dbengine
#for release unittest binary
./dbenginetest
```
