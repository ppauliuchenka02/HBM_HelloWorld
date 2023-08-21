# HBM_HelloWorld

## Installing Memkind
```
git clone https://github.com/memkind/memkind.git
```

## Building and Installing
```
./autogen.sh
./config --prefix=$HOME/usr
make
make install
```

Man pages contain information / docs, to generate man files:

```
make man-local
```

> ```diff
> Error pandoc not installed
> ```
> > ### Instaling pandoc
> > _locally:_ download ``pandoc-3.1.6.1-1-amd64.deb`` bundle for **AMD64** from https://github.com/jgm/pandoc/releases/tag/3.1.6.1
> >
> > _move to the cloud:_ ``scp path_to_pandoc-3.1.6.1-1-amd64.deb userId@devcloud:~``
> 
> > ### Inside Intel DevCloud
> > ```
> > mkdir -p ~/pandoc
> > dpkg-deb -x ./pandoc-3.1.6.1-1-amd64.deb ~/pandoc
> > echo 'export PATH="$PATH:$HOME/pandoc/usr/bin"' >> ~/.bashrc
> > source ~/.bashrc
> > ```
> > 
> > ### Test if installed correctly
> > ``` 
> > pandoc --version
> > pandoc 3.1.6.1
> > Features: +server +lua
> > Scripting engine: Lua 5.4
> > User data directory: /home/u200591/.local/share/pandoc
> > Copyright (C) 2006-2023 John MacFarlane. Web: https://pandoc.org
> > This is free software; see the source for copying conditions. There is no
> > warranty, not even for merchantability or fitness for a particular purpose.
> >```

## Makefile
**Must include paths to ``hbwmalloc.h`` and ``-lmemkind``**

hbwmalloc: ``-I$(HOME)/memkind/include``

-lmemkind ``-L$(HOME)/usr/lib -lmemkind``

### Create new Environmental Variable
> this variable specifies a list of directories where runtime **linker** should look for shared libraries.
> ``` 
> export LD_LIBRARY_PATH=~/USR/LIB:$LD_LIBRARY_PATH 
> ```

## Results
### Default Node
```c
~/HBM_Hello_World$ ./hello_world 
Sequential
Hello, World!
Time: 0.000006

OpenMP
Total threads: 12
Time: 0.010190

HBM, using memkind library - hbwmalloc
Total threads: 12
Time: 0.024167
```

### Node: qsub -I -l nodes=1:ram1024gb:ppn=2

```
~/HBM_Hello_World$ ./hello_world 
Sequential
Hello, World!
Time: 0.000006

OpenMP
Total threads: 224
Time: 6.715491

HBM, using memkind library - hbwmalloc
Total threads: 224
Time: 3.401594
```
```
make clean
make
./hello_world 

Sequential
Hello, World!
Time: 0.000006

OpenMP
Total threads: 224
Time: 4.549395

HBM, using memkind library - hbwmalloc
Total threads: 224
Time: 3.542929
```