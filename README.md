# BSG Bootstrap Generator
BSG is a wrapper that is designed to generate a sub theme for Drupal. It has 
Bootstrap, Sass, Gulp, Grunt, Bower, Panels, BrowserSync and Font Awesome built-in.

Install the theme, set Bootstrap Generator to the default theme, then go to your 
terminal get into your drupal site and run the following command
drush bsg "My Subtheme" --bootswatch=cerulean.

# Quick Start
1. Download and enable Bootstrap Generator: 
`cd to sites/all/themes git `
`clone git@github.com:arttus/bsg.git`
`drush en bsg -y; drush vset theme_default bsg`

2. Create a subtheme: 
`drush cc all; drush bsg "Subtheme"`

3. Set default theme:
`drush en subtheme -y; drush vset theme_default subtheme`

Once you have generated your subtheme you will need follow the instructions in subtheme README.md

# Features
1. Components and plugins from Bootstrap.
2. Responsive Panels
5. Bootstrap, Sass, Gulp, Grunt, Bower, Panels, BrowserSync and Font Awesome built-in.
6. Drush intergration: drush bsg "My Subtheme".
8. Works with Bootswatch themes: drush bsg "My Subtheme" --bootswatch=cerulean.

# Links
* Project Page:    
* Documentation:   
* Demo:           
* Support:         

# Thanks
BSG Bootstrap Generator borrows heavily from the Radix theme, 
and is a basically wrapper for the work that Wrender has done 
cd around creating 
Bootstrap SASS theme to scratch his own itch with the Bootstrap 
base theme. I added native panels support.