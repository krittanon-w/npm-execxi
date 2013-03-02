var execxi = require("./build/Release/execxi.node");

//require the extension/module/wtv
// var execxi = require("execxi");

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

// Right now we have array of 7 commands to run

// lets run in chained mode to observe
var res = execxi.executeArray(tests_to_run);
// lets see what it returns as a result array
console.dir(res);

// lets run without chained mode on, and also observe
var res = execxi.executeArray(tests_to_run, false);

// lets see what it returns as a result array
console.dir(res);