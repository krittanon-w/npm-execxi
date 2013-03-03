var execxi = require("../build/Release/execxi.node");

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
// I get the commands I want to run to commands array.
var commands = Array();

commands = commands.concat(regular, exit_codes,non_existent, long_text);

// Right now we have array of 8 commands to run

// lets run in chained mode off to observe
var res1 = execxi.executeArray(commands, {"chained": false, "verbose":false});

// conducting some tests on this
exports.longTest = function(test){
    // console.log("\nTesting to see if a line that is 5000 characters long will be stored in result array in one line.");
    test.equal("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec mattis nisi at justo elementum fermentum. Donec tincidunt, lectus nec bibendum sagittis, lectus purus placerat libero, quis varius tellus magna nec felis. Phasellus non lobortis velit. Suspendisse eget lorem neque. Donec sem risus, feugiat eu pulvinar eu, elementum a dui. Suspendisse sed urna non lacus luctus dapibus. Curabitur tristique nunc ac nibh cursus dignissim eleifend mauris ullamcorper. Ut mauris est, venenatis quis rutrum at, facilisis non massa. Praesent imperdiet neque at augue egestas bibendum. Sed eu elit eget felis iaculis pretium. Donec sagittis pulvinar diam a sagittis. Aenean eu tincidunt nunc. Proin imperdiet pellentesque diam a adipiscing. Curabitur eget velit a lectus varius ornare. Nullam bibendum rutrum dignissim. Phasellus posuere scelerisque imperdiet. Integer faucibus consectetur semper. Aenean nibh neque, ornare vel molestie eget, pellentesque accumsan orci. Vivamus at interdum risus. Ut quis odio est, quis faucibus libero. Curabitur gravida condimentum pharetra. Quisque ut ipsum augue, vulputate porttitor justo. In hac habitasse platea dictumst. Sed ut quam odio. Maecenas at mauris quam, id hendrerit ipsum. Nam ut lacus orci. Suspendisse arcu libero, gravida vel posuere dapibus, bibendum vitae libero. Fusce non turpis velit, in tristique nisl. Etiam a tellus ac enim fermentum pellentesque. Mauris cursus, tortor et venenatis varius, orci leo convallis sem, et pellentesque purus velit non orci. Fusce sit amet interdum sem. Ut quis sapien sapien. Etiam luctus nibh non turpis euismod vitae porttitor lacus dictum. Duis nec turpis id tortor imperdiet adipiscing eget et erat. Fusce ultrices mattis urna at suscipit. Vivamus eget risus vestibulum enim posuere sollicitudin consequat eget nisl. Quisque neque nisi, molestie et gravida vel, pretium quis mauris. Aenean nec vehicula lorem. Sed eget porttitor neque. Nunc leo ligula, aliquet eget lacinia et, sollicitudin eget erat. In elementum viverra sodales. Curabitur dui ligula, iaculis sit amet fermentum quis, pharetra quis magna. Praesent ornare consequat felis, at mollis neque mollis quis. Fusce nec ipsum turpis, vitae vehicula lacus. Vestibulum nulla elit, convallis non sodales id, tristique sed arcu. Nulla ligula est, lacinia aliquet faucibus nec, congue gravida nunc. Nunc pellentesque tristique adipiscing. Pellentesque orci leo, rhoncus quis elementum non, elementum bibendum magna. Fusce dignissim sodales neque sit amet luctus. Integer ac urna nec est aliquam auctor quis et urna. In ornare velit vitae risus vehicula hendrerit. Duis semper, massa quis rhoncus sagittis, nunc eros egestas neque, sit amet auctor lacus nibh vel leo. Phasellus non nisi eu ipsum scelerisque mattis vitae vel mauris. Phasellus a mauris a sem pellentesque porttitor dapibus at massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Aenean id augue nisl, in semper eros. Ut fermentum ipsum eu metus tempor porta. In consectetur est vitae ligula porta non condimentum libero mattis. Mauris imperdiet vehicula lacus lobortis pharetra. Sed pretium lorem non elit posuere sagittis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Fusce sollicitudin enim euismod tortor feugiat vitae faucibus turpis varius. Pellentesque sed sagittis dolor. Aenean egestas augue in urna lobortis cursus congue mi vulputate. Donec mollis porttitor massa vitae vulputate. Ut in lobortis nisi. Proin sagittis arcu urna. Sed ut tincidunt mi. Duis eu odio eu velit tincidunt pellentesque. Donec vitae placerat eros. Etiam scelerisque euismod risus, sed pretium eros varius a. Praesent luctus facilisis tellus sed tincidunt. Maecenas ac turpis eu mauris malesuada aliquam. Sed mauris eros, lacinia non cursus id, rhoncus congue purus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Vivamus molestie tincidunt ligula sed fringilla. Vestibulum mauris nisi, molestie adipiscing mollis sed, fringilla scelerisque dui. Donec euismod, nibh sed pretium venenatis, dui lectus porttitor tortor, sit amet bibendum velit nulla vitae enim. Aliquam turpis massa, commodo vel elementum suscipit, pretium et quam. Aliquam erat volutpat. Integer aliquet nibh at neque adipiscing id tempor diam placerat. Ut non neque at massa dapibus cursus eu quis neque. Phasellus ut lectus ac massa malesuada mollis lobortis at felis. Proin et dolor nec nisl tristique adipiscing sed id nulla. Fusce dapibus neque vel tellus posuere vitae dignissim enim faucibus. Curabitur egestas vulputate justo, sed faucibus quam blandit imperdiet. Nunc et turpis elementum mi iaculis ultricies vitae eu nisl. Ut non magna dui, at vehicula velit. Ut a enim arcu. Cras fermentum lobortis justo, sed porta nisl dictum nec. Donec elementum feugiat erat, venenatis commodo libero bibendum imperdiet. Aliquam erat volutpat. Cras auctor mattis dui, in ultricies sem vehicula eu. Phasellus vel dignissim posuere.", res1[8].output[0]);
    test.done();
};
var res2 = execxi.executeArray(commands, {"chained": true, "verbose":false});
exports.optionChained = function(test){
    // console.log("\nChecking if Chained option works.");
    test.equal(5, res2.ran);
    test.done();
};

var res3 = execxi.executeArray(exit_codes, {"chained": true, "exitSuccess":[0,1], "verbose":false});
exports.optionExitSuccess = function(test){
    // console.log("\nChecking if Chained option works.");
    test.equal(1, res3.failed);
    test.done();
};
var res4 = execxi.executeArray(exit_codes, {"chained": true, "exitSuccess":[0,1,2], "verbose":false});
exports.optionExitSuccess2 = function(test){
    // console.log("\nChecking if Chained option works.");
    test.equal(0, res4.failed);
    test.done();
};

var res4 = execxi.executeArray(exit_codes, {"chained": true, "exitSuccess":[0,1,2], "prettyPrint":false});
exports.visualTest_PrettyPrint = function(test){
    // console.log("\nChecking if Chained option works.");
    test.equal(0, res4.failed);
    test.done();
};

var res4 = execxi.executeArray(exit_codes, {"chained": true, "exitSuccess":[0,1,2], "verbose":false});
exports.visualTest_Verbose = function(test){
    // console.log("\nChecking if Chained option works.");
    test.equal(0, res4.failed);
    test.done();
};