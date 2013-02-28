var exec_all = require("./build/Release/exec_all.node");

var long_commands = ["find ~/"];
var exit_codes = ["./tests/exit_0.sh","./tests/exit_1.sh","./tests/exit_2.sh"];
var non_existent = ["./tests/sadf.sh"];
var regular = Array("ls","echo \"Works\"", "ls -lart");

var tests_to_run = Array();
tests_to_run = tests_to_run.concat(regular, exit_codes,non_existent);


var res = exec_all.executeArray(tests_to_run);
console.dir(res);
var res = exec_all.executeArray(tests_to_run, false);
console.dir(res);