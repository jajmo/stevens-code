Assignment 3 - Filesystem
=========================

External Libraries
------------------
* `tree.hh` and `tree_util.hh` from [here](http://tree.phi-sci.com/download.html)

Dependencies
------------
* std::list
* Libraries X11, Xmu, m, and rt

Usage
-----
Run `make` in the project root

`./filesystem [-fsb]`

With file_list and dir_list:

`./filesystem -f dir_list.txt file_list.txt`

With file_list, dir_list, and sizes

`./filesystem -f dir_list.txt file_list.txt -s diskSize -b blockSize`

**NOTE**: If you provide the diskSize and not the blockSize, or vice versa, it will use defaults for both.
