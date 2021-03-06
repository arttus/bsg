<?php
/**
 * @file
 * Helper functions for the {{machine_name}} theme.
 */

/**
 * Returns Bootstrap panel classes.
 */
function _{{machine_name}}_get_bootstrap_panel_classes() {
  return array(
    'panel-default',
    'panel-primary',
    'panel-success',
    'panel-info',
    'panel-warning',
    'panel-danger'
  );
}

/**
 * Returns the current active theme.
 */
function _{{machine_name}}_current_theme() {
  global $custom_theme, $theme;

  if (!empty($custom_theme)) {
    $current_theme = $custom_theme;
  }
  else {
    $current_theme = $theme ? $theme : variable_get('theme_default', 'garland');
  }

  return $current_theme;
}

/**
 * Returns a menu built for rendering as a dropdown menu.
 */
function _{{machine_name}}_dropdown_menu_tree($menu_name, $options = array()) {
  $menu_tree = menu_build_tree($menu_name, $options);
  $element = menu_tree_output($menu_tree);
  $element['#theme_wrappers'] = array();
  foreach (element_children($element) as $mlid) {
    _{{machine_name}}_dropdown_menu_link_process($element[$mlid]);
  }
  return $element;
}

/**
 * Suggest the the menu link to render with a dropdown.
 */
function _{{machine_name}}_dropdown_menu_link_process(&$element) {
  //$element['theme_hook_suggestion'] = 'menu_link__dropdown';
  $element['#theme'] = 'menu_link__dropdown';
  if (!empty($element['#below'])) {
    foreach (element_children($element['#below']) as $mlid) {
      _{{machine_name}}_dropdown_menu_link_process($element['#below'][$mlid]);
    }
  }
}
