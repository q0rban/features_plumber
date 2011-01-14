<?php
// $Id$

/**
 * @file
 * Features Plumber features export functions.
 */

/**
 * Helper to features_plumber_features_export_alter().
 */
function _features_plumber_features_export_alter(&$export, $module_name) {
  $cleanup = array();
  features_plumber_include('crud');
  foreach (features_plumber_records_load_by_feature($module_name) as $record) {
    if (empty($module_name) || $module_name == $record->feature) {
      // If this is a depencency, we need a different part of the $export array.
      if ($record->component == 'dependencies') {
        $array = &$export['dependencies'];
      }
      elseif (isset($export['features'][$record->component])) {
        $array = &$export['features'][$record->component];
      }
      else {
        continue;
      }

      if (isset($array[$record->component_val])) {
        unset($array[$record->component_val]);
        $cleanup[$record->component] = TRUE;
        $export['features']['features_plumber'][$record->name] = $record->name;
      }
    }
  }

  if (!isset($export['features']['features_plumber'])) {
    $cleanup['features_plumber'] = TRUE;
  }
  // Make sure these guys are here.
  else {
    $export['dependencies']['features_plumber'] = 'features_plumber';
    ctools_features_export(array('features_plumber'), $export, $module_name);
  }

  foreach (array_keys($cleanup) as $component) {
    $function = "features_plumber_export_{$component}_cleanup";
    if (function_exists($function)) {
      $function($export, $module_name);
    }
  }
}

/**
 * Cleanup after Views removals.
 */
function features_plumber_export_views_cleanup(&$export) {
  if (empty($export['features']['views'])) {
    unset($export['features']['views'], $export['features']['views_api'], $export['dependencies']['views']);
  }
}

/**
 * Cleanup after Features Plumber removal.
 */
function features_plumber_export_features_plumber_cleanup(&$export) {
  if (empty($export['features']['features_plumber'])) {
    unset($export['dependencies']['features_plumber'], $export['features']['ctools']['features_plumber:features_plumber_records:1']);
  }
}