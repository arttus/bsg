<!-- @file Instructions for subtheming using the Sass Starterkit. -->
<!-- @defgroup subtheme_sass -->
<!-- @ingroup subtheme -->

# SASS Starterkit

Below are instructions on how to create a Bootstrap sub-theme using a SASS
preprocessor.

- [Requirements](#requirements)
- [Setup](#setup)
- [Compiling - Using NPM, Bower & Grunt](#npm)
- [Override Styles](#styles)
- [Override Settings](#settings)
- [Override Templates and Theme Functions](#registry)

## Requirements {#requirements}
This starter theme assumes that you have:
- Bootstrap in your themes folder (This is based off of this theme)
- Jquery 1.9.1 or higher (Use jQuery_Update module for Drupal)
- NPM (Node Package Manager) (NPM Version 2.x or greater)
- Grunt, Gulp or Compass installed in your dev enviroment.


## Setup {#setup}
The instructions provided here are for getting your theme setup using Grunt.
First you will need a functional NodeJS, NPM Grunt installations in your dev enviroment.
Download this project into your sites/all/themes folder of your Drupal
installation.

-  Run `npm install`

## Using NPM, Grunt or Gulp in workflow {#npm}

Next run `grunt copy` to move bootstrap-sass and font-awesome to the assets directory.

Next run `grunt init` to compile SASS for the first time into the css folder.

{.alert.alert-warning} **WARNING:** Do not modify the files inside of
`./subtheme/bootstrap-sass` directly. Doing so may cause issues when upgrading
the [Bootstrap Framework] in the future.

You can now edit the files in the /sass folder to make changes. Start by
reviewing and editing variables in the /sass/base/_variable-overrides.scss file.

After you've run the initial `grunt init` you can then use `grunt watch` to
continuously watch the sass folder for changes, or you can run `grunt sass`
to just do a single  run and compile the sass.

Adding Browsersync to workflow

- Install the Drupal browsersync module from
https://www.drupal.org/project/browsersync
- In "Themes" -> "Appearance" -> "Settings" scroll down and enable browsersync
for the Bootstrap Sass Starterkit Theme.
- Edit the proxy IP in the gruntfile.js file to match the IP or hostname of
your Drupal website.
- Run `grunt browsersync` (Watches the sass folder, and sets up a browsersync
session.)

## Override Styles {#styles}
The `./subtheme/sass/_variable-overrides.scss` file is generally where you will
the majority of your time overriding the variables provided by the [Bootstrap
Framework].

The `./subtheme/sass/_bootstrap.scss` file is nearly an exact copy from the
[Bootstrap Framework Source Files]. The only difference is that it injects the
`_variable-overrides.scss` file directly before it has imported the[Bootstrap
Framework]'s `_variables.scss` file. This allows you to easily override
variables without having to constantly keep up with newer or missing variables
during an upgrade.

The `./subtheme/sass/_overrides.scss` file contains various Drupal overrides to
properly integrate with the [Bootstrap Framework]. It may contain a few
enhancements, feel free to edit this file as you see fit.

The `./subtheme/sass/{{machine_name}}.style.scss` file is the glue that combines the
`_bootstrap.scss` and `_overrides.scss` files together. Generally, you will not
need to modify this file unless you need to add or remove files to be imported.
This is the file that you should compile to `./subtheme/css/{{machine_name}}.styles.css` (note
the same file name, using a different extension of course).

## Override Theme Settings {#settings}
Please refer to the @link subtheme_settings Sub-theme Settings @endlink topic.

## Override Templates and Theme Functions {#registry}
Please refer to the @link registry Theme Registry @endlink topic.

[Bootstrap Framework]: http://getbootstrap.com
[Bootstrap Framework Source Files]: https://github.com/twbs/bootstrap/releases
[SASS]: http://sass-lang.com/

## Caveats 
We have included a npm_post.sh file until this issue is fixed in Drupal Core https://www.drupal.org/node/2349457
If you still run into Segfaults you may find running this command in the root of your theme
the quickest fix.

'find node_modules -type f -name '*.info' | xargs rm;'