<?php
/**
 * @file
 * Theme functions for {{machine_name}} + Bootstrap.
 */

/**
 * Implements hook_theme().
 */
function {{machine_name}}_theme(&$existing, $type, $theme, $path) {
  return array(
    '{{machine_name}}_dropdown' => array(
      'variables' => array(
        'links' => NULL,
        'attributes' => NULL,
        'wrapper' => NULL,
      ),
      'function' => 'theme_{{machine_name}}_dropdown',
    ),
    '{{machine_name}}_button_group' => array(
      'variables' => array(
        'buttons' => NULL,
        'attributes' => NULL,
      ),
      'function' => 'theme_{{machine_name}}_button_group',
    ),
    '{{machine_name}}_button_dropdown' => array(
      'variables' => array(
        'button' => NULL,
        'links' => NULL,
        'split' => NULL,
        'attributes' => NULL,
      ),
      'function' => 'theme_{{machine_name}}_button_dropdown',
    ),
    '{{machine_name}}_modal' => array(
      'variables' => array(
        'header' => NULL,
        'content' => NULL,
        'buttons' => NULL,
      ),
      'template' => 'templates/other/{{machine_name}}-modal',
    ),
    '{{machine_name}}_tabs' => array(
      'variables' => array(
        'tabs' => NULL,
        'type' => NULL,
      ),
      'template' => 'templates/other/{{machine_name}}-tabs',
    ),
    '{{machine_name}}_grid' => array(
      'variables' => array(
        'items' => NULL,
      ),
      'template' => 'templates/other/{{machine_name}}-grid',
    ),
    '{{machine_name}}_alert' => array(
      'variables' => array(
        'text' => NULL,
        'type' => 'status',
      ),
    ),
    '{{machine_name}}_icon' => array(
      'variables' => array(
        'icon' => NULL,
        'text' => NULL,
        'link' => NULL,
      ),
      'function' => 'theme_{{machine_name}}_icon',
    ),
  );
}

/**
 * Implements theme_{{machine_name}}_dropdown().
 */
function theme_{{machine_name}}_dropdown($variables) {
  $links = $variables['links'];
  $attributes = (isset($variables['attributes'])) ? $variables['attributes'] : array();
  $wrapper = (isset($variables['wrapper'])) ? $variables['wrapper'] : FALSE;
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('dropdown-menu')));

  if ($wrapper) {
    $output .= '<div class="dropdown">';
  }
  $output .= '<ul' . drupal_attributes($attributes) . '>';

  $num_links = count($links);
  $i = 1;

  foreach ($links as $key => $link) {
    $class = array($key);

    // Add first, last and active classes to the list of links.
    if ($i == 1) {
      $class[] = 'first';
    }
    if ($i == $num_links) {
      $class[] = 'last';
    }

    // If empty, render as divider.
    if (empty($link)) {
      $output .= '<li class="divider"></li>';
      $i++;
      continue;
    }

    if (isset($link['href']) && ($link['href'] == $_GET['q']
        || ($link['href'] == '<front>' && drupal_is_front_page()))) {
      $class[] = 'active';
    }

    // Add a disabled option.
    if (isset($link['disabled']) && $link['disabled']) {
      $class[] = 'disabled';
    }

    $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

    if (isset($link['href'])) {
      // Pass in $link as $options, they share the same keys.
      $output .= l($link['title'], $link['href'], $link);
    }
    elseif (!empty($link['title'])) {
      // Some links are actually not links,
      // But we wrap these in <span> for adding title and class attributes.
      if (empty($link['html'])) {
        $link['title'] = check_plain($link['title']);
      }
      $span_attributes = '';
      if (isset($link['attributes'])) {
        $span_attributes = drupal_attributes($link['attributes']);
      }
      $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
    }

    $i++;
    $output .= "</li>\n";
  }

  $output .= '</ul>';

  if ($wrapper) {
    $output .= '</div>';
  }

  return $output;
}

/**
 * Implements theme_{{machine_name}}_button_group().
 */
function theme_{{machine_name}}_button_group($variables) {
  $buttons = $variables['buttons'];
  $attributes = $variables['attributes'];
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('btn-group')));

  $output .= '<div' . drupal_attributes($attributes) . '>';

  $num_links = count($buttons);
  $i = 1;

  foreach ($buttons as $key => $button) {
    $class = array($key);
    $class[] = 'btn';

    // Add first, last and active classes to the list of links.
    if ($i == 1) {
      $class[] = 'first';
    }
    if ($i == $num_links) {
      $class[] = 'last';
    }

    // Add Bootstrap attributes.
    $button['attributes'] = drupal_array_merge_deep($button['attributes'], array('class' => $class));

    $output .= l($button['title'], $button['href'], $button);

    $i++;
    $output .= "</li>\n";
  }

  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_{{machine_name}}_button_dropdown().
 */
function theme_{{machine_name}}_button_dropdown($variables) {
  $button = $variables['button'];
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $split = $variables['split'];
  $output = '';

  // Add Bootstrap attributes.
  $attributes = drupal_array_merge_deep($attributes, array('class' => array('btn-group')));

  $output .= '<div' . drupal_attributes($attributes) . '>';

  // Handle split buttons.
  if ($split) {
    // Add Boostrap attributes.
    $button['attributes'] = drupal_array_merge_deep($button['attributes'], array(
      'class' => array('btn'),
    ));
  }
  else {
    // Add Boostrap attributes.
    $button['attributes'] = drupal_array_merge_deep($button['attributes'], array(
      'class' => array('btn', 'dropdown-toggle'),
      'data-toggle' => 'dropdown',
    ));

    // When split, we do not want the button to have href.
    $button['href'] = '';
    $button['absolute'] = TRUE;
    $button['fragment'] = FALSE;

    // Add caret to title.
    $button['title'] .= '<span class="caret"></span>';
    $button['html'] = TRUE;
  }

  // Render the button.
  $output .= l($button['title'], $button['href'], $button);

  if ($split) {
    // Add a split button.
    $split_attributes = drupal_array_merge_deep($button['attributes'], array(
      'class' => array('btn', 'dropdown-toggle'),
      'data-toggle' => 'dropdown',
    ));
    $output .= '<button ' . drupal_attributes($split_attributes) . '><span class="caret"></span></button>';
  }

  // Render the dropdown menu.
  $output .= theme('{{machine_name}}_dropdown', array('links' => $links));

  $output .= '</div>';
  return $output;
}

/**
 * Implements template_proprocess_{{machine_name}}_modal().
 */
function {{machine_name}}_preprocess_{{machine_name}}_modal(&$variables) {
  $variables['modal_id'] = drupal_html_id($variables['id']);

  // Create trigger button.
  if (isset($variables['trigger_button'])) {
    $trigger_button = $variables['trigger_button'];
    $text = (isset($trigger_button['text'])) ? $trigger_button['text'] : t('Open');
    $attributes = array(
      'data-toggle' => 'modal',
      'data-target' => '#' . $variables['modal_id'],
      'class' => array('btn', 'btn-default')
    );
    
    if (isset($trigger_button['attributes'])) {
      $attributes = array_merge($attributes, $trigger_button['attributes']);
    }

    $variables['trigger_button']['#markup'] = l($text, '', array(
      'absolute' => TRUE,
      'fragment' => FALSE,
      'attributes' => $attributes,
    ));
  }

  // Format content and add to template.
  if (isset($variables['content'])) {
    if (is_string($variables['content'])) {
      $variables['content']['#markup'] = $variables['content'];
    }
  }

  // Format modal butttons.
  if (isset($variables['buttons'])) {
    if (count($variables['buttons'])) {
      foreach ($variables['buttons'] as $key => $button) {
        $text = isset($button['text']) ? $button['text'] : '';
        $link = isset($button['link']) ? $button['link'] : '';
        $options = array();

        // If not link is provided, set as fragment.
        if (empty($link)) {
          $options['absolute'] = TRUE;
          $options['fragment'] = FALSE;
        }

        // Merge options.
        $options['attributes'] = array('class' => array('btn', 'btn-default'));
        if (isset($button['attributes'])) {
          $options['attributes'] = array_merge($options['attributes'], $button['attributes']);
        }

        $variables['buttons'][$key] = l($button['text'], $link, $options);
      }
    }
  }
}

/**
 * Implements template_proprocess_{{machine_name}}_tabs().
 */
function {{machine_name}}_preprocess_{{machine_name}}_tabs(&$variables) {
  $tabs = &$variables['tabs'];

  // Create an id for each tab.
  foreach ($tabs as &$tab) {
    // Create an attributes_array for each tab.
    $attributes_array = !empty($tab['attributes_array']) ? $tab['attributes_array'] : array();

    // Get options.
    $options = !empty($tab['options']) ? $tab['options'] : array();
    $options = array_merge($options, array('html' => TRUE, 'attributes' => $attributes_array));

    // Create the tab element.
    $tab['tab'] = array(
      '#theme' => 'link',
      '#text' => $tab['title'],
      '#path' => isset($tab['href']) ? $tab['href'] : current_path(),
      '#options' => $options,
    );

    // If content is not empty, this tab can toggle a tab.
    if (!empty($tab['content'])) {
      $tab['id'] = drupal_html_class($tab['title']);
      $tab['tab']['#options']['fragment'] = $tab['id'];
      $tab['tab']['#options']['attributes']['data-toggle'] = "tab";
    }
  }

  // Default to nav-tabs if type is not provided.
  if (empty($variables['type'])) {
    $variables['type'] = 'tabs';
  }
}

/**
 * Implements template_preprocess_{{machine_name}}_alert().
 */
function template_preprocess_{{machine_name}}_alert(&$variables) {
  $type = $variables['type'];

  // Add classes.
  $variables['classes_array'][] = 'alert';
  $variables['classes_array'][] = 'alert-' . $type;
}

/**
 * Implements theme_{{machine_name}}_icon().
 */
function theme_{{machine_name}}_icon($variables) {
  $icon = $variables['icon'];
  $text = $variables['text'];
  $link = $variables['link'];

  $html  = '<i class="fa fa-' . check_plain($icon) . '">';
  if ($text) {
    $html .= '<span class="element-invisible">' . check_plain($text) . '</span>';
  }
  $html .= '</i>';

  if ($link) {
    $link_options = array('html' => TRUE);
    if ($text) {
      $link_options['attributes']['title'] = $text;
    }
    return l($html, $link, $link_options);
  }

  return $html;
}
