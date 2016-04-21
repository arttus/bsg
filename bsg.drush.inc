<?php
/**
 * @file
 * Contains Drush hooks. Inspired by Zen and Omega Tools.
 */

// BOOTSWATCH_URL
define('BOOTSWATCH_URL', 'https://github.com/arttus/bsg-bootswatch/archive/master.zip');

/**
 * Implements hook_drush_command().
 */
function bsg_drush_command() {
  $items = array();

  $items['bsg'] = array(
    'description' => 'Create a Bootstrap Generator subtheme.',
    'arguments' => array(
      'name'         => 'The name of your subtheme.',
    ),
    'options' => array(
      'machine_name' => 'The machine-readable name of your subtheme. This will be auto-generated from the human-readable name if ommited.',
      'description' => 'The description of your subtheme',
      'destination' => 'The destination of your subtheme. Defaults to "all" (sites/all/themes).',
      'kit' => 'The name or url of the starter kit to use. Defaults to "default".',
      'bootswatch' => 'The Bootswatch theme to use. See https://github.com/arttus/bsg-bootswatch.',
    ),
    'examples' => array(
      'drush bsg "My Theme"' => 'Creates a Bootstrap Generator subtheme called "My Theme", using the default options.',
      'drush bsg "My Theme" --machine_name=my_theme' => 'Creates a Bootstrap Generator subtheme called "My Theme" with a specific machine name.',
      'drush bsg "My Theme" --bootswatch=cerulean' => 'Creates a Bootstrap Generator subtheme called "My Theme" using Cerulean Bootswatch theme.',
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function bsg_drush_help($section) {
  switch ($section) {
    case 'drush:bsg':
      return dt('This command will create a Bootstrap Generator subtheme. See examples to get started.');
  }
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_bsg($name = NULL, $machine_name = NULL) {

  // If no $name provided, abort.
  if (!$name) {
    drush_print(dt('Theme name missing. See help using drush bsg --help.'));
    return;
  }

  // Determine the theme name.
  if (!isset($name)) {
    $name = drush_get_option('name');
  }

  // Determine the machine name.
  if (!isset($machine_name)) {
    $machine_name = drush_get_option('machine_name');
  }
  if (!$machine_name) {
    $machine_name = $name;
  }
  $machine_name = str_replace(' ', '_', strtolower($machine_name));
  $search = array(
    '/[^a-z0-9_]/', // Remove characters not valid in function names.
    '/^[^a-z]+/',   // Functions must begin with an alpha character.
  );
  $machine_name = preg_replace($search, '', $machine_name);

  // Description of subtheme.
  $description = (drush_get_option('description')) ? trim(drush_get_option('description')) : 'A theme based on Bootstrap.';

  // Determine the path to the new subtheme.
  $subtheme_path = 'sites/all/themes';
  if ($path = drush_get_option('path')) {
    $subtheme_path = drush_trim_path($path);
  }
  $subtheme_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . $subtheme_path . '/' . $machine_name);

  // Determine the kit to use.
  $kit = (drush_get_option('kit')) ? drush_trim_path(drush_get_option('kit')) : 'default';

  // Make a fresh copy of the kit.
  $kit_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'bsg') . '/kits/' . $kit);

  // Allow kits to be pulled from external urls.
  if (valid_url($kit, TRUE)) {
    $kit_url = $kit;
    $kit_name = 'kit';

    // Get kit name from kit url.
    if (preg_match("/\/bsg\-kit\-([a-z0-9\_]*)\//", $kit_url, $matches)) {
      $kit_name = $kit = $matches[1];
    }

    // Switch to a temp directory.
    $current_dir = getcwd();
    chdir(drush_tempdir());

    drush_print(dt('Downloading @kit_name from @kit_url...', array(
      '@kit_name' => (!empty($kit_name)) ? $kit_name . ' kit' : $kit_name,
      '@kit_url' => $kit_url,
    )));
    if ($filepath = drush_download_file($kit_url)) {
      $filename = basename($filepath);
      $dirname =  basename($filepath, '.zip');

      // Decompress the zip archive.
      drush_tarball_extract($filename, $dirname, TRUE);
      $kit_path = getcwd() . '/' . $dirname . '/bsg-kit-' . $kit_name . '-master';

      // Set working directory back to the previous working directory.
      chdir($current_dir);
    }
  }

  if (!is_dir(dirname($subtheme_path))) {
    drush_die(dt('The directory "!directory" was not found.', array('!directory' => dirname($subtheme_path))));
  }
  drush_op('drush_copy_dir', $kit_path, $subtheme_path);

  // Copy Bootswatch theme to bootswatch folder.
  if ($bootswatch = drush_get_option('bootswatch')) {
    // Switch to a temp directory.
    $current_dir = getcwd();
    chdir(drush_tempdir());

    if ($filepath = drush_download_file(BOOTSWATCH_URL)) {
      $filename = basename($filepath);
      $dirname =  basename($filepath, '.zip');

      // Decompress the zip archive.
      drush_tarball_extract($filename, $dirname, TRUE);

      // Copy bootswatch theme to subtheme.
      $bootswatch_path = $subtheme_path . '/scss/bootswatch/';
      drush_print($bootswatch_path);
      drush_move_dir($dirname . '/bsg-bootswatch-master/' . $bootswatch, $bootswatch_path, TRUE);
    }

    // Set working directory back to the previous working directory.
    chdir($current_dir);
  }

  // Alter the contents of the .info file based on the command options.
  $alterations = array(
    '{{Name}}' => $name,
    '{{Description}}' => $description,
    '{{machine_name}}' => $machine_name,
    'hidden = true' => '',
  );
  // drush_op('bsg_file_str_replace', $subtheme_info_file, array_keys($alterations), $alterations);

  // Replace all occurrences of '{{machine_name}}' with the machine name of our sub theme.
  $files_to_replace = array(
    $kit . '.info',
    'template.php',
    'package.json',
    'includes/admin.inc',
    'includes/block.inc',
    'includes/comment.inc',
    'includes/contrib.inc',
    'includes/field.inc',
    'includes/form.inc',
    'includes/maintenance.inc',
    'includes/menu.inc',
    'includes/panel.inc',
    'includes/structure.inc',
    'includes/theme.inc',
    'includes/user.inc',
    'includes/utilities.inc',
    'includes/view.inc',
    'gruntfile.js',
    'gulpfile.js',

    'scss/' . $kit . '.style.scss',
  );
  foreach ($files_to_replace as $file_to_replace) {
    drush_op('bsg_file_str_replace', $subtheme_path . '/' . $file_to_replace, array_keys($alterations), $alterations);
  }

  // Rename files.
  $files_to_rename = array(
    '{{kit}}.info',
    'scss/{{kit}}.style.scss',
    'scss/base/_{{kit}}.variables.scss',
    'js/{{kit}}.script.js',

  );
  foreach ($files_to_rename as $file_to_rename_path) {
    $file_original_path = $subtheme_path . '/' . str_replace('{{kit}}', $kit, $file_to_rename_path);
    $file_new_path = $subtheme_path . '/' . str_replace('{{kit}}', $machine_name, $file_to_rename_path);
    drush_op('rename', drush_normalize_path($file_original_path), drush_normalize_path($file_new_path));
  }

  // Notify user of the newly created theme.
  $message = 'Successfully created Bootstrap Generator subtheme "!name" created in: !path using the "!kit" kit';

  // Add bootstwatch to message.
  if ($bootswatch != '') {
    $message .= ' and the "!bootswatch" bootswatch theme. Follow the README.md in the subtheme to complete your theme build';
  }

  $message = dt($message . '.', array(
    '!name' => $name,
    '!path' => $subtheme_path,
    '!kit' => $kit,
    '!bootswatch' => $bootswatch,
  ));
  drush_print($message);
}


/**
 * Replace strings in a file.
 */
function bsg_file_str_replace($file_path, $find, $replace) {
  $file_path = drush_normalize_path($file_path);
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}