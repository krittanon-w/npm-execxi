module.exports = (grunt) ->
  grunt.loadNpmTasks('grunt-contrib-nodeunit');
  #Project configuration.
  grunt.initConfig(
    nodeunit: 
      all: ['tests/*_test.js']
  )
  grunt.registerTask('test', ["nodeunit"]);
  grunt.registerTask('default', ["test"]);