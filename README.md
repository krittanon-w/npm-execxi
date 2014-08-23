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



# ExecXI [![Build Status](https://travis-ci.org/aponxi/npm-execxi.png?branch=master)](https://travis-ci.org/aponxi/npm-execxi)

## Version 1.3 Supports Node 0.8, 0.9, 0.10!

ExecXI is a node extension written in C++ to execute shell commands one by one, outputting the command's output to the console in real-time. Optional chained, and unchained ways are present; meaning that you can choose to stop the script after a command fails (chained), or you can continue as if nothing has happened !

Returns exit code of all the commands, and outputs of all the commands. (Be careful of the memory usage.)

### From March 2013 to Aug 2014

This extension was built on Node.js 0.8 and back then there was a very useful library called [V8 Juice](https://code.google.com/p/v8-juice/). It was their type conversion functions that allowed this program to interpret JavaScript values as C++. The C++ part would then take care of the functionality and return a converted JavaScript array, also by utilizing that library.

That V8 library was discontinued due to the major changes after this Node.js version. 

Therefore, execxi seized to function at Node.js 0.9++ as well. 

The biggest challange in restoring this project was that I had a lot trouble finding detailed documentations, examples or function reference on this subject. The problem was to interpret passed arguments from JavaScript and do something with them in C++. As I am documenting my findings, I might as well post them here in case someone is trying to write a Node.js Addon and looking for examples.


- [Sample Addon For Node 0.8.18: jltrem.com](http://jltrem.com/blog/2013/02/06/simple-example-node-js-addon-to-glue-c-to-javascript/)
- [v8 header is the best source: The Doxygen of Google V8 Framework](http://izs.me/v8-docs/namespacev8.html)
- [StackOverflow has specific answers: Search by type like how to convert String](http://stackoverflow.com/questions/16613828/how-to-convert-stdstring-to-v8s-localstring)
- [StackOverflow: Arrays— there is iteration too!](http://stackoverflow.com/questions/23123406/v8-array-of-objects)
- [The joyent/node source for salvaging examples like array usage](https://github.com/joyent/node/blob/2944e03/src/node_child_process.cc#L92-104)
- [My question at StackOverflow before I figured out some specific conversions used in this project](http://stackoverflow.com/questions/25451792/type-casting-between-v8-and-javascript-variable-types-when-writing-a-node-js-c)
- [This repository has examples: rvagg/node-addon-examples](https://github.com/rvagg/node-addon-examples)

To summarize, the clues for writing a Node.js Addon is mostly in the V8 and Ndoe source code. I feel that setting up a good development environment that recognizes v8 functions in the IDE and helps with suggestions would be optimal. Without it, this 1.3 patch was like swimming in the dark; and my light was [this project called aponxi/npm-addon-tests](https://github.com/aponxi/npm-addon-tests) I've started to "Read header files at node and v8 — Find out functions — Try them and compile — Test and Repeat". With a little bit of luck this patch was ready to release after a day or two.

### Projects that are using this extension:

- [Grunt-WXI-Shell](https://github.com/aponxi/grunt-wxi-shell) Grunt Plugin: Executing Shell commands synchronously with Grunt! 

## Jump to Section


* [Installation](#installation)
* [Usage](#usage)
* [Options](#options)
* [Example](#example)
* [Example Output to Console](#output)
* [Building and Testing](#building-and-testing)
* [Change Log](#change-log)
* [Legal Stuff](#legal-mambo-jambo)

## Installation
[Back To Top](#execxi-)

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
[Back To Top](#execxi-)

```js
var execxi = require("execxi");
execxi.executeArray(<Array> Commands[, <Object> Options] )
```

- You just supply with one or two arguments. First is the array of commands to run, such as:

```js
[ "ls", "ls -lart"] //as many as you want (I suppose)
```

- Second argument is Options, see [Options](#options).

- In the end it outputs a summary to the console, stating how many commands are run, how many passed, how many failed and which ones passed and failed.

- Returns an array of results:

```js
[
    0: bool, // true if all commands exited with code 0, false if one or more exited with other than 0.

    // here will be information about the commands you have run
    // lets say you wanted to run 10 commands, then 
    // [1] will point to an Array with first command's output and exit code
    // [2] will point to an Array with second command's output and exit code
    // ...
    // ...
    // [n] will point to an Array with nth command's output and exit code
    // As an example let's assume we have one command:

    1 : ["output": Array(), "exit_code": int],

    // As you can see there are two things that we return about the first command
    // "output" and "exit_code"
    //
    // Not available if returnOption is turned off (it is on by default):
    // "output" is an array of the command's output, first line being the 1st key 
    // in the array, second line being the 2nd key in the array... and so on.
    // You can see the example output below in the Example section of this Read Me.
    //
    // "exit_code" is just the exit code of the command that we ran.

    "max": int, // number of commands that you wanted to run
    "ran": int, // number of commands that have been run, or at least tried to run.
    "failed": int, // number of commands that have failed (exited with other than 0)
    "passed": int // number of commands that have passed (exited with 0)
]
```
If the output's line is more than the maximum bytes, then the rest of the characters will be treated as if it's in the next line. Meaning that you can find a very long line split into two in the `output` array key. Right now the max char limit is `16384` bytes.

## Options
[Back To Top](#execxi-)

- `chained`: `bool`

  `chained`, which is `true` by default, is an option that can stop running commands after one of them failed. To see if it failed, it checks the exit code of the command that is run.

- `returnOutput`: `bool`

  `returnOutput` is also `true` by default. This is what returns the output in an array, parsing them line by line. I supply with this option because sometimes you might run a command that only returns server's IP address or sometimes you can run a command that just outputs very long lines and a very long text. I added the ability to opt out so that when unnecessary you might set it to false.

- `exitSuccess`: `Array(int[,int, ...])`

  `exitSuccess` is an array that contains a collection of error codes that you deem to be a successful exit. All programs use different exit codes, sometimes they give a warning and exit with `2`. In situations like those, I find myself wanting to allow exiting with `2` for that group of commands to be treated as if command was successfully run. This allows the chained commands to continue. 

  By default only `0` exit codes are known to be successful runs. If you supply with `exitSuccess` option you will be overriding that. So, by your definition; a program that fails to run can still be a success.

- `prettyPrint`: `bool`

  `prettyPrint` is `true` by default. This gives the console output its color. Sometimes I find that I need to redirect output into a log file, and don't want the ANSI escape characters such as `\033[0;32m` to appear in the log. This will give you a colorless output in console messages.

- `verbose`: `bool`

  `verbose` is `true` by default. It is used for outputting the command's output as well as giving information on the status (such as "Running Command [1/3]"). There may be times when you just want to quietly utilize the shell command's output. Setting this to `false` will save you from headaches. I usually turn it off when I'm conducting tests, because if I don't, it's a real mess. 


## Example
[Back To Top](#execxi-)

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
// this is just a command that echoes one line, 5000 bytes.
var long_text = ["./tests/echo_bytes_5000.sh"];
// some regular commands that run successfully
var regular = Array("ls","echo \"Works\"", "ls -lart");

// I get the commands I want to run to tests_to_run array.
var tests_to_run = Array();
tests_to_run = tests_to_run.concat(regular, exit_codes,non_existent, long_text);

// Right now we have array of 8 commands to run

// lets run in chained mode to observe
var res = execxi.executeArray(tests_to_run);
// lets see what it returns as a result array
console.dir(res);

// lets run without chained mode on, and also observe
var res = execxi.executeArray(tests_to_run, {"chained": false});

// to test returnOutput option:
// var res = execxi.executeArray(tests_to_run, {"chained": false, "returnOutput":false});

// lets see what it returns as a result array
console.dir(res);

// lets only run this one if the previous one had a 100% pass
console.log ("Lets only run this one if the previous one had a 100% pass");
if (res[0]) {
    console.log("everything passed");
    var res = execxi.executeArray(regular, {"chained": false});
    console.dir(res);
} else {
    console.log("Not running this: previous one did not have a 100% pass");
}
```

## Output

[Back To Top](#execxi-)

That example outputs something long like this:

- With Color:

![Imgur](http://i.imgur.com/jjrm9h4.png)

- Copy/Paste from console:

```
logan@home:~/projects/npm-execxi$ make test
```
```
￭ Running Command [ 1/8 ]
----------------------------------------

binding.gyp
build
exec_all.cpp
execxi.sublime-project
execxi.sublime-workspace
Makefile
package.json
README.md
test.html
test.js
test.log
tests

✔ Command [ 1/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 2/8 ]
----------------------------------------

Works

✔ Command [ 2/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 3/8 ]
----------------------------------------

total 272
drwxr-xr-x 30 logan logan  4096 Feb 28 00:02 ..
-rw-rw-r--  1 logan logan    73 Feb 28 00:16 execxi.sublime-project
-rw-rw-r--  1 logan logan   154 Feb 28 01:16 .npmignore
-rw-rw-r--  1 logan logan   154 Feb 28 02:02 .gitignore
-rw-rw-r--  1 logan logan 44835 Feb 28 06:44 execxi.sublime-workspace
-rw-rw-r--  1 logan logan   102 Mar  1 18:21 binding.gyp
drwxrwxr-x  2 logan logan  4096 Mar  1 20:42 tests
drwxrwxr-x  3 logan logan  4096 Mar  1 20:50 build
-rw-rw-r--  1 logan logan   837 Mar  1 21:26 package.json
-rw-rw-r--  1 logan logan 13055 Mar  1 22:11 exec_all.cpp
-rw-rw-r--  1 logan logan 24505 Mar  1 22:37 README.md
-rw-rw-r--  1 logan logan 21419 Mar  1 22:41 test.html
-rw-rw-r--  1 logan logan 18778 Mar  1 22:41 test.log
-rw-rw-r--  1 logan logan   180 Mar  1 22:43 Makefile
drwxrwxr-x  5 logan logan  4096 Mar  1 22:44 .
-rw-rw-r--  1 logan logan  1780 Mar  1 22:47 test.js
drwxrwxr-x  8 logan logan  4096 Mar  1 22:47 .git

✔ Command [ 3/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 4/8 ]
----------------------------------------

Exit 0

✔ Command [ 4/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 5/8 ]
----------------------------------------

Exit 1

✗ Command [ 5/8 ] exited with: 1. Stopped at after running command #5.

  ▲ If you would like to continue after a command doesn't exit with code 0, supply "executeArray(<Array> Commands, <bool> Chained)" function with "Chained" = "false" argument.
----------------------------------------

[ false,
  [ output: [ 'binding.gyp',
      'build',
      'exec_all.cpp',
      'execxi.sublime-project',
      'execxi.sublime-workspace',
      'Makefile',
      'package.json',
      'README.md',
      'test.html',
      'test.js',
      'test.log',
      'tests' ],
    exit_code: 0 ],
  [ output: [ 'Works' ], exit_code: 0 ],
  [ output: [ 'total 272',
      'drwxr-xr-x 30 logan logan  4096 Feb 28 00:02 ..',
      '-rw-rw-r--  1 logan logan    73 Feb 28 00:16 execxi.sublime-project',
      '-rw-rw-r--  1 logan logan   154 Feb 28 01:16 .npmignore',
      '-rw-rw-r--  1 logan logan   154 Feb 28 02:02 .gitignore',
      '-rw-rw-r--  1 logan logan 44835 Feb 28 06:44 execxi.sublime-workspace',
      '-rw-rw-r--  1 logan logan   102 Mar  1 18:21 binding.gyp',
      'drwxrwxr-x  2 logan logan  4096 Mar  1 20:42 tests',
      'drwxrwxr-x  3 logan logan  4096 Mar  1 20:50 build',
      '-rw-rw-r--  1 logan logan   837 Mar  1 21:26 package.json',
      '-rw-rw-r--  1 logan logan 13055 Mar  1 22:11 exec_all.cpp',
      '-rw-rw-r--  1 logan logan 24505 Mar  1 22:37 README.md',
      '-rw-rw-r--  1 logan logan 21419 Mar  1 22:41 test.html',
      '-rw-rw-r--  1 logan logan 18778 Mar  1 22:41 test.log',
      '-rw-rw-r--  1 logan logan   180 Mar  1 22:43 Makefile',
      'drwxrwxr-x  5 logan logan  4096 Mar  1 22:44 .',
      '-rw-rw-r--  1 logan logan  1780 Mar  1 22:47 test.js',
      'drwxrwxr-x  8 logan logan  4096 Mar  1 22:47 .git' ],
    exit_code: 0 ],
  [ output: [ 'Exit 0' ], exit_code: 0 ],
  [ output: [ 'Exit 1' ], exit_code: 1 ],
  max: 8,
  ran: 5,
  failed: 1,
  passed: 4 ]

￭ Running Command [ 1/8 ]
----------------------------------------

binding.gyp
build
exec_all.cpp
execxi.sublime-project
execxi.sublime-workspace
Makefile
package.json
README.md
test.html
test.js
test.log
tests

✔ Command [ 1/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 2/8 ]
----------------------------------------

Works

✔ Command [ 2/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 3/8 ]
----------------------------------------

total 272
drwxr-xr-x 30 logan logan  4096 Feb 28 00:02 ..
-rw-rw-r--  1 logan logan    73 Feb 28 00:16 execxi.sublime-project
-rw-rw-r--  1 logan logan   154 Feb 28 01:16 .npmignore
-rw-rw-r--  1 logan logan   154 Feb 28 02:02 .gitignore
-rw-rw-r--  1 logan logan 44835 Feb 28 06:44 execxi.sublime-workspace
-rw-rw-r--  1 logan logan   102 Mar  1 18:21 binding.gyp
drwxrwxr-x  2 logan logan  4096 Mar  1 20:42 tests
drwxrwxr-x  3 logan logan  4096 Mar  1 20:50 build
-rw-rw-r--  1 logan logan   837 Mar  1 21:26 package.json
-rw-rw-r--  1 logan logan 13055 Mar  1 22:11 exec_all.cpp
-rw-rw-r--  1 logan logan 24505 Mar  1 22:37 README.md
-rw-rw-r--  1 logan logan 21419 Mar  1 22:41 test.html
-rw-rw-r--  1 logan logan 18778 Mar  1 22:41 test.log
-rw-rw-r--  1 logan logan   180 Mar  1 22:43 Makefile
drwxrwxr-x  5 logan logan  4096 Mar  1 22:44 .
-rw-rw-r--  1 logan logan  1780 Mar  1 22:47 test.js
drwxrwxr-x  8 logan logan  4096 Mar  1 22:47 .git

✔ Command [ 3/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 4/8 ]
----------------------------------------

Exit 0

✔ Command [ 4/8 ] exited with 0.
----------------------------------------


￭ Running Command [ 5/8 ]
----------------------------------------

Exit 1

▲ Command [ 5/8 ] exited with 1.
----------------------------------------


￭ Running Command [ 6/8 ]
----------------------------------------

Exit 2

▲ Command [ 6/8 ] exited with 2.
----------------------------------------


￭ Running Command [ 7/8 ]
----------------------------------------


▲ Command [ 7/8 ] exited with 127.
----------------------------------------


￭ Running Command [ 8/8 ]
----------------------------------------

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec mattis nisi at justo elementum fermentum. Donec tincidunt, lectus nec bibendum sagittis, lectus purus placerat libero, quis varius tellus magna nec felis. Phasellus non lobortis velit. Suspendisse eget lorem neque. Donec sem risus, feugiat eu pulvinar eu, elementum a dui. Suspendisse sed urna non lacus luctus dapibus. Curabitur tristique nunc ac nibh cursus dignissim eleifend mauris ullamcorper. Ut mauris est, venenatis quis rutrum at, facilisis non massa. Praesent imperdiet neque at augue egestas bibendum. Sed eu elit eget felis iaculis pretium. Donec sagittis pulvinar diam a sagittis. Aenean eu tincidunt nunc. Proin imperdiet pellentesque diam a adipiscing. Curabitur eget velit a lectus varius ornare. Nullam bibendum rutrum dignissim. Phasellus posuere scelerisque imperdiet. Integer faucibus consectetur semper. Aenean nibh neque, ornare vel molestie eget, pellentesque accumsan orci. Vivamus at interdum risus. Ut quis odio est, quis faucibus libero. Curabitur gravida condimentum pharetra. Quisque ut ipsum augue, vulputate porttitor justo. In hac habitasse platea dictumst. Sed ut quam odio. Maecenas at mauris quam, id hendrerit ipsum. Nam ut lacus orci. Suspendisse arcu libero, gravida vel posuere dapibus, bibendum vitae libero. Fusce non turpis velit, in tristique nisl. Etiam a tellus ac enim fermentum pellentesque. Mauris cursus, tortor et venenatis varius, orci leo convallis sem, et pellentesque purus velit non orci. Fusce sit amet interdum sem. Ut quis sapien sapien. Etiam luctus nibh non turpis euismod vitae porttitor lacus dictum. Duis nec turpis id tortor imperdiet adipiscing eget et erat. Fusce ultrices mattis urna at suscipit. Vivamus eget risus vestibulum enim posuere sollicitudin consequat eget nisl. Quisque neque nisi, molestie et gravida vel, pretium quis mauris. Aenean nec vehicula lorem. Sed eget porttitor neque. Nunc leo ligula, aliquet eget lacinia et, sollicitudin eget erat. In elementum viverra sodales. Curabitur dui ligula, iaculis sit amet fermentum quis, pharetra quis magna. Praesent ornare consequat felis, at mollis neque mollis quis. Fusce nec ipsum turpis, vitae vehicula lacus. Vestibulum nulla elit, convallis non sodales id, tristique sed arcu. Nulla ligula est, lacinia aliquet faucibus nec, congue gravida nunc. Nunc pellentesque tristique adipiscing. Pellentesque orci leo, rhoncus quis elementum non, elementum bibendum magna. Fusce dignissim sodales neque sit amet luctus. Integer ac urna nec est aliquam auctor quis et urna. In ornare velit vitae risus vehicula hendrerit. Duis semper, massa quis rhoncus sagittis, nunc eros egestas neque, sit amet auctor lacus nibh vel leo. Phasellus non nisi eu ipsum scelerisque mattis vitae vel mauris. Phasellus a mauris a sem pellentesque porttitor dapibus at massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Aenean id augue nisl, in semper eros. Ut fermentum ipsum eu metus tempor porta. In consectetur est vitae ligula porta non condimentum libero mattis. Mauris imperdiet vehicula lacus lobortis pharetra. Sed pretium lorem non elit posuere sagittis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Fusce sollicitudin enim euismod tortor feugiat vitae faucibus turpis varius. Pellentesque sed sagittis dolor. Aenean egestas augue in urna lobortis cursus congue mi vulputate. Donec mollis porttitor massa vitae vulputate. Ut in lobortis nisi. Proin sagittis arcu urna. Sed ut tincidunt mi. Duis eu odio eu velit tincidunt pellentesque. Donec vitae placerat eros. Etiam scelerisque euismod risus, sed pretium eros varius a. Praesent luctus facilisis tellus sed tincidunt. Maecenas ac turpis eu mauris malesuada aliquam. Sed mauris eros, lacinia non cursus id, rhoncus congue purus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Vivamus molestie tincidunt ligula sed fringilla. Vestibulum mauris nisi, molestie adipiscing mollis sed, fringilla scelerisque dui. Donec euismod, nibh sed pretium venenatis, dui lectus porttitor tortor, sit amet bibendum velit nulla vitae enim. Aliquam turpis massa, commodo vel elementum suscipit, pretium et quam. Aliquam erat volutpat. Integer aliquet nibh at neque adipiscing id tempor diam placerat. Ut non neque at massa dapibus cursus eu quis neque. Phasellus ut lectus ac massa malesuada mollis lobortis at felis. Proin et dolor nec nisl tristique adipiscing sed id nulla. Fusce dapibus neque vel tellus posuere vitae dignissim enim faucibus. Curabitur egestas vulputate justo, sed faucibus quam blandit imperdiet. Nunc et turpis elementum mi iaculis ultricies vitae eu nisl. Ut non magna dui, at vehicula velit. Ut a enim arcu. Cras fermentum lobortis justo, sed porta nisl dictum nec. Donec elementum feugiat erat, venenatis commodo libero bibendum imperdiet. Aliquam erat volutpat. Cras auctor mattis dui, in ultricies sem vehicula eu. Phasellus vel dignissim posuere.

✔ Command [ 8/8 ] exited with 0.
----------------------------------------



----------------------------------------
----------------------------------------
-               SUMMARY                -
----------------------------------------

  ￭ Ran 8/8 commands.

----------------------------------------

  ✔ Passed: 5 commands:
  ✔ #1 #2 #3 #4 #8 

----------------------------------------

  ✗ Failed: 3 commands:
  ✗ #5 #6 #7 

----------------------------------------

----------------------------------------
----------------------------------------

[ false,
  [ output: [ 'binding.gyp',
      'build',
      'exec_all.cpp',
      'execxi.sublime-project',
      'execxi.sublime-workspace',
      'Makefile',
      'package.json',
      'README.md',
      'test.html',
      'test.js',
      'test.log',
      'tests' ],
    exit_code: 0 ],
  [ output: [ 'Works' ], exit_code: 0 ],
  [ output: [ 'total 272',
      'drwxr-xr-x 30 logan logan  4096 Feb 28 00:02 ..',
      '-rw-rw-r--  1 logan logan    73 Feb 28 00:16 execxi.sublime-project',
      '-rw-rw-r--  1 logan logan   154 Feb 28 01:16 .npmignore',
      '-rw-rw-r--  1 logan logan   154 Feb 28 02:02 .gitignore',
      '-rw-rw-r--  1 logan logan 44835 Feb 28 06:44 execxi.sublime-workspace',
      '-rw-rw-r--  1 logan logan   102 Mar  1 18:21 binding.gyp',
      'drwxrwxr-x  2 logan logan  4096 Mar  1 20:42 tests',
      'drwxrwxr-x  3 logan logan  4096 Mar  1 20:50 build',
      '-rw-rw-r--  1 logan logan   837 Mar  1 21:26 package.json',
      '-rw-rw-r--  1 logan logan 13055 Mar  1 22:11 exec_all.cpp',
      '-rw-rw-r--  1 logan logan 24505 Mar  1 22:37 README.md',
      '-rw-rw-r--  1 logan logan 21419 Mar  1 22:41 test.html',
      '-rw-rw-r--  1 logan logan 18778 Mar  1 22:41 test.log',
      '-rw-rw-r--  1 logan logan   180 Mar  1 22:43 Makefile',
      'drwxrwxr-x  5 logan logan  4096 Mar  1 22:44 .',
      '-rw-rw-r--  1 logan logan  1780 Mar  1 22:47 test.js',
      'drwxrwxr-x  8 logan logan  4096 Mar  1 22:47 .git' ],
    exit_code: 0 ],
  [ output: [ 'Exit 0' ], exit_code: 0 ],
  [ output: [ 'Exit 1' ], exit_code: 1 ],
  [ output: [ 'Exit 2' ], exit_code: 2 ],
  [ output: [], exit_code: 127 ],
  [ output: [ 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec mattis nisi at justo elementum fermentum. Donec tincidunt, lectus nec bibendum sagittis, lectus purus placerat libero, quis varius tellus magna nec felis. Phasellus non lobortis velit. Suspendisse eget lorem neque. Donec sem risus, feugiat eu pulvinar eu, elementum a dui. Suspendisse sed urna non lacus luctus dapibus. Curabitur tristique nunc ac nibh cursus dignissim eleifend mauris ullamcorper. Ut mauris est, venenatis quis rutrum at, facilisis non massa. Praesent imperdiet neque at augue egestas bibendum. Sed eu elit eget felis iaculis pretium. Donec sagittis pulvinar diam a sagittis. Aenean eu tincidunt nunc. Proin imperdiet pellentesque diam a adipiscing. Curabitur eget velit a lectus varius ornare. Nullam bibendum rutrum dignissim. Phasellus posuere scelerisque imperdiet. Integer faucibus consectetur semper. Aenean nibh neque, ornare vel molestie eget, pellentesque accumsan orci. Vivamus at interdum risus. Ut quis odio est, quis faucibus libero. Curabitur gravida condimentum pharetra. Quisque ut ipsum augue, vulputate porttitor justo. In hac habitasse platea dictumst. Sed ut quam odio. Maecenas at mauris quam, id hendrerit ipsum. Nam ut lacus orci. Suspendisse arcu libero, gravida vel posuere dapibus, bibendum vitae libero. Fusce non turpis velit, in tristique nisl. Etiam a tellus ac enim fermentum pellentesque. Mauris cursus, tortor et venenatis varius, orci leo convallis sem, et pellentesque purus velit non orci. Fusce sit amet interdum sem. Ut quis sapien sapien. Etiam luctus nibh non turpis euismod vitae porttitor lacus dictum. Duis nec turpis id tortor imperdiet adipiscing eget et erat. Fusce ultrices mattis urna at suscipit. Vivamus eget risus vestibulum enim posuere sollicitudin consequat eget nisl. Quisque neque nisi, molestie et gravida vel, pretium quis mauris. Aenean nec vehicula lorem. Sed eget porttitor neque. Nunc leo ligula, aliquet eget lacinia et, sollicitudin eget erat. In elementum viverra sodales. Curabitur dui ligula, iaculis sit amet fermentum quis, pharetra quis magna. Praesent ornare consequat felis, at mollis neque mollis quis. Fusce nec ipsum turpis, vitae vehicula lacus. Vestibulum nulla elit, convallis non sodales id, tristique sed arcu. Nulla ligula est, lacinia aliquet faucibus nec, congue gravida nunc. Nunc pellentesque tristique adipiscing. Pellentesque orci leo, rhoncus quis elementum non, elementum bibendum magna. Fusce dignissim sodales neque sit amet luctus. Integer ac urna nec est aliquam auctor quis et urna. In ornare velit vitae risus vehicula hendrerit. Duis semper, massa quis rhoncus sagittis, nunc eros egestas neque, sit amet auctor lacus nibh vel leo. Phasellus non nisi eu ipsum scelerisque mattis vitae vel mauris. Phasellus a mauris a sem pellentesque porttitor dapibus at massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Aenean id augue nisl, in semper eros. Ut fermentum ipsum eu metus tempor porta. In consectetur est vitae ligula porta non condimentum libero mattis. Mauris imperdiet vehicula lacus lobortis pharetra. Sed pretium lorem non elit posuere sagittis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Fusce sollicitudin enim euismod tortor feugiat vitae faucibus turpis varius. Pellentesque sed sagittis dolor. Aenean egestas augue in urna lobortis cursus congue mi vulputate. Donec mollis porttitor massa vitae vulputate. Ut in lobortis nisi. Proin sagittis arcu urna. Sed ut tincidunt mi. Duis eu odio eu velit tincidunt pellentesque. Donec vitae placerat eros. Etiam scelerisque euismod risus, sed pretium eros varius a. Praesent luctus facilisis tellus sed tincidunt. Maecenas ac turpis eu mauris malesuada aliquam. Sed mauris eros, lacinia non cursus id, rhoncus congue purus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Vivamus molestie tincidunt ligula sed fringilla. Vestibulum mauris nisi, molestie adipiscing mollis sed, fringilla scelerisque dui. Donec euismod, nibh sed pretium venenatis, dui lectus porttitor tortor, sit amet bibendum velit nulla vitae enim. Aliquam turpis massa, commodo vel elementum suscipit, pretium et quam. Aliquam erat volutpat. Integer aliquet nibh at neque adipiscing id tempor diam placerat. Ut non neque at massa dapibus cursus eu quis neque. Phasellus ut lectus ac massa malesuada mollis lobortis at felis. Proin et dolor nec nisl tristique adipiscing sed id nulla. Fusce dapibus neque vel tellus posuere vitae dignissim enim faucibus. Curabitur egestas vulputate justo, sed faucibus quam blandit imperdiet. Nunc et turpis elementum mi iaculis ultricies vitae eu nisl. Ut non magna dui, at vehicula velit. Ut a enim arcu. Cras fermentum lobortis justo, sed porta nisl dictum nec. Donec elementum feugiat erat, venenatis commodo libero bibendum imperdiet. Aliquam erat volutpat. Cras auctor mattis dui, in ultricies sem vehicula eu. Phasellus vel dignissim posuere.' ],
    exit_code: 0 ],
  max: 8,
  ran: 8,
  failed: 3,
  passed: 5 ]
Lets only run this one if the previous one had a 100% pass
Not running this: previous one did not have a 100% pass

```
## Building and Testing
[Back To Top](#execxi-)

I have packaged a `Makefile`, `Gruntfile` for building and testing, and `npm` scripts point to those.

Available commands are:

- `make` (Aliases: `npm run-script preinstall`) : 
  Compiles the C++ code into node extension.

- `make clean` (Aliases: `npm run-script preuninstall`):
  Removes the `build` directory.

- `node test` (Aliases: `make test`) : 
  This is for visual testing rather than unit testing. 

- `grunt test`  (Aliases: `grunt`; `npm test`): 
  This is for unit testing. 


## Change Log

### V1.3.0 22/Aug/2014

- Removed CVV8 (V8-Juice) and wrote alternative type casting solutions.
- Fixed #14

## Legal mambo jambo

[Back To Top](#execxi-)

If you would mention WeaponXI in your source code or under credits or something it would mean the world to me!

Copyright © 2012 - 2013 WeaponXI <aponxi@weaponxi.com>
This software is licensed under [MIT License](http://aponxi.mit-license.org/).
