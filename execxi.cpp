/*
                                                   
                                             __    
       __     _____     ___     ___    __  _/\_\   
     /'__`\  /\ '__`\  / __`\ /' _ `\ /\ \/'\/\ \  
    /\ \L\.\_\ \ \L\ \/\ \L\ \/\ \/\ \\/>  </\ \ \ 
    \ \__/.\_\\ \ ,__/\ \____/\ \_\ \_\/\_/\_\\ \_\
     \/__/\/_/ \ \ \/  \/___/  \/_/\/_/\//\/_/ \/_/
                \ \_\                              
                 \/_/                              
                 
    Copyright (c) 2013 <Logan Howlett> <info@weaponxi.com>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#include <node/node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>

#include <cvv8/convert.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <set>
// #include "./execxi.h"
namespace cv = cvv8;
using namespace v8;



Handle<Value> executeArray(const Arguments& args) {
    HandleScope scope;
    // OPTIONS
    /////////////////////
    
    //
    // Chained (bool)
    //   If a command doesn't exit with 0 then we won't run the next command
    //   default: true
    bool Chained = true;
    
    //
    // returnOutput (bool)
    //  Lets say you know you are gonna cause some trouble when you return output
    //  or even you won't really use it, you can turn it off now.
    bool returnOutput = true;
    
    //
    // exitSuccess (std::set)
    //  The exit codes you want to allow
    std::set<int> exitSuccess;

    //
    // default values for prettyPrint
    bool prettyPrint = true;
    // these are formatting strings
    std::string 
      RESET, GREEN, CYAN, YELLOW, RED,
      TICK, BULLET, CROSS, TRIANGLE,
      LINE, UNDER, BOLD;

    //
    // verbose, output the command output and information
    bool Verbose = true; 




   // String _usage = "\nUsage: \n\texecuteArray(<Array>Commands, <Object>Options)";
    if (args.Length() != 1 && args.Length() != 2) {
    
        ThrowException(Exception::TypeError( String::New("Wrong number of arguments") ) );
        return scope.Close(Undefined());
    }
 
    if (!args[0]->IsArray()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments, need Array for Commands")));
        return scope.Close(Undefined());
    }

  //               __                                  
  //              /\ \__  __                           
  //   ___   _____\ \ ,_\/\_\    ___     ___     ____  
  //  / __`\/\ '__`\ \ \/\/\ \  / __`\ /' _ `\  /',__\ 
  // /\ \L\ \ \ \L\ \ \ \_\ \ \/\ \L\ \/\ \/\ \/\__, `\
  // \ \____/\ \ ,__/\ \__\\ \_\ \____/\ \_\ \_\/\____/
  //  \/___/  \ \ \/  \/__/ \/_/\/___/  \/_/\/_/\/___/ 
  //           \ \_\                                   
  //            \/_/    

    if (args.Length() == 2)
    {
      if (args[1]->IsObject())
      {
        // you must be passing options...
        // it must be an object


        Handle<Object> opt = Handle<Object>::Cast(args[1]);

        if (opt->Has(String::New("chained"))) {
          // you passed chained option
          if ((opt->Get(String::New("chained"))->IsBoolean())){
            // the chained option must be bool
            Handle<Value> _chained = opt->Get(String::New("chained"));
            Chained = cv::CastFromJS<bool>(_chained);

          } else {
            // chained is not bool, throw error
            ThrowException(Exception::TypeError(String::New("Wrong arguments, need boolean for chained option")));
            return scope.Close(Undefined());
          }
        }

        if (opt->Has(String::New("verbose"))) {
          // you passed verbose option
          if ((opt->Get(String::New("verbose"))->IsBoolean())){
            // the verbose option must be bool
            Handle<Value> _verbose = opt->Get(String::New("verbose"));
            Verbose = cv::CastFromJS<bool>(_verbose);

          } else {
            // chained is not bool, throw error
            ThrowException(Exception::TypeError(String::New("Wrong arguments, need boolean for chained option")));
            return scope.Close(Undefined());
          }
        }

        if (opt->Has(String::New("returnOutput"))) {
          //you passed returnOutput option

          if ((opt->Get(String::New("returnOutput"))->IsBoolean())){
            // the returnOutput option must be bool
            Handle<Value> _returnOutput = opt->Get(String::New("returnOutput"));
            returnOutput = cv::CastFromJS<bool>(_returnOutput);
          } else {
            // returnOutput option isn't bool, throw error
            ThrowException(Exception::TypeError(String::New("Wrong arguments, need boolean for returnOutput option")));
            return scope.Close(Undefined());
          }
        }

        if (opt->Has(String::New("exitSuccess"))) {
          //you passed exitSuccess option

          if ((opt->Get(String::New("exitSuccess"))->IsArray())){
            // the exitSuccess option must be Array
            Handle<Array>  _exitSuccess = Handle<Array>::Cast(opt->Get(String::New("exitSuccess")));
            for (int i = 0; i < _exitSuccess->Length(); i++) {

            // get the corresponding array element
            v8::Local<v8::Value> _e = _exitSuccess->Get(i);
            int __e = cv::CastFromJS<int>(_e);
            exitSuccess.insert(__e);
            }
          } else {
            // exitSuccess option isn't Array, throw error
            ThrowException(Exception::TypeError(String::New("Wrong arguments, need Array for exitSuccess option")));
            return scope.Close(Undefined());
          }
        }

        if (opt->Has(String::New("prettyPrint"))) {
          //you passed prettyPrint option

          if ((opt->Get(String::New("prettyPrint"))->IsBoolean())){
            // the prettyPrint option must be bool
            Handle<Value> _prettyPrint = opt->Get(String::New("prettyPrint"));
            prettyPrint = cv::CastFromJS<bool>(_prettyPrint);
            
            
          } else {
            // prettyPrint option isn't bool, throw error
            ThrowException(Exception::TypeError(String::New("Wrong arguments, need boolean for prettyPrint option")));
            return scope.Close(Undefined());
          }
        }

      } 
      else {
        // options must be object, if not, throw error
        ThrowException(Exception::TypeError(String::New("Wrong arguments, need Object for options")));
        return scope.Close(Undefined());
      }
    }
    // Default Options
    if (prettyPrint == true)
    {
          RESET     =   "\033[0m";
          GREEN     =   "\033[0;32m";
          CYAN      =   "\033[0;36m";
          YELLOW    =   "\033[0;33m";
          RED       =   "\033[0;31m";

          TICK      =   "\u2714";
          BULLET    =   "\uffed";
          CROSS     =   "\u2717";
          TRIANGLE  =   "\u25B2";

          LINE      =   "----------------------------------------";
          UNDER     =   "\033[4m";
          BOLD      =   "\033[1m";
    }
    else {

          RESET     =   "";
          GREEN     =   "";
          CYAN      =   "";
          YELLOW    =   "";
          RED       =   "";

          TICK      =   "\u2714";
          BULLET    =   "\uffed";
          CROSS     =   "\u2717";
          TRIANGLE  =   "\u25B2";

          LINE      =   "----------------------------------------";
          UNDER     =   "";
          BOLD      =   "";
    }

    //default exitSuccess
    if (exitSuccess.empty())
    {
      exitSuccess.insert(0);
    }
 
      Handle<Array> array = Handle<Array>::Cast(args[0]);
      // the number of commands to execute
      int max = array->Length();

      v8::Handle<v8::Array> result_array = v8::Array::New();
      //lets populate result array
      result_array->Set(cv::CastToJS("max"), cv::CastToJS(max));
      result_array->Set(cv::CastToJS("ran"), cv::CastToJS(0));
      result_array->Set(cv::CastToJS("failed"), cv::CastToJS(0));
      result_array->Set(cv::CastToJS("passed"), cv::CastToJS(0));
      result_array->Set(cv::CastToJS(0), True());
    std::stringstream  summary, passed_ones, failed_ones;
    for (int i = 0; i < array->Length(); i++) {

      // get the corresponding array element
      v8::Local<v8::Value> element = array->Get(i);

      //convert the array element to std::string
      std::string cmd = cv::CastFromJS<std::string>(element);
       
      // execxi class
      // ExecXI execxi;

      // we will store exit code here
      int exitcode;

      // for messages
      std::stringstream 
        current, 
        running, 
        exit_msg, 
        fatal_error;
      // for output of the command
      std::stringstream cmd_output;

        // current running command number
        // [ 1/10 ]
        current << "[ " << i+1 << "/" << max << " ]";

        // This will be echoed before runing command
        running 
          << std::endl << CYAN 
          << BULLET << " " << UNDER 
          << "Running Command" 
          << RESET << CYAN 
          << "\t"
          << current.str() 
          << std::endl << LINE 
          << RESET 
          << std::endl
          << std::endl;

        // Fatal error message
        fatal_error 
          << std::endl
          << RED
          << CROSS << " "
          << "Stopped at after running command #" << i+1 << ". Fatal Error when running the command."
          << RESET
          << std::endl
          << std::endl;

      //debug before cmd is run
      if (Verbose)
      {
        std::cout << running.str();
      }

      //Run the command
      // exitcode = execxi.run(cmd);

      FILE *in;
      char buff[16384];

      if(!(in = popen(cmd.c_str(), "r"))){
        // fatal error running command
        if (Verbose)
        {
          std::cout << fatal_error.str();
        }
        
      }


        // for array keys for storing outputs
        int line_n;
        line_n =0;
        // for storing outputs line by line
        v8::Handle<v8::Array> output_array = v8::Array::New();
      

      while(fgets(buff, sizeof(buff), in)!=NULL){
        if (Verbose)
        {
          std::cout << buff;
        }
        if (returnOutput) {
          //clear output
          cmd_output.str(std::string());
          // stream buffer to output
          cmd_output << buff;
          std::string str;
          str = cmd_output.str();

          // erase the last char if its a new line
          if (str[str.length()-1] == '\n')
          {
            str.erase(str.length()-1);
          }
          //testing
          // std::cout 
          //   << CYAN << "\n buffered output \n'"<< str
          //   << "'\n length: " << cmd_output.str().length()
          //   << "/" << str.length() << "\n" << RESET;

          // store output line by line here
          output_array->Set(cv::CastToJS(line_n), cv::CastToJS(str));
          line_n++;
        }

      }

      // std::cout << "\n buffered output \n"<< cmd_output.str()
      // << "\n length: " << cmd_output.str().length();

      exitcode = pclose(in);
      // Convert exit code from 16 bit
      exitcode = exitcode/256;

      

      

      //store result to array
        // ran this number of commands
        result_array->Set(cv::CastToJS("ran"), cv::CastToJS(i+1));
        // this command's exit code and output
          v8::Handle<v8::Array> this_command = v8::Array::New();
          if (returnOutput) {
            this_command->Set(cv::CastToJS("output"), output_array);
          }
          this_command->Set(cv::CastToJS("exit_code"), cv::CastToJS(exitcode));

        // store results
        result_array->Set(cv::CastToJS(i+1), this_command);
        // currently we have this many passed (exited with 0)
        int _passed = cv::CastFromJS<int>(result_array->Get(cv::CastToJS("passed")));
        // currently we have this many failed (exited with not 0)
        int _failed = cv::CastFromJS<int>(result_array->Get(cv::CastToJS("failed")));

        // checking if the exitcode is a success 
        // (default success code is 0, it can be supplied by user too)
        if (exitSuccess.find(exitcode) != exitSuccess.end())
        {
          // our command was exited with 0, so lets add that to passed 
          result_array->Set(cv::CastToJS("passed"), cv::CastToJS(_passed+1));
          // storing passed cmd to sstream
          passed_ones 
          << "#" << i+1 << " ";
          //debug after cmd is run
          exit_msg 
            << std::endl
            << GREEN
            << TICK << " "
            << "Command " << current.str() << " exited with " << exitcode << "."
            << std::endl << LINE
            << RESET
            << std::endl
            << std::endl;
          if (Verbose)
          {
            std::cout << exit_msg.str();
          }

        }
        else {
          //our command was exited with not 0, so lets add that to failed
          result_array->Set(cv::CastToJS("failed"), cv::CastToJS(_failed+1));
          //setting [0] to false since we have failed at least once
          result_array->Set(cv::CastToJS(0), False());

          // storing failed cmd to sstream
          failed_ones 
          << "#" << i+1 << " ";

          // if the chained option is true...
          if (Chained)
          {
            exit_msg 
              << std::endl
              << RED
              << CROSS << " "
              << "Command " << current.str() << " exited with: " << exitcode << ". "
              << "Stopped at after running command #" << i+1 << "."
              << std::endl << LINE
              << RESET
              << std::endl
              << std::endl;
            if (Verbose)
            {
              std::cout << exit_msg.str();
            }
            //we don't want to continue anymore 
            return scope.Close(result_array);
          } else {
            exit_msg 
              << std::endl
              << YELLOW
              << TRIANGLE << " "
              << "Command " << current.str() << " exited with " << exitcode << "."
              << std::endl << LINE
              << RESET
              << std::endl
              << std::endl;
            if (Verbose){
              std::cout << exit_msg.str();
            }
          }
        }


      
       
    }
  // finally we have this many passed (exited with 0)
  int _passed = cv::CastFromJS<int>(result_array->Get(cv::CastToJS("passed")));
  // finally we have this many failed (exited with not 0)
  int _failed = cv::CastFromJS<int>(result_array->Get(cv::CastToJS("failed")));
  // finally we have this many commands run 
  int _ran = cv::CastFromJS<int>(result_array->Get(cv::CastToJS("ran")));
  summary
    << std::endl
    << std::endl
    << CYAN << BOLD
    << LINE
    << std::endl
    << LINE
    << std::endl
    << "-               SUMMARY                -"
    << std::endl
    << LINE

    << RESET << CYAN
    << std::endl

    << std::endl
    << "  " << BULLET << " Ran " << _ran << "/" << max << " commands."
    << std::endl << std::endl
    << LINE
    << std::endl

    << std::endl
    << GREEN
    << "  " << TICK << " Passed: " << _passed << " commands:"
    << std::endl
    << "  " << TICK << " " << passed_ones.str()
    << std::endl << std::endl
    << LINE
    << std::endl

    << std::endl
    << RED
    << "  " << CROSS << " Failed: " << _failed << " commands:"
    << std::endl
    << "  " << CROSS << " " << failed_ones.str()
    << std::endl << std::endl
    << LINE
    << std::endl

    << CYAN << BOLD
    << std::endl
    << LINE
    << std::endl
    << LINE
    << std::endl

    << RESET
    << std::endl;
  if (Verbose)
  {
    std::cout << summary.str();
  }
  return scope.Close(result_array);
}
 
 
void init(Handle<Object> target) {
    target->Set(String::NewSymbol("executeArray"),
        FunctionTemplate::New(executeArray)->GetFunction());
}
NODE_MODULE(execxi, init)