<?php
// $Id$

/**
 * @file
 * Features Plumber Drush commands.
 */

/**
 * Implements hook_drush_help().
 */
function features_plumber_drush_help($section) {
  switch ($section) {
    case 'drush:features-component-remove':
      return dt('Remove a component from a feature.');
  }
}

/**
 * Implements hook_drush_command().
 */
function features_plumber_drush_command() {
  $items = array();

  $items['features-component-remove'] = array(
    'description' => dt('Remove a component from a feature.'),
    'arguments' => array(
      'feature-name' => 'The machine name of the feature.',
      'component' => 'The name of the component, ie `views`.',
      'component-value' => 'The value of the component, ie `frontpage` (the machine name of a view.',
    ),
    'aliases' => array('fcr'),
  );

  return $items;
}

function drush_features_plumber_features_component_remove_validate($feature = NULL, $component = NULL, $component_val = NULL) {
  $dt_args = array(
    '@feature' => $feature,
    '@component' => $component,
    '@component-val' => $component_val,
  );

  $name = features_plumber_generate_name($feature, $component, $component_val);
  $records = features_plumber_records_load_all();

  if (!isset($feature) || !isset($component) || !isset($component_val)) {
    $message = 'You must specify all arguments for this command';
  }
  elseif (!features_plumber_component_is_supported($component)) {
    $message = 'The component @component is unsupported.';
  }
  elseif (!(($module = feature_load($feature, TRUE)) && module_exists($feature))) {
    $message = 'There is no feature named @feature on this site.';
  }
  elseif (isset($records[$name])) {
    $message = '@component->@component-val has already been removed from feature @feature.';
  }
  else {
    $dt_args['@feature'] = $module->name;
    $component_vals = array();
    if ($component == 'dependencies') {
      $component_vals = $module->info['dependencies'];
    }
    elseif (isset($module->info['features'][$component])) {
      $component_vals = $module->info['features'][$component];
    }
    if (!in_array($component_val, $component_vals)) {
      $message = 'The component value @component-val does not exist for component @component in feature @feature.';
    }
  }

  if (isset($message)) {
    drush_log(dt($message, $dt_args), 'error');
    return FALSE;
  }
}

function drush_features_component_remove($feature, $component, $component_val) {
  $dt_args = array(
    '@feature' => $feature,
    '@component' => $component,
    '@component-val' => $component_val,
  );

  $record = new stdClass();
  $record->name = features_plumber_generate_name($feature, $component, $component_val);
  $record->feature = $feature;
  $record->component = $component;
  $record->component_val = $component_val;

  if (features_plumber_record_save($record)) {
    drush_log(dt('Successfully wrote the record to features_plumber.'));
    if (drush_confirm(dt('About to overrwrite the feature code. Do you really want to continue?'))) {
      drush_backend_invoke("features-update $feature");
    }
  }
}