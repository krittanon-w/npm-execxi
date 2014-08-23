# Downloading Libraries

## Faster Way

```
# master
git clone https://chromium.googlesource.com/external/v8
```

## Longer Way
https://code.google.com/p/v8/wiki/UsingGit 

## Prerequisites

Make sure git and git-svn are installed. To install using apt-get:

```
apt-get install git git-svn
```

You will also need to [install depot tools](http://dev.chromium.org/developers/how-tos/install-depot-tools).

```
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
```

Add depot_tools to your [PATH](http://www.lmgtfy.com/?q=PATH+environment):

```
export PATH=`pwd`/depot_tools:"$PATH"
```

- (Yes, you want to put depot_tools ahead of everything else, otherwise `gcl` will refer to the GNU Common Lisp compiler.)
- You may want to add this to your `.bashrc` file or your shell's equivalent so that you don’t need to reset your $PATH manually each time you open a new shell.

# How to start

Cloning v8's bleeding_edge branch, setting up git svn, and getting all dependencies can be done using:


```
fetch v8
```


## Staying up-to-date

On your development branch:

```
git pull --rebase origin
```

Sometimes dependencies of v8 are updated. You can synchronize those by running

```
gclient sync
```