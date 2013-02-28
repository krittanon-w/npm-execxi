                                __   __   ______     
                               /\ \ /\ \ /\__  _\    
       __   __  _    __    ___ \ `\`\/'/'\/_/\ \/    
     /'__`\/\ \/'\ /'__`\ /'___\`\/ > <     \ \ \    
    /\  __/\/>  <//\  __//\ \__/   \/'/\`\   \_\ \__ 
    \ \____\/\_/\_\ \____\ \____\  /\_\\ \_\ /\_____\
     \/____/\//\/_/\/____/\/____/  \/_/ \/_/ \/_____/
                                                     
                                                     

                                                   
                                             __    
       __     _____     ___     ___    __  _/\_\   
     /'__`\  /\ '__`\  / __`\ /' _ `\ /\ \/'\/\ \  
    /\ \L\.\_\ \ \L\ \/\ \L\ \/\ \/\ \\/>  </\ \ \ 
    \ \__/.\_\\ \ ,__/\ \____/\ \_\ \_\/\_/\_\\ \_\
     \/__/\/_/ \ \ \/  \/___/  \/_/\/_/\//\/_/ \/_/
                \ \_\                              
                 \/_/                              

# Jump to Section


* [Installation](#installation)
* [Usage](#usage)
* [Example](#example)
* [Example Output to Console](#output)
* [Legal Stuff](#legal-mombo-jombo)

# execXI

ExecXI is a node extension written in C++ to execute shell commands one by one, outputting the command's output to the console in real-time. Optional chained, and unchained ways are present; meaning that you can choose to stop the script after a command fails (chained), or you can continue as if nothing has happened !

## Installation
[Back To Top](#)

- via npm

```shell
npm install execxi --save
```

- Manually

```shell
git clone git://github.com/aponxi/npm-execxi.git
make
```

## Usage
[Back To Top](#)

```
var execxi = require("execxi");
execxi.executeArray(<Array> Commands[, <bool> Chained = true] )
```

- You just supply with one or two arguments. First is the array of commands to run, such as:

```js
[ "ls", "ls -lart"] //as many as you want (I suppose)
```

- Second argument `Chained`, which is `true` by default, is an option that can stop running commands after one of them failed. To see if it failed, it checks the exit code of the command that is run.

- In the end it outputs a summary to the console, stating how many commands are run, how many passed, how many failed and which ones passed and failed.

- Returns an array of results:

```js
[
    0: bool, // true if all commands exited with code 0, false if one or more exited with other than 0.
    1: int, // exit code of the first command that is run
    2: int, // exit code of the second command that is run
//  ...
//  ...
    n: int, // exit code of the nth command that is run. (these numbers corresponds with commands that have been run, just note that in our commands array the first command would "be" with key [0] when here it is with key [1] )
    "max": int, // number of commands that you wanted to run
    "ran": int, // number of commands that have been run, or at least tried to run.
    "failed": int, // number of commands that have failed (exited with other than 0)
    "passed": int // number of commands that have passed (exited with 0)
]
```

## Example
[Back To Top](#)

```js
//require the extension/module/wtv
var execxi = require("execxi");

// I just defined some commands here
// These will run for a long time. So you can see that outputs are occurring in real-time.
var long_commands = ["find ~/"];
// These are just some shell scripts that exit with different exit codes
// one exits with 0, other exists with 1, and lastly 2.
var exit_codes = ["./tests/exit_0.sh","./tests/exit_1.sh","./tests/exit_2.sh"];
// this is non existent command to see what happens when it doesn't find the command to run.
// returns 127 exit code.
var non_existent = ["./tests/sadf.sh"];
// some regular commands that run successfully
var regular = Array("ls","echo \"Works\"", "ls -lart");

// I get the commands I want to run to tests_to_run array.
var tests_to_run = Array();
tests_to_run = tests_to_run.concat(regular, exit_codes,non_existent);

// Right now we have array of 7 commands to run

// lets run in chained mode to observe
var res = execxi.executeArray(tests_to_run);
// lets see what it returns as a result array
console.dir(res);

// lets run without chained mode on, and also observe
var res = execxi.executeArray(tests_to_run, false);

// lets see what it returns as a result array
console.dir(res);
```

## Output

[Back To Top](#)

That example outputs something long like this:

- With Color:

![Imgur](http://i.imgur.com/jjrm9h4.png)

- Copy/Paste from console:

```
logan@home:~/projects/npm-execxi$ node test

￭ Running Command   [ 1/7 ]
----------------------------------------

binding.gyp
build
exec_all.cpp
execxi.cpp
execxi.h
execxi.sublime-project
execxi.sublime-workspace
Makefile
package.json
README.md
test.js
tests

✔ Command [ 1/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 2/7 ]
----------------------------------------

Works

✔ Command [ 2/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 3/7 ]
----------------------------------------

total 168
drwxrwxr-x  2 logan logan  4096 Feb 27 02:00 tests
-rw-rw-r--  1 logan logan   362 Feb 28 00:01 README.md
drwxr-xr-x 30 logan logan  4096 Feb 28 00:02 ..
-rw-rw-r--  1 logan logan    73 Feb 28 00:16 execxi.sublime-project
-rw-rw-r--  1 logan logan 15220 Feb 28 00:16 execxi.sublime-workspace
-rw-rw-r--  1 logan logan   154 Feb 28 00:16 .gitignore
-rw-rw-r--  1 logan logan   587 Feb 28 00:17 package.json
-rw-rw-r--  1 logan logan   496 Feb 28 00:18 test.js
-rw-rw-r--  1 logan logan    52 Feb 28 00:24 Makefile
-rw-rw-r--  1 logan logan  1339 Feb 28 00:27 execxi.h
-rw-rw-r--  1 logan logan  1421 Feb 28 00:27 execxi.cpp
-rw-rw-r--  1 logan logan   115 Feb 28 00:29 binding.gyp
drwxrwxr-x  5 logan logan  4096 Feb 28 00:49 .
drwxrwxr-x  3 logan logan  4096 Feb 28 00:49 build
-rw-rw-r--  1 logan logan  7755 Feb 28 00:57 exec_all.cpp
drwxrwxr-x  8 logan logan  4096 Feb 28 00:57 .git

✔ Command [ 3/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 4/7 ]
----------------------------------------

Exit 0

✔ Command [ 4/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 5/7 ]
----------------------------------------

Exit 1

✗ Command [ 5/7 ] exited with: 1. Stopped at after running command #5.

  ▲ If you would like to continue after a command doesn't exit with code 0, supply "executeArray(<Array> Commands, <bool> Chained)" function with "Chained" = "false" argument.
----------------------------------------

[ false, 0, 0, 0, 0, 1, max: 7, ran: 5, failed: 1, passed: 4 ]

￭ Running Command   [ 1/7 ]
----------------------------------------

binding.gyp
build
exec_all.cpp
execxi.cpp
execxi.h
execxi.sublime-project
execxi.sublime-workspace
Makefile
package.json
README.md
test.js
tests

✔ Command [ 1/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 2/7 ]
----------------------------------------

Works

✔ Command [ 2/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 3/7 ]
----------------------------------------

total 168
drwxrwxr-x  2 logan logan  4096 Feb 27 02:00 tests
-rw-rw-r--  1 logan logan   362 Feb 28 00:01 README.md
drwxr-xr-x 30 logan logan  4096 Feb 28 00:02 ..
-rw-rw-r--  1 logan logan    73 Feb 28 00:16 execxi.sublime-project
-rw-rw-r--  1 logan logan 15220 Feb 28 00:16 execxi.sublime-workspace
-rw-rw-r--  1 logan logan   154 Feb 28 00:16 .gitignore
-rw-rw-r--  1 logan logan   587 Feb 28 00:17 package.json
-rw-rw-r--  1 logan logan   496 Feb 28 00:18 test.js
-rw-rw-r--  1 logan logan    52 Feb 28 00:24 Makefile
-rw-rw-r--  1 logan logan  1339 Feb 28 00:27 execxi.h
-rw-rw-r--  1 logan logan  1421 Feb 28 00:27 execxi.cpp
-rw-rw-r--  1 logan logan   115 Feb 28 00:29 binding.gyp
drwxrwxr-x  5 logan logan  4096 Feb 28 00:49 .
drwxrwxr-x  3 logan logan  4096 Feb 28 00:49 build
-rw-rw-r--  1 logan logan  7755 Feb 28 00:57 exec_all.cpp
drwxrwxr-x  8 logan logan  4096 Feb 28 00:57 .git

✔ Command [ 3/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 4/7 ]
----------------------------------------

Exit 0

✔ Command [ 4/7 ] exited with 0.
----------------------------------------


￭ Running Command   [ 5/7 ]
----------------------------------------

Exit 1

▲ Command [ 5/7 ] exited with 1.
----------------------------------------


￭ Running Command   [ 6/7 ]
----------------------------------------

Exit 2

▲ Command [ 6/7 ] exited with 2.
----------------------------------------


￭ Running Command   [ 7/7 ]
----------------------------------------


▲ Command [ 7/7 ] exited with 127.
----------------------------------------



----------------------------------------
----------------------------------------
-               SUMMARY                -
----------------------------------------

  ￭ Ran 7/7 commands.

----------------------------------------

  ✔ Passed: 4 commands:
  ✔ #1 #2 #3 #4 

----------------------------------------

  ✗ Failed: 3 commands:
  ✗ #5 #6 #7 

----------------------------------------

----------------------------------------
----------------------------------------

[ false, 0, 0, 0, 0, 1, 2, 127, max: 7, ran: 7, failed: 3, passed: 4 ]
```

## Legal mombo jombo

[Back To Top](#)

If you would mention WeaponXI in your source code or under credits or something it would mean the world to me!

Copyright © 2012 - 2013 WeaponXI <aponxi@weaponxi.com>
This software is licensed under [MIT License](http://aponxi.mit-license.org/).
