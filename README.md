# EasyTourney
A simple, easy to use tournament bracket manager.

## Installation 

**Linux Installation: Building from Source**  
  
1. First, install the development files for GTK+2 (or whatever your windowing system is):
  ```  
  $ sudo apt-get install libgtk2.0-dev  
  OR  
  $ sudo yum install gtk2-devel
  ```
  
2. Download the wxWidgets source code and extract it: http://wxwidgets.org/downloads/

3. Open a terminal, cd into the wxWidgets directory, and create a new build directory:
  ```
  $ cd wxWidgets-3.0.2  
  $ mkdir build-gtk
  ```
  
4. Cd into the new build directory and call the configure script, replacing gtk=2 with your windowing system (gtk, x11, osx-cocoa, etc)
  ```
  $ cd build-gtk
  $ ../configure --with-gtk=2 --disable-shared
  ```
  
5. Call make to build the wxWidgets library. Warning: this step takes about 10 minutes and 2GB of space (which you can safely delete after the end of this installation tutorial)
  ```
  $ make
  ```
  
6. Download the EasyTourney source code and cd into its base directory: 
  ```
  cd EasyTourney/
  ```

7. Open the Makefile with a text editor and modify the first line so it has the **full** path to the wxWidgets build directory that you created in step 3. It will look something like: 
  ```
  WX_BUILD = /home/user/Downloads/wxWidgets-3.0.2/build-gtk
  ```

8. Now just run make, and the executable EasyTourney file should appear in the EasyTourney/build directory
  ```
  $ make
  ```

**Linux Installation: Precompiled Binary**  
A precompiled binary executable is available here: http://www.tcnj.edu/~wulfd1/EasyTourney/EasyTourney  
This binary should work on most Linux systems using gtk2 or gtk3. Just run the following command on the file and it will be ready to go.
```
$ chmod +x EasyTourney
```

**OSX Installation: Building from Source**  
I have not yet built this application on OSX but it should be very similar to the Linux method.

**Windows Installation: Building from Source**  
Coming soon!
