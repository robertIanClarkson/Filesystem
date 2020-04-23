# LBA structure (summary)
## file
#### 1: Name
#### 2: file
#### 3: metadata LBA index
#### 4: LBA index of body #1
#### ...
#### 31: LBA index of body #28
#### 32: LBA index for extended

## folder
#### 1: Name
#### 2: folder
#### 3: metadata LBA index
#### 4: LBA index of child #1
####   ...
#### 31: LBA index of child #28
#### 32: LBA index for extended

## metadata
#### 1: Name file/folder it is representing
#### 2: metadata
#### 3: type
#### 4: value
####   ...
#### 31: type
#### 32: value

## extended
#### 1: Name file/folder it is representing
#### 2: extended
#### 3: LBA index of body/child #29
#### 4: LBA index of body/child #30
#### ...
#### 31: LBA index of body/child #59
#### 32: LBA index for extended

### ***************************************************

## Easiest
### $ make bang!
### $ make superclean! 

## Bierman file (fsLowDriver.c):
### $ make clean
### $ make runLow

## Our File (fsdriver3.c):
### $ make clean
### $ make run

## hexdump (hexdump.c):
### First (make runLow) || (make run)
### $ make cleanHex
### $ make runHexDump

## functions:
#### (create a directory named 'foo' under the directory 'root')
#### Filesystem_Prompt$ mkdir foo root

#### (create a file named 'foo' under the directory 'root')
#### Filesystem_Prompt$ touch foo root

#### (list all directories under 'root')
#### Filesystem_Prompt$ ld root

#### (remove a file named 'foo' under the directory 'root')\n
#### Filesystem_Prompt$ rm foo root

#### (copy file 'foo' as 'blah' from directory 'hello' to directory 'world')
#### Filesystem_Prompt$ cp foo hello blah world

#### (move file 'foo' as 'blah' from directory 'hello' to directory 'world')
#### Filesystem_Prompt$ mv foo hello blah world

#### (set meta data category 'author' to name 'foo' 'bar' in file 'hello' in directory 'world')
#### Filesystem_Prompt$ set hello world author foo bar

#### (copy actual file '/my/local/path/on/my/computer.txt' to project directory 'foo')
#### Filesystem_Prompt$ cp_from /my/local/path/on/my/computer.txt foo

#### (copy file 'foo' in directory 'bar' into '/my/local/path/on/my/computer/')
#### Filesystem_Prompt$ cp_to foo bar /my/local/path/on/my/computer/

## LBA structure (FOCUS ON RIGHT SIDE OF PRINT OUT)
### file
#### initialization char = '-'
#### filename            = foo
#### type                = file
#### metadata LBA Index  = 1
#### body LBA Indexes    = 2 & 3

##### 000200: 72 6F 6F 74 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | foo-------------
##### 000210: 66 6F 6C 64 65 72 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | file------------
##### 000220: 31 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | 1---------------
##### 000230: 32 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | 2---------------
##### 000240: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | 3---------------
##### 000250: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000260: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000270: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000280: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000290: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002A0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002B0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002C0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002D0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002E0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002F0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------

##### 000300: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000310: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000320: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000330: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000340: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000350: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000360: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000370: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000380: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000390: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003A0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003B0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003C0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003D0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003E0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003F0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ---------------- 

### folder
#### initialization char = '-'
#### filename            = root
#### type                = folder
#### metadata LBA Index  = 1
#### child LBA Index     = 2

##### 000200: 72 6F 6F 74 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | root------------
##### 000210: 66 6F 6C 64 65 72 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | folder----------
##### 000220: 31 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | 1---------------
##### 000230: 32 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | 2---------------
##### 000240: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000250: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000260: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000270: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000280: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000290: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002A0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002B0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002C0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002D0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002E0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0002F0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------

##### 000300: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000310: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000320: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000330: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000340: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000350: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000360: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000370: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000380: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 000390: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003A0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003B0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003C0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003D0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003E0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------
##### 0003F0: 2D 2D 2D 2D 2D 2D 2D 2D  2D 2D 2D 2D 2D 2D 2D 2D | ----------------

### metadata
#### initialization char = '*'
#### filename            = root
#### type                = metadata
#### catagories          = author & created
#### values              = foo bar & 4/20/2020

##### 000400: 72 6F 6F 74 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | root************
##### 000410: 6D 65 74 61 64 61 74 61  2A 2A 2A 2A 2A 2A 2A 2A | metadata********
##### 000420: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | author**********
##### 000430: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | foo bar*********
##### 000440: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | created*********
##### 000450: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | 4/20/2020*******
##### 000460: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000470: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000480: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000490: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0004A0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0004B0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0004C0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0004D0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0004E0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0004F0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************

##### 000500: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000510: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000520: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000530: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000540: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000550: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000560: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000570: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000580: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 000590: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0005A0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0005B0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0005C0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0005D0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0005E0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
##### 0005F0: 2A 2A 2A 2A 2A 2A 2A 2A  2A 2A 2A 2A 2A 2A 2A 2A | ****************
