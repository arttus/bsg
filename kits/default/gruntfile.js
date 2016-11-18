/**
 * @file
 * Defines grunt tasks to be run by Grunt task runner.
 */

/* eslint-env node */

module.exports = function (grunt) {
  'use strict';
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    copy: {
      main: {
        files: [
          // Vendor scripts.
          {  expand: true, cwd: 'node_modules/bootstrap-sass/', src: ['**'],  dest: 'assets/bootstrap-sass/' },
          {expand: true, cwd: 'node_modules/font-awesome/',  src: ['**'],  dest: 'assets/font-awesome/'  },
        ],
      },
    },
    // Compile SASS files into minified CSS.
    sass: {
      // options: {
      //   includePaths: ['assets/bootstrap-sass/assets/stylesheets']
      // },
      dist: {
        options: {
          outputStyle: 'compressed'
        },
        files: {
          'assets/css/{{machine_name}}.style.css': 'sass/{{machine_name}}.style.scss'
        }
      }
    },

    // Watch these files and notify of changes.
    watch: {
      grunt: {files: ['gruntfile.js']},

      sass: {
        files: [
          'sass/**/*.scss'
        ],
        tasks: ['sass']
      }
    },

    browserSync: {
      dev: {
        bsFiles: {
          src: [
            'assets/css/*.css'
          ]
        },
        options: {
          watchTask: true,
          proxy: "yoursite.dev"
        }
      }
    }

  });

  // Load externally defined tasks. //
  grunt.loadNpmTasks('grunt-sass');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-browser-sync');

  // Establish tasks we can run from the terminal. //
  grunt.registerTask('init', ['sass']);
  grunt.registerTask('default', ['watch']);
  grunt.registerTask('browsersync', ['browserSync', 'watch']);

};
